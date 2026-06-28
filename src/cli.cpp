#include "cli.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

void run_interactive_cli(const rubiks_solver& solver) {
    std::unordered_map<std::string, Move> move_map = {
        {"F", Move::F}, {"F'", Move::Fp}, {"F2", Move::F2},
        {"R", Move::R}, {"R'", Move::Rp}, {"R2", Move::R2},
        {"U", Move::U}, {"U'", Move::Up}, {"U2", Move::U2}
    };

    const char* names[] = {"F", "F'", "F2", "R", "R'", "R2", "U", "U'", "U2"};

    std::cout << "\n==========================================\n";
    std::cout << "        2x2 ALGEBRAIC CUBE SOLVER         \n";
    std::cout << "==========================================\n";
    std::cout << "Valid moves: F, F', F2, R, R', R2, U, U', U2\n";
    std::cout << "Separate moves with spaces (e.g., R U R' U').\n";
    std::cout << "Type 0 to exit the program.\n";
    std::cout << "==========================================\n";

    std::string line;
    while (true) {
        std::cout << "\nEnter scramble: ";
        if (!std::getline(std::cin, line)) break;

        if (line == "0") {
            std::cout << "Exiting...\n";
            break;
        }

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<Move> scramble;
        bool valid_input = true;

        while (ss >> token) {
            if (move_map.find(token) != move_map.end()) {
                scramble.push_back(move_map[token]);
            } else {
                std::cout << "Error: Unrecognized move '" << token << "'. Please try again.\n";
                valid_input = false;
                break;
            }
        }

        if (!valid_input || scramble.empty()) continue;

        std::vector<Move> solution = solver.solve(scramble);

        std::cout << "Solution (" << solution.size() << " moves): ";
        for (Move m : solution) {
            std::cout << names[static_cast<int>(m)] << " ";
        }
        std::cout << "\n";
    }
}