
#include "UI.hh"

UI::UI(visual_data data)
  : win{{width, height}, "n-puzzle"}
  , info_box_x(width - 380)
  , info_box_spacing(30)
  , sum_opened(data.sum_opened_elems)
  , max_active(data.max_active_elems)
  , states_size(data.states_size)
  , state(std::move(data.state)) {
    
    win.setFramerateLimit(60);
    font.loadFromFile("data/CaviarDreams.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
}

void UI::start() {
  while (poll()) {
    win.clear(Color::Black);
    
    draw_info_box();
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
    break;    
  }
  return true;
}

void UI::draw_state_box() {
  
  
}

void UI::draw_info_box() {
  text.setCharacterSize(20);
  text.setFillColor(Color::White);
  
  float y = info_box_spacing;
  display_text(string("Total number of states: ") + to_string(sum_opened), info_box_x, y);
  
  y += info_box_spacing;
  display_text(string("Maximum states in memory: ") + to_string(max_active), info_box_x, y);
  
  y += info_box_spacing;
  display_text(string("Solution length: ") + to_string(states_size), info_box_x, y);
  
  y += info_box_spacing;
  display_text(string("Current state: ") + to_string(current_state), info_box_x, y);
  
  y += info_box_spacing * 2;
  display_text("Controls: use left and right arrows", info_box_x, y, Text::Bold);
}

void UI::display_text(const string& str, float x, float y,  int style) {
  text.setStyle(style);
  text.setPosition({x, y});
  text.setString(str);
  win.draw(text);
  text.setStyle(0);
}