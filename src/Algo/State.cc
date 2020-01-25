#include "State.hh"
#include <cmath>
#include <iostream>
#include <exception>

State::State(const Snapshot& data, std::shared_ptr<State> parent, const point& blank)
: parent_(parent), data_(data), blank_(blank) {
    switch(State::heuristics_type_) {
        case Heuristic::MANHATTAN:
            heuristic_ = &State::manhattan_distance;
            break;
        case Heuristic::HAMMING:
            heuristic_ = &State::hamming_distance;
            break;
        case Heuristic::EUCLIDEAN:
            heuristic_ = &State::euclidean_distance;
            break;
        default:
            std::logic_error("Unsupported heuristic");
    }
    update_heuristics(); //TODO: replace
}

bool State::operator==(const State& s2) const {
    return data_ == s2.data_;
}

void State::set_parent(std::shared_ptr<State> new_parent) {
    parent_ = new_parent;
    update_heuristics();
}

std::vector<int>& State::operator[](int pos) {
    return data_[pos];
}

void State::swap_elems(const point& p1, const point& p2) {
    if (data_[p1.y][p1.x] == 0) {
        blank_.y = p2.y;
        blank_.x = p2.x;
    } else if (data_[p2.y][p2.x] == 0) {
        blank_.y = p1.y;
        blank_.x = p1.x;
    } else {
        throw std::logic_error("Invalid swap, invalid game move");
    }
    std::swap(data_[p1.y][p1.x], data_[p2.y][p2.x]);
    update_heuristics();
}

point State::get_blank_pos() const {
    return blank_;
}

std::shared_ptr<State> State::get_parent() const {
    return parent_;
}

unsigned State::get_g() const {
    return g_;
}

double State::get_h() const {
    return h_;
}

double State::get_f() const {
    return f_;
}

const Snapshot& State::get_snap() const {
    return data_;
}

void State::update_heuristics() {
    if (parent_) {
        g_ = parent_->get_g() + 1;
    } else {
        g_ = 0;
    }
    h_ = (this->*heuristic_)();
    f_ = g_ + h_;
}

void State::dump_state() const {
    std::cout << "--------------" << std::endl;
    std::cout << "h = " << h_ << std::endl;
    std::cout << "g = " << g_ << std::endl;
    std::cout << "f = " << f_ << std::endl;
    for (auto const& row : data_) {
        for (auto const& el : row) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------" << std::endl;
}

void State::set_final_state(std::vector<point> fs) {
    State::final_state_ = fs;
}

void State::set_heuristics(Heuristic h) {
    State::heuristics_type_ = h;
}

double State::euclidean_distance() const {
    unsigned mark = 0;
    double d{1};
    for (int y = 0; y < data_.size(); ++y) {
        for (int x = 0; x < data_[y].size(); ++x) {
            // ignore zero
            if (data_[y][x]) {
                auto const& final_num_pos = State::final_state_[data_[y][x]];
                int dx = std::abs(x - final_num_pos.x);
                int dy = std::abs(y - final_num_pos.y);
                mark += std::sqrt(dx * dx + dy * dy);
            }
        }
    }
    return d * mark;
}

/*
double State::diagonal_distance() const {
    unsigned mark = 0;
    double d1{1};
    double d2{std::sqrt(2)};
    for (int y = 0; y < data_.size(); ++y) {
        for (int x = 0; x < data_[y].size(); ++x) {
            // ignore zero
            if (data_[y][x]) {
                auto const& final_num_pos = State::final_state_[data_[y][x]];
                int dx = std::abs(x - final_num_pos.x);
                int dy = std::abs(y - final_num_pos.y);
                mark += d2 * (dx + dy) + (d2 - 2 * d1) * std::min(dx, dy);
            }
        }
    }
    return mark;
}
*/

double State::manhattan_distance() const {
    unsigned mark = 0;
    for (int y = 0; y < data_.size(); ++y) {
        for (int x = 0; x < data_[y].size(); ++x) {
            // ignore zero
            if (data_[y][x]) {
                auto const& final_num_pos = State::final_state_[data_[y][x]];
                mark += std::abs(y - final_num_pos.y) + std::abs(x - final_num_pos.x);
            }
        }
    }
    return 2 * mark;
}

double State::hamming_distance() const {
    unsigned mark{0};
    for (int y = 0; y < data_.size(); ++y) {
        for (int x = 0; x < data_[y].size(); ++x) {
            // ignore zero
            if (data_[y][x]) {
                auto const& final_num_pos = State::final_state_[data_[y][x]];
                if ((final_num_pos.y != y) || (final_num_pos.x != x)) {
                    ++mark;
                }
            }
        }
    }
    return 2 * mark;
}

std::vector<point> State::final_state_ = {};
Heuristic State::heuristics_type_ = Heuristic::MANHATTAN;
