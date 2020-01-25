#pragma once

#include "State.hh"
#include "MyPriorQueue.hh"

#include <vector>
#include <memory>
#include <set>
#include <functional>

class NPuzzleSolver {
    public:
        static std::vector<std::shared_ptr<State>> gen_neighbours(
                const std::shared_ptr<State>& state,
                const MyPriorQueue<std::shared_ptr<State>,std::vector<std::shared_ptr<State>>,std::function<bool(std::shared_ptr<State>,std::shared_ptr<State>)>>& open,
                const std::set<std::shared_ptr<State>>& closed);
        static visual_data a_star_solver(const Snapshot& initial);
    private:
        static visual_data convert_output(std::shared_ptr<State> last, int tc, int sc);
};
