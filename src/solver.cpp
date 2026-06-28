#include "solver.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

rubiks_solver::rubiks_solver(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("Could not open the binary file.");

    uint32_t num_nodes;
    in.read(reinterpret_cast<char*>(&num_nodes), sizeof(num_nodes));
    automaton.resize(num_nodes);

    for (uint32_t i = 0; i < num_nodes; ++i) {
        in.read(reinterpret_cast<char*>(automaton[i].children), 9 * sizeof(int32_t));
        in.read(reinterpret_cast<char*>(&automaton[i].lhs_size), sizeof(uint32_t));
        
        uint32_t rhs_size;
        in.read(reinterpret_cast<char*>(&rhs_size), sizeof(rhs_size));
        
        if (rhs_size > 0) {
            automaton[i].is_terminal = true;
            std::vector<uint8_t> rhs_bytes(rhs_size);
            in.read(reinterpret_cast<char*>(rhs_bytes.data()), rhs_size);
            for (uint8_t b : rhs_bytes) {
                automaton[i].rhs.push_back(static_cast<Move>(b));
            }
        } else {
            automaton[i].is_terminal = false;
        }
    }
}

Move rubiks_solver::invert_move(Move m) const {
    switch (m) {
        case Move::U: return Move::Up;
        case Move::Up: return Move::U;
        case Move::R: return Move::Rp;
        case Move::Rp: return Move::R;
        case Move::F: return Move::Fp;
        case Move::Fp: return Move::F;
        default: return m;
    }
}

std::vector<Move> rubiks_solver::solve(const std::vector<Move>& scramble) const {
    std::vector<Move> inverted_scramble;
    for (auto it = scramble.rbegin(); it != scramble.rend(); ++it) {
        inverted_scramble.push_back(invert_move(*it));
    }

    std::vector<int32_t> state_stack = {0};
    std::vector<Move> result;
    
    std::vector<Move> remaining;
    for (auto it = inverted_scramble.rbegin(); it != inverted_scramble.rend(); ++it) {
        remaining.push_back(*it);
    }

    while (!remaining.empty()) {
        Move m = remaining.back();
        remaining.pop_back();

        int32_t current_state = state_stack.back();
        int32_t next_state = automaton[current_state].children[static_cast<int>(m)];
        
        state_stack.push_back(next_state);
        result.push_back(m);

        if (automaton[next_state].is_terminal) {
            uint32_t pop_count = automaton[next_state].lhs_size;
            for (uint32_t i = 0; i < pop_count; ++i) {
                state_stack.pop_back();
                result.pop_back();
            }

            const auto& rhs = automaton[next_state].rhs;
            for (auto it = rhs.rbegin(); it != rhs.rend(); ++it) {
                remaining.push_back(*it);
            }
        }
    }
    return result;
}