#pragma once

struct point {
  int y, x;
};

struct visual_data {
  int sum_opened_elems{0};   // complexity in time
  int max_active_elems{0};   // complexity in size
  int states_size{0};        // number of states in a solution
  int board_size{0};
  vector<vector<int>> state; // should be a list or vector of states
};