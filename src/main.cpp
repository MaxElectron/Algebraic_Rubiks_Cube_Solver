#include "cube_state.hpp"
#include "graph_engine.hpp"
#include "automaton_compiler.hpp"
#include "solver.hpp"
#include "cli.hpp"
#include <filesystem> 
#include <iostream>

int main() {
    const std::string bin_filename = "2x2_automaton.bin";

    try {
        if (!std::filesystem::exists(bin_filename)) {
            std::cout << "[SYSTEM] " << bin_filename << " not found. Initiating Compiler...\n";
            std::cout << std::string(42, '-') << "\n";
            
            graph_engine engine;
            engine.build_graph();
            
            automaton_compiler compiler(engine);
            compiler.compile();
            compiler.save_to_file(bin_filename);
            
            std::cout << std::string(42, '-') << "\n";
        } else {
            std::cout << "[SYSTEM] Existing automaton binary found. Skipping compilation.\n";
        }

        std::cout << "[SYSTEM] Initializing Solver Runtime...\n";
        rubiks_solver solver(bin_filename);

        run_interactive_cli(solver);

    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}