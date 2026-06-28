#pragma once
#include <cstdint>

enum class Move : uint_fast8_t {
    F, Fp, F2,
    R, Rp, R2,
    U, Up, U2
};

/*
==================================================
NOTE
==================================================
The following is an automatically generated output by an annealing algorithm, finding the optimal memory layout for the bit stickers representation, it has been manually edited to include some additionally helpful information, such as the solved state

==================================================
ASCII MANIFOLD: STICKER TO MEMORY SLOT LAYOUT
==================================================
             +-------+
             | 01 10 |
             | 05 09 |
     +-------+-------+-------+-------+
     | 00 06 | 04 07 | 08 11 | 12 02 |
     | xx 19 | 18 15 | 17 14 | 13 xx |
     +-------+-------+-------+-------+
             | 20 16 |
             | xx 03 |
             +-------+
        (xx = fixed DBL corner)

==================================================
ASCII MANIFOLD: MARKED STICKERS
==================================================
             +-------+
             | 01 02 |
             | 03 04 |
     +-------+-------+-------+-------+
     | 00 00 | 00 00 | 00 00 | 00 00 |
     | xx 00 | 00 00 | 00 00 | 00 xx |
     +-------+-------+-------+-------+
             | 05 06 |
             | xx 07 |
             +-------+
        (xx = fixed DBL corner)

==================================================
GENERATED C++ BITWISE CODE:
==================================================
--- Move U ---
move_U(state) {
    new_state = state & 0x7FFFFF8000000E00ULL;
    new_state |= (state & 0x0000007E3F1FF000ULL) >> 12;
    new_state |= (state & 0x00000001C0E00000ULL) >> 3;
    new_state |= (state & 0x00000000000001F8ULL) << 27;
    new_state |= (state & 0x0000000000000007ULL) << 36;
    return new_state;
}

--- Move U' ---
move_U_prime(state) {
    new_state = state & 0x7FFFFF8000000E00ULL;
    new_state |= (state & 0x0000007000000000ULL) >> 36;
    new_state |= (state & 0x0000000FC0000000ULL) >> 27;
    new_state |= (state & 0x00000000381C0000ULL) << 3;
    new_state |= (state & 0x0000000007E3F1FFULL) << 12;
    return new_state;
}

--- Move U2 ---
move_U2(state) {
    new_state = state & 0x7FFFFF8000000E00ULL;
    new_state |= (state & 0x000000703F000000ULL) >> 24;
    new_state |= (state & 0x0000000FC0E00000ULL) >> 15;
    new_state |= (state & 0x00000000001F81C0ULL) << 15;
    new_state |= (state & 0x000000000000703FULL) << 24;
    return new_state;
}

--- Move R ---
move_R(state) {
    new_state = state & 0x7FC00000001FF1FFULL;
    new_state |= (state & 0x003F007000000000ULL) >> 27;
    new_state |= (state & 0x0000E00000000000ULL) >> 18;
    new_state |= (state & 0x00001F8FFFE00000ULL) << 9;
    new_state |= (state & 0x0000000000000E00ULL) << 36;
    return new_state;
}

--- Move R' ---
move_R_prime(state) {
    new_state = state & 0x7FC00000001FF1FFULL;
    new_state |= (state & 0x0000E00000000000ULL) >> 36;
    new_state |= (state & 0x003F1FFFC0000000ULL) >> 9;
    new_state |= (state & 0x0000000038000000ULL) << 18;
    new_state |= (state & 0x0000000007E00E00ULL) << 27;
    return new_state;
}

--- Move R2 ---
move_R2(state) {
    new_state = state & 0x7FC00000001FF1FFULL;
    new_state |= (state & 0x003F1F8038000000ULL) >> 18;
    new_state |= (state & 0x0000E00000000000ULL) >> 9;
    new_state |= (state & 0x0000007000000000ULL) << 9;
    new_state |= (state & 0x0000000FC7E00E00ULL) << 18;
    return new_state;
}

--- Move F ---
move_F(state) {
    new_state = state & 0x00001FFFC0000FFFULL;
    new_state |= (state & 0x7FC0000000000000ULL) >> 42;
    new_state |= (state & 0x003FE000001FF000ULL) << 9;
    new_state |= (state & 0x000000003FE00000ULL) << 24;
    return new_state;
}

--- Move F' ---
move_F_prime(state) {
    new_state = state & 0x00001FFFC0000FFFULL;
    new_state |= (state & 0x003FE00000000000ULL) >> 24;
    new_state |= (state & 0x7FC000003FE00000ULL) >> 9;
    new_state |= (state & 0x00000000001FF000ULL) << 42;
    return new_state;
}

--- Move F2 ---
move_F2(state) {
    new_state = state & 0x00001FFFC0000FFFULL;
    new_state |= (state & 0x7FFFE00000000000ULL) >> 33;
    new_state |= (state & 0x000000003FFFF000ULL) << 33;
    return new_state;
}
*/

