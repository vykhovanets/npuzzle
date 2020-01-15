#pragma once

#include "log.hh"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

using std::vector;
using namespace sf;

struct visual_data {
  int sum_opened_elems{0};   // complexity in time
  int max_active_elems{0};   // complexity in size
  int states_size{0};        // number of states in a solution
  vector<vector<int>> state; // should be a list or vector of states
};

constexpr int width{740}, height{360};

class UI {
public:
  UI(visual_data data);
  void start();
  
private:
  bool poll();
  void draw_state_box();
  void draw_info_box();
  void display_text(const string& str, float x, float y,  int style = 0);
  
  RenderWindow win;
  Event event;
  Font font;
  Text text;
  
  float info_box_x;
  float info_box_spacing;
  
  float state_box_offset_x;
  float state_box_offset_y;
  
  int sum_opened;
  int max_active;
  int states_size;
  vector<vector<int>> state;
  
  int current_state{0};
};
