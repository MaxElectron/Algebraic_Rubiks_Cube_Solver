#pragma once
#include "cube_state.hpp"
#include <cstdint>
#include <unordered_map>
#include <vector>

struct identity_hash {
    std::size_t operator()(uint64_t key) const noexcept {
        key ^= key >> 33;
        key *= 0xff51afd7ed558ccdULL; 
        key ^= key >> 33;
        return static_cast<std::size_t>(key);
    }
};

class graph_engine {
public:
    static constexpr uint32_t MAX_STATES = 3674160;

    std::vector<uint32_t> parent_id;
    std::vector<Move> move_from_parent;
    std::vector<uint8_t> depth;
    std::vector<Cube_State> id_to_state;

    std::unordered_map<uint64_t, uint32_t, identity_hash> state_to_id;

    graph_engine();

    void build_graph();

    std::vector<Move> get_word(uint32_t id) const;
};