struct Cube_State {
    uint_fast64_t raw_state;

    explicit constexpr Cube_State(uint64_t value) noexcept : raw_state(value) {}
    constexpr Cube_State() noexcept : raw_state(0x50060000A0018E08ULL) {} 

    constexpr bool operator==(const Cube_State &other) const noexcept { return raw_state == other.raw_state; }
    constexpr bool operator!=(const Cube_State &other) const noexcept { return raw_state != other.raw_state; }

    template <Move M>
    [[nodiscard]] constexpr Cube_State turn() const noexcept {
        if constexpr (M == Move::U) {
            return Cube_State(
                (((raw_state & 0x7FFFFF8000000E00ULL) |
                ((raw_state & 0x0000007E3F1FF000ULL) >> 12) |
                ((raw_state & 0x00000001C0E00000ULL) >> 3) |
                ((raw_state & 0x00000000000001F8ULL) << 27) |
                ((raw_state & 0x0000000000000007ULL) << 36)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::Up) {
            return Cube_State(
                (((raw_state & 0x7FFFFF8000000E00ULL) |
                ((raw_state & 0x0000007000000000ULL) >> 36) |
                ((raw_state & 0x0000000FC0000000ULL) >> 27) |
                ((raw_state & 0x00000000381C0000ULL) << 3) |
                ((raw_state & 0x0000000007E3F1FFULL) << 12)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::U2) {
            return Cube_State(
                (((raw_state & 0x7FFFFF8000000E00ULL) |
                ((raw_state & 0x000000703F000000ULL) >> 24) |
                ((raw_state & 0x0000000FC0E00000ULL) >> 15) |
                ((raw_state & 0x00000000001F81C0ULL) << 15) |
                ((raw_state & 0x000000000000703FULL) << 24)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::R) {
            return Cube_State(
                (((raw_state & 0x7FC00000001FF1FFULL) |
                ((raw_state & 0x003F007000000000ULL) >> 27) |
                ((raw_state & 0x0000E00000000000ULL) >> 18) |
                ((raw_state & 0x00001F8FFFE00000ULL) << 9) |
                ((raw_state & 0x0000000000000E00ULL) << 36)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::Rp) {
            return Cube_State(
                (((raw_state & 0x7FC00000001FF1FFULL) |
                ((raw_state & 0x0000E00000000000ULL) >> 36) |
                ((raw_state & 0x003F1FFFC0000000ULL) >> 9) |
                ((raw_state & 0x0000000038000000ULL) << 18) |
                ((raw_state & 0x0000000007E00E00ULL) << 27)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::R2) {
            return Cube_State(
                (((raw_state & 0x7FC00000001FF1FFULL) |
                ((raw_state & 0x003F1F8038000000ULL) >> 18) |
                ((raw_state & 0x0000E00000000000ULL) >> 9) |
                ((raw_state & 0x0000007000000000ULL) << 9) |
                ((raw_state & 0x0000000FC7E00E00ULL) << 18)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::F) {
            return Cube_State(
                (((raw_state & 0x00001FFFC0000FFFULL) |
                ((raw_state & 0x7FC0000000000000ULL) >> 42) |
                ((raw_state & 0x003FE000001FF000ULL) << 9) |
                ((raw_state & 0x000000003FE00000ULL) << 24)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::Fp) {
            return Cube_State(
                (((raw_state & 0x00001FFFC0000FFFULL) |
                ((raw_state & 0x003FE00000000000ULL) >> 24) |
                ((raw_state & 0x7FC000003FE00000ULL) >> 9) |
                ((raw_state & 0x00000000001FF000ULL) << 42)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else if constexpr (M == Move::F2) {
            return Cube_State(
                (((raw_state & 0x00001FFFC0000FFFULL) |
                ((raw_state & 0x7FFFE00000000000ULL) >> 33) |
                ((raw_state & 0x000000003FFFF000ULL) << 33)) 
                & 0x7FFFFFFFFFFFFFFFULL)
            );
        } else {
            return *this;
        }
    }
};

template <typename Func>
constexpr void for_each_move(Func&& f) {
    f.template operator()<Move::F>(Move::F);
    f.template operator()<Move::Fp>(Move::Fp);
    f.template operator()<Move::F2>(Move::F2);
    f.template operator()<Move::R>(Move::R);
    f.template operator()<Move::Rp>(Move::Rp);
    f.template operator()<Move::R2>(Move::R2);
    f.template operator()<Move::U>(Move::U);
    f.template operator()<Move::Up>(Move::Up);
    f.template operator()<Move::U2>(Move::U2);
}