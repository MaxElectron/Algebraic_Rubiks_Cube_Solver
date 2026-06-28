#include "automaton_compiler.hpp"
#include <fstream>
#include <iostream>
#include <queue>

automaton_compiler::automaton_compiler(const graph_engine& g) : graph(g) {
    create_node(0); 
}

int automaton_compiler::create_node(uint32_t depth) {
    nodes.emplace_back(depth);
    return nodes.size() - 1;
}

void automaton_compiler::insert_rule(const std::vector<Move>& lhs, const std::vector<Move>& rhs) {
    int current = 0;
    for (Move m : lhs) {
        int idx = static_cast<int>(m);
        if (nodes[current].children[idx] == -1) {
            nodes[current].children[idx] = create_node(nodes[current].depth + 1);
        }
        current = nodes[current].children[idx];
    }
    if (!nodes[current].is_terminal) {
        nodes[current].is_terminal = true;
        nodes[current].rhs = rhs;
        nodes[current].lhs_size = nodes[current].depth;
    }
}

bool automaton_compiler::contains_reducible_suffix(const std::vector<Move>& lhs) const {
    for (size_t i = 1; i < lhs.size(); ++i) {
        int current = 0;
        for (size_t j = i; j < lhs.size(); ++j) {
            int idx = static_cast<int>(lhs[j]);
            current = nodes[current].children[idx];
            if (current == -1) break;
            if (nodes[current].is_terminal) return true;
        }
    }
    return false;
}

void automaton_compiler::build_dfa() {
    std::queue<int> q;
    for (int i = 0; i < 9; ++i) {
        if (nodes[0].children[i] == -1) {
            nodes[0].children[i] = 0;
        } else {
            nodes[nodes[0].children[i]].fail = 0;
            q.push(nodes[0].children[i]);
        }
    }

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < 9; ++i) {
            int child = nodes[current].children[i];
            if (child != -1) {
                int fail_node = nodes[nodes[current].fail].children[i];
                nodes[child].fail = fail_node;

                if (!nodes[child].is_terminal && fail_node != -1 && nodes[fail_node].is_terminal) {
                    nodes[child].is_terminal = true;
                    nodes[child].rhs = nodes[fail_node].rhs;
                    nodes[child].lhs_size = nodes[fail_node].lhs_size;
                }
                q.push(child);
            } else {
                nodes[current].children[i] = nodes[nodes[current].fail].children[i];
            }
        }
    }
}

void automaton_compiler::compile() {
    std::cout << "Extracting minimal Knuth-Bendix rules...\n";
    int rules_found = 0, rules_kept = 0;

    for (uint32_t id = 0; id < graph_engine::MAX_STATES; ++id) {
        std::vector<Move> word_s = graph.get_word(id);
        
        for_each_move([&]<Move M>(Move m_val) {
            Cube_State next_state = graph.id_to_state[id].turn<M>();
            uint32_t next_id = graph.state_to_id.at(next_state.raw_state);
            
            std::vector<Move> lhs = word_s;
            lhs.push_back(m_val);
            std::vector<Move> rhs = graph.get_word(next_id);
            
            if (lhs != rhs) {
                rules_found++;
                if (!contains_reducible_suffix(lhs)) {
                    insert_rule(lhs, rhs);
                    rules_kept++;
                }
            }
        });
    }
    std::cout << "Raw sub-optimal edges ignored: " << rules_found - rules_kept << "\n";
    std::cout << "Minimal rules inserted: " << rules_kept << "\n";
    std::cout << "Building Aho-Corasick DFA transitions...\n";
    build_dfa();
    std::cout << "Automaton complete! Total states: " << nodes.size() << "\n";
}

void automaton_compiler::save_to_file(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    uint32_t num_nodes = nodes.size();
    out.write(reinterpret_cast<const char*>(&num_nodes), sizeof(num_nodes));

    for (const auto& node : nodes) {
        out.write(reinterpret_cast<const char*>(node.children), 9 * sizeof(int32_t));
        
        out.write(reinterpret_cast<const char*>(&node.lhs_size), sizeof(node.lhs_size));
        
        uint32_t rhs_size = node.is_terminal ? node.rhs.size() : 0;
        out.write(reinterpret_cast<const char*>(&rhs_size), sizeof(rhs_size));
        
        if (rhs_size > 0) {
            std::vector<uint8_t> rhs_bytes(rhs_size);
            for (size_t i = 0; i < rhs_size; ++i) rhs_bytes[i] = static_cast<uint8_t>(node.rhs[i]);
            out.write(reinterpret_cast<const char*>(rhs_bytes.data()), rhs_size);
        }
    }
    std::cout << "Saved to " << filename << "\n";
}