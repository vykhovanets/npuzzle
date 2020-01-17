#include "NPuzzleSolver.hh"
#include <algorithm>
#include "MyPriorQueue.hh"

// TODO: i need to see the parent, to ignore repeating the states
// or not ?
// if it's already in the closed queue, then no
std::vector<std::shared_ptr<State>> NPuzzleSolver::gen_neighbours(
        const std::shared_ptr<State>& state) {
    int size = NPuzzleSolver::size;
    const auto& parent = state->get_parent();
    point pre{-1, -1};
    if (parent) {
        pre = parent->get_blank_pos();
    }
    std::vector<std::shared_ptr<State>> neighbours;
    auto const& bpos = state->get_blank_pos();

    if ((bpos.x + 1 <= size) && !(bpos.x + 1 == pre.x && bpos.y == pre.y)) {
        State next(*state);
        next.set_parent(state);
        std::swap(next[bpos.y][bpos.x + 1], next[bpos.y][bpos.x]);
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    if ((bpos.x - 1 >= 0) && !(bpos.x - 1 == pre.x && bpos.y == pre.y)) {
        State next(*state);
        next.set_parent(state);
        std::swap(next[bpos.y][bpos.x - 1], next[bpos.y][bpos.x]);
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    if ((bpos.y + 1 <= size) && !(bpos.y + 1 == pre.y && bpos.x == pre.x)) {
        State next(*state);
        next.set_parent(state);
        std::swap(next[bpos.y + 1][bpos.x], next[bpos.y][bpos.x]);
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    if ((bpos.y - 1 >= 0) && !(bpos.y - 1 == pre.y && bpos.x == pre.x)) {
        State next(*state);
        next.set_parent(state);
        std::swap(next[bpos.y - 1][bpos.x], next[bpos.y][bpos.x]);
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    return neighbours;
}

void NPuzzleSolver::set_size(int size) {
    NPuzzleSolver::size = size;
}

int NPuzzleSolver::get_size() {
    return NPuzzleSolver::size;
}

/*
   make an openlist containing only the starting node
   make an empty closed list
   while (the destination node has not been reached):
       consider the node with the lowest f score in the open list
       if (this node is our destination node) :
           we are finished
       if not:
           put the current node in the closed list and look at all of its neighbors
           for (each neighbor of the current node):
               if (neighbor has lower g value than current and is in the closed list) :
                   replace the neighbor with the new, lower, g value
                   current node is now the neighbor's parent
               else if (current g value is lower and this neighbor is in the open list ) :
                   replace the neighbor with the new, lower, g value
                   change the neighbor's parent to our current node

               else if this neighbor is not in both lists:
                   add it to the open list and set its g
*/

void NPuzzleSolver::a_star_solver(Snapshot initial) {
    std::shared_ptr<State> start_state = std::make_shared<State>(initial, nullptr, point{2, 2});
    auto comparator = [](auto lhs,auto rhs) { return lhs->get_f() > rhs->get_f(); };
    MyPriorQueue<std::shared_ptr<State>,std::vector<std::shared_ptr<State>>,decltype(comparator)> open(comparator);
    std::vector<std::shared_ptr<State>> closed;

    open.push(start_state);

    //TODO: figure out the end condition
    while (true) {
        // prioritized by f
        auto const& cur = open.top();
        open.pop();
        if (!cur->get_f()) {
            // we are done
            break;
        }
        else {
            closed.push_back(cur);
            auto const& neighbours = gen_neighbours(cur);
            for (auto const &neighbour : neighbours) {
                if ((neighbour->get_g() < cur->get_g()) && std::find(std::begin(closed), std::end(closed), neighbour) != std::end(closed)) {
                    neighbour->set_parent(cur);
                } else if ((neighbour->get_g() > cur->get_g()) && open.find(neighbour) != open.end()) {
                    neighbour->set_parent(cur);
                } else if (open.find(neighbour) == open.end() && std::find(std::begin(closed), std::end(closed), neighbour) == std::end(closed)) {
                    open.push(neighbour);
                    // TODO: set it's g
                }
            }
        }
    }
}

int NPuzzleSolver::size = 0;
