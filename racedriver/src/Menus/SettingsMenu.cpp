#include <Menus/SettingsMenu.hh>

SettingsMenu::SettingsMenu() : OptionsMenu("truckdriver", 50, "carbon", "graphite")
{
  extern sf::Vector2i g_winsize;
  std::vector<std::string> items = {"Resolution", "Fullscreen", "Back"};
  std::vector<std::pair<std::vector<std::string>, int>> values;
  std::vector<std::string> iovalue = {"On", "Off"};
  std::vector<std::string> empty = {""};
  sf::Rect<int> pos = {(g_winsize.x / 2) - 225, 150, 450, 500};

  std::vector<std::string> resolution = {"1024x768", "1336x768", "1600x900", "1920x1080"};
  values.push_back(std::make_pair(resolution, 0));
  values.push_back(std::make_pair(iovalue, 0));
  values.push_back(std::make_pair(empty, 0));
  initLabel("Settings Menu", items, values);
  setPosition(pos, false);
}

SettingsMenu::~SettingsMenu()
{

}

int SettingsMenu::update(sf::Event event)
{
  updateNav(event);
  if (event.type == sf::Event::KeyPressed
      && event.key.code == sf::Keyboard::Return)
    {
      switch (_cursor)
      {
        case 0:
          break;
        case 1:
          break;
        case 2:
          return (0);
          break;
      }
    }
	return (-1);
}

void SettingsMenu::draw(sf::RenderWindow &win)
{
  drawNav(win);
}
