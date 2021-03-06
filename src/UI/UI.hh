#pragma once

#include "common.hh"
#include "log.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

constexpr int width{740}, height{360};

class UI {
public:
  UI(visual_data data);
  void start();

private:
  bool poll();
  void decrement_state();
  void increment_state();
  void draw_state_box();
  void draw_info();
  void draw_rect(int i_x, int i_y, int num);
  void display_text(const string &str, float x, float y, int style = 0);

  RenderWindow win;
  Event event;
  Font font;
  Text text;
  RectangleShape shape;

  float info_x;
  float info_spacing;

  float offset_x;
  float offset_y;
  float board_size_px;

  float rect_size;
  float rect_origin;
  float box_offset_x;
  float box_offset_y;

  int sum_opened;
  int max_active;
  int states_size;
  int board_size_elems;
  vector<vector<vector<int>>> states;

  int current_state{0};
};
