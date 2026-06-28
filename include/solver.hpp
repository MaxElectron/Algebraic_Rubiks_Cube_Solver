#pragma once
#include "cube_state.hpp"
#include <string>
#include <vector>

struct Runtime_Node {
    int32_t children[9];
    uint32_t lhs_size;
    std::vector<Move> rhs;
    bool is_terminal;
};

class rubiks_solver {
public:
    std::vector<Runtime_Node> automaton;

    explicit rubiks_solver(const std::string& filename);

    std::vector<Move> solve(const std::vector<Move>& scramble) const;

private:
    Move invert_move(Move m) const;
};