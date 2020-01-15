
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
  text.setStyle(0);
  
  // sum_opened:
  float y = info_box_spacing;
  text.setPosition({info_box_x, y});
  text.setString(string("Total number of states: ") + to_string(sum_opened));
  win.draw(text);
  
  y += info_box_spacing;
  text.setPosition({info_box_x, y});
  text.setString(string("Maximum states in memory: ") + to_string(max_active));
  win.draw(text);
  
  y += info_box_spacing;
  text.setPosition({info_box_x, y});
  text.setString(string("Solution length: ") + to_string(states_size));
  win.draw(text);
  
  y += info_box_spacing;
  text.setPosition({info_box_x, y});
  text.setString(string("Current state: ") + to_string(current_state));
  win.draw(text);
  
  text.setStyle(Text::Bold);
  y += info_box_spacing * 2;
  text.setPosition({info_box_x, y});
  text.setString("Controls: use left and right arrows");
  win.draw(text);
  text.setStyle(0);
}