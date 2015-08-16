#include <Menus/SettingsMenu.hh>

SettingsMenu::SettingsMenu() : OptionsMenu("truckdriver", 50, "carbon", "graphite")
{
  extern sf::Vector2i g_winsize;

  std::vector<std::string> items = {"Resolution", "Fullscreen", "Music", "Back"};
  std::vector<std::pair<std::vector<std::string>, int>> values;
  std::vector<std::string> iovalue = {"On", "Off"};
  std::vector<std::string> empty = {""};
  sf::Rect<int> pos = {(g_winsize.x / 2) - 225, 150, 450, 500};
  std::vector<sf::VideoMode> vmodes = sf::VideoMode::getFullscreenModes();
  float scratio = static_cast<float>(sf::VideoMode::getDesktopMode().width / sf::VideoMode::getDesktopMode().height);
  std::vector<std::string> resolutions;

  for (size_t i = 0; i < vmodes.size(); i++)
  {
    if (vmodes[i].isValid() && vmodes[i].height >= 600 && scratio == static_cast<float>(vmodes[i].width / vmodes[i].height))
       resolutions.push_back(std::to_string(vmodes[i].width)+"x"+std::to_string(vmodes[i].height));
  }
  values.push_back(std::make_pair(resolutions, 0));
  values.push_back(std::make_pair(iovalue, 0));
  values.push_back(std::make_pair(iovalue, 0));
  values.push_back(std::make_pair(empty, 0));
  initLabel("Settings Menu", items, values);
  setPosition(pos, false);
}

SettingsMenu::~SettingsMenu()
{

}

void SettingsMenu::setResolution(GameEngine &game)
{
  extern sf::Vector2i g_winsize;
  std::string res = _values[_cursor].first[_hcursor];

  g_winsize.x = atoi((res.substr(0, res.find("x"))).c_str());
  g_winsize.y = atoi((res.substr(res.find("x") + 1, res.length())).c_str());
  game.createWindow(false);
  game.initialize();
}

void SettingsMenu::fullscreenToggle(GameEngine &game)
{
  if (_hcursor == 1)
    game.createWindow(false);
  else
    game.createWindow(true);
}

void SettingsMenu::musicToggle(GameEngine &game)
{
  if (_hcursor == 1)
    game.getMusicBox().toggle(false);
  else
    game.getMusicBox().toggle(true);
}

int SettingsMenu::update(sf::Event event)
{
  static_cast<void>(event);
  return (0);
}

int SettingsMenu::update(sf::Event event, GameEngine &game)
{
  updateNav(event);
  if (event.type == sf::Event::KeyPressed
      && event.key.code == sf::Keyboard::Return)
    {
      switch (_cursor)
      {
        case 0:
          setResolution(game);
          break;
        case 1:
          fullscreenToggle(game);
          break;
        case 2:
          musicToggle(game);
          break;
        case 3:
          return (Main);
          break;
      }
    }
	return (-1);
}

void SettingsMenu::draw(sf::RenderWindow &win)
{
  drawNav(win);
}
