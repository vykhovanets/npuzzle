#pragma once

#include "common.hh"

#include <memory>
#include <vector>

using Snapshot = std::vector<std::vector<int>>;

class State {
    public:
        State(const Snapshot& data, std::shared_ptr<State> parent, const point& blank);

        void set_parent(std::shared_ptr<State> new_parent);

        std::vector<int>& operator[](int pos);

        point get_blank_pos() const;

        std::shared_ptr<State> get_parent() const;

        unsigned get_g() const;

        double get_h() const;

        double get_f() const;

        const Snapshot& get_snap() const;

        void dump_state() const;

        static void set_final_state(std::vector<point> fs);

    private:
        double manhattan_distance() const;
        std::shared_ptr<State> parent_;
        Snapshot data_;
        point blank_;
        unsigned g_;
        double f_;
        double h_;
        static std::vector<point> final_state_;
};

