#include "NPuzzleSolver.hh"
#include <algorithm>
#include <set>
#include "MyPriorQueue.hh"

// TODO: i need to see the parent, to ignore repeating the states
// or not ?
// if it's already in the closed queue, then no
std::vector<std::shared_ptr<State>> NPuzzleSolver::gen_neighbours(
        const std::shared_ptr<State>& state) {
    int size = state->get_snap().size();
    const auto& parent = state->get_parent();
    point pre{-1, -1};
    if (parent) {
        pre = parent->get_blank_pos();
    }
    std::vector<std::shared_ptr<State>> neighbours;
    auto const& bpos = state->get_blank_pos();

    if ((bpos.x + 1 < size) && !(bpos.x + 1 == pre.x && bpos.y == pre.y)) {
        State next(*state);
        next.set_parent(state);
        next.swap_elems({bpos.y, bpos.x + 1}, {bpos.y, bpos.x});
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    if ((bpos.x - 1 >= 0) && !(bpos.x - 1 == pre.x && bpos.y == pre.y)) {
        State next(*state);
        next.set_parent(state);
        next.swap_elems({bpos.y, bpos.x - 1}, {bpos.y, bpos.x});
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    if ((bpos.y + 1 < size) && !(bpos.y + 1 == pre.y && bpos.x == pre.x)) {
        State next(*state);
        next.set_parent(state);
        next.swap_elems({bpos.y + 1, bpos.x}, {bpos.y, bpos.x});
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    if ((bpos.y - 1 >= 0) && !(bpos.y - 1 == pre.y && bpos.x == pre.x)) {
        State next(*state);
        next.set_parent(state);
        next.swap_elems({bpos.y - 1, bpos.x}, {bpos.y, bpos.x});
        next.dump_state();
        neighbours.push_back(std::make_shared<State>(std::move(next)));
    }
    return neighbours;
}

//TODO: =(
static point zero_finder(Snapshot snap) {
    for (int y{0}; y < snap.size(); ++y) {
        for (int x{0}; x < snap[y].size(); ++x) {
            if (snap[y][x] == 0) {
                return {.y=y, .x=x};
            }
        }
    }
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

visual_data NPuzzleSolver::convert_output(std::shared_ptr<State> last, int tc, int sc) {
    std::vector<Snapshot> result;
    result.push_back(last->get_snap());
    std::shared_ptr<State> runner = last;
    while (auto parent = runner->get_parent()) {
        result.insert(result.begin(), parent->get_snap());
        runner = parent;
    }
    return {tc, sc, result.size(), last->get_snap().size(),result};
}

visual_data NPuzzleSolver::a_star_solver(const Snapshot& initial) {
    std::shared_ptr<State> start_state = std::make_shared<State>(initial, nullptr, zero_finder(initial));
    auto comparator = [](auto lhs,auto rhs) { return lhs->get_f() > rhs->get_f(); };
    MyPriorQueue<std::shared_ptr<State>,std::vector<std::shared_ptr<State>>,decltype(comparator)> open(comparator);
    std::set<std::shared_ptr<State>> closed;
    int time_complexity{0};
    int size_complexity{0};

    open.push(start_state);
    ++time_complexity;
    ++size_complexity;

    //TODO: figure out the end condition
    auto find_in_closed = [&closed](const auto& neighbour) { return std::find(std::begin(closed), std::end(closed), neighbour) != std::end(closed); };
    auto find_in_opened = [&open](const auto& neighbour) { return open.find(neighbour) != open.end(); };

    while (true) {
        auto total_size = open.size() + closed.size();
        if (total_size > size_complexity) {
            size_complexity = total_size;
        }
        // prioritized by f
        auto cur = open.top();
        open.pop();
        if (!cur->get_h()) {
            // we are done
            return NPuzzleSolver::convert_output(cur, time_complexity, size_complexity);
        }
        else {
            closed.insert(cur);
            auto neighbours = gen_neighbours(cur);
            for (auto const &neighbour : neighbours) {
                if ((neighbour->get_g() < cur->get_g()) && find_in_closed(neighbour)) {
                    neighbour->set_parent(cur);
                } else if ((neighbour->get_g() > cur->get_g()) && find_in_opened(neighbour)) {
                    neighbour->set_parent(cur);
                } else if (!find_in_opened(neighbour) && !find_in_closed(neighbour)) {
                    open.push(neighbour);
                    ++time_complexity;
                    // TODO: set it's g
                }
            }
        }
    }
}
