#pragma once
#include "graph_engine.hpp"
#include <string>
#include <vector>

struct Trie_Node {
    int32_t children[9];
    int32_t fail;
    std::vector<Move> rhs;
    uint32_t depth;
    uint32_t lhs_size;
    bool is_terminal;

    Trie_Node(uint32_t d = 0) {
        for (int i = 0; i < 9; ++i) children[i] = -1;
        fail = -1;
        depth = d;
        lhs_size = 0;
        is_terminal = false;
    }
};

class automaton_compiler {
public:
    std::vector<Trie_Node> nodes;
    const graph_engine& graph;

    explicit automaton_compiler(const graph_engine& g);

    void compile();
    void save_to_file(const std::string& filename) const;

private:
    int create_node(uint32_t depth);
    void insert_rule(const std::vector<Move>& lhs, const std::vector<Move>& rhs);
    bool contains_reducible_suffix(const std::vector<Move>& lhs) const;
    void build_dfa();
};