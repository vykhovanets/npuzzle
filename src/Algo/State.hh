#pragma once

#include "common.hh"

#include <memory>
#include <vector>

using Snapshot = std::vector<std::vector<int>>;

class State {
    public:
        State(const Snapshot& data, std::shared_ptr<State> parent, const point& blank);

        bool operator==(const State& s2) const;

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
        static void set_heuristics(Heuristic h);

        void update_heuristics();

        void swap_elems(const point& p1, const point& p2);

    private:
        double manhattan_distance() const;
        double hamming_distance() const;
        //double diagonal_distance() const;
        double euclidean_distance() const;
        std::shared_ptr<State> parent_;
        Snapshot data_;
        point blank_;
        unsigned g_;
        double f_;
        double h_;
        static std::vector<point> final_state_;
        static Heuristic heuristics_type_;
        typedef double(State::*HFunc) () const;
        HFunc heuristic_;
};

