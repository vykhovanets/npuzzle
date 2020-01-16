
#include "UI.hh"

UI::UI(visual_data data)
  : win{{width, height}, "n-puzzle"}
  , info_x{width - 380}
  , info_spacing{30}
  , offset_x{30}
  , offset_y{30}
  , board_size_px{300}
  , sum_opened{data.sum_opened_elems}
  , max_active{data.max_active_elems}
  , states_size{data.states_size}
  , board_size_elems{data.board_size}
  , states{std::move(data.state)} {
    
    win.setFramerateLimit(60);
    font.loadFromFile("data/CaviarDreams.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    
    rect_size = board_size_px / board_size_elems;
    rect_origin = rect_size / 2;
    box_offset_x = offset_x + rect_origin;
    box_offset_y = offset_y + rect_origin;
    
    shape.setSize({rect_size - 2, rect_size - 2});
    shape.setOrigin(rect_origin, rect_origin);
}

// .:: public

void UI::start() {
  while (poll()) {
    win.clear(Color::Black);
    
    draw_info();
    draw_state_box();
    win.display();
  }
}

// .:: private

bool UI::poll() {
  while (win.pollEvent(event)) {
    if (event.type == Event::Closed or
       (event.type == Event::KeyPressed and event.key.code == Keyboard::Escape))
      return false;
    else if (event.type == Event::KeyPressed and event.key.code == Keyboard::Left)
      decrement_state();
    else if (event.type == Event::KeyPressed and event.key.code == Keyboard::Right)
      increment_state();
    break;    
  }
  return true;
}

void UI::decrement_state() {
  if (current_state - 1 >= 0)
    current_state--;
}

void UI::increment_state() {
  if (current_state + 1 < states_size)
    current_state++;
}

void UI::draw_state_box() {
  auto& state = states;  // TODO: current_state as an index in vector of states;
  
  for (int y{0}; y < board_size_elems; y++) {
    for (int x{0}; x < board_size_elems; x++) {
      draw_rect(x, y, state[y][x]);
    }
  }
}

void UI::draw_rect(int i_x, int i_y, int num) {
  shape.setPosition(box_offset_x + rect_size * i_x, box_offset_y + rect_size * i_y);
  shape.setFillColor(num != 0 ? Color::Red : Color::Black);
  
  // a little ugliness here :)
  text.setCharacterSize(rect_size / 3);
  text.setFillColor(num != 0 ? Color::White : Color::Black);
  text.setString(to_string(num));
  text.setOrigin(rect_size / 4, rect_size / 4);
  text.setPosition(box_offset_x + rect_size * i_x, box_offset_y + rect_size * i_y);
  
  win.draw(shape);
  win.draw(text);
}

void UI::draw_info() {
  text.setCharacterSize(20);
  text.setFillColor(Color::White);
  
  float y = info_spacing;
  display_text(string("Total number of states: ") + to_string(sum_opened), info_x, y);
  
  y += info_spacing;
  display_text(string("Maximum states in memory: ") + to_string(max_active), info_x, y);
  
  y += info_spacing;
  display_text(string("Solution length: ") + to_string(states_size), info_x, y);
  
  y += info_spacing;
  display_text(string("Current state: ") + to_string(current_state), info_x, y);
  
  y += info_spacing * 2;
  display_text("Controls: use left and right arrows", info_x, y, Text::Bold);
}

void UI::display_text(const string& str, float x, float y,  int style) {
  text.setStyle(style);
  text.setOrigin(0, 0);
  text.setPosition({x, y});
  text.setString(str);
  win.draw(text);
  text.setStyle(0);
}