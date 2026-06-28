#include "graph_engine.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <stdexcept>

graph_engine::graph_engine() {
    parent_id.resize(MAX_STATES);
    move_from_parent.resize(MAX_STATES);
    depth.resize(MAX_STATES);
    id_to_state.resize(MAX_STATES); 
    state_to_id.reserve(MAX_STATES); 
}

void graph_engine::build_graph() {
    std::cout << "Cayley graph is initialized...\n";
    auto start_time = std::chrono::high_resolution_clock::now();

    std::queue<uint32_t> q;

    Cube_State solved{};
    uint32_t current_id = 0;

    state_to_id[solved.raw_state] = current_id;
    id_to_state[current_id] = solved;
    parent_id[current_id] = current_id; 
    depth[current_id] = 0;
    
    q.push(current_id);
    current_id++;

    while (!q.empty()) {
        uint32_t p_id = q.front();
        q.pop();

        Cube_State current_state = id_to_state[p_id];
        uint8_t next_depth = depth[p_id] + 1;

        for_each_move([&]<Move M>(Move m_val) {
            Cube_State next_state = current_state.turn<M>();

            if (state_to_id.find(next_state.raw_state) == state_to_id.end()) {
                uint32_t n_id = current_id++;

                state_to_id[next_state.raw_state] = n_id;
                id_to_state[n_id] = next_state;
                
                parent_id[n_id] = p_id;
                move_from_parent[n_id] = m_val;
                depth[n_id] = next_depth;

                q.push(n_id);
            }
        });
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;

    std::cout << "BFS completed in " << diff.count() << " sec\n";
    std::cout << "State count: " << state_to_id.size() << " / " << MAX_STATES << "\n";
    
    // Clean exception handling
    if (state_to_id.size() != MAX_STATES) {
        throw std::runtime_error("State space manifold boundary check failed!");
    }
}

std::vector<Move> graph_engine::get_word(uint32_t id) const {
    std::vector<Move> word;
    while (depth[id] > 0) {
        word.push_back(move_from_parent[id]);
        id = parent_id[id];
    }
    std::reverse(word.begin(), word.end());
    return word;
}