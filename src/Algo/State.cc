#include "State.hh"
#include <cmath>
#include <iostream>

State::State(const Snapshot& data, std::shared_ptr<State> parent, const point& blank)
: parent_(parent), data_(data), blank_(blank) {
    update_heuristics(); //TODO: replace
}

void State::set_parent(std::shared_ptr<State> new_parent) {
    parent_ = new_parent;
    update_heuristics();
}

std::vector<int>& State::operator[](int pos) {
    return data_[pos];
}

//TODO: i'm so ugly
void State::set_blank(const point& p) {
    blank_ = p;
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
    h_ = manhattan_distance();
    f_ = g_ + h_;
}

void State::dump_state() const {
    for (auto const& row : data_) {
        for (auto const& el : row) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
}

void State::set_final_state(std::vector<point> fs) {
    State::final_state_ = fs;
}

double State::manhattan_distance() const {
    unsigned mark = 0;
    for (int y = 0; y < data_.size(); ++y) {
        for (int x = 0; x < data_[y].size(); ++x) {
            auto const& final_num_pos = State::final_state_[data_[y][x]];
            mark += std::abs(y - final_num_pos.y) + std::abs(x - final_num_pos.x);
        }
    }
    return mark;
}

std::vector<point> State::final_state_ = {};
