#pragma once

#include "State.hh"

#include <vector>
#include <memory>

class NPuzzleSolver {
    public:
        static std::vector<std::shared_ptr<State>> gen_neighbours(const std::shared_ptr<State>& state);
        static visual_data a_star_solver(std::vector<std::vector<int>> initial);
        static void set_size(int size);
        static int get_size();

    private:
        static visual_data convert_output(std::shared_ptr<State> last, int tc, int sc);
        static int size;
};
