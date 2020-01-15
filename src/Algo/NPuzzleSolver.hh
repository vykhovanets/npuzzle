#pragma once

#include "State.hh"

#include <vector>
#include <memory>

class NPuzzleSolver {
    public:
        static std::vector<std::shared_ptr<State>> gen_neighbours(const std::shared_ptr<State>& state);
        static void a_star_solver(std::vector<std::vector<int>> initial);
        static void set_size(int size);
        static int get_size();

    private:
        static int size;
};
