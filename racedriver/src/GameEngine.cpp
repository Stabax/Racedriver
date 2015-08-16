#include <GameEngine.hpp>

GameEngine::GameEngine()
{
  extern sf::Vector2i	g_winsize;

  std::cout << "Initializing Game, please wait...\n";
  g_winsize.x = 1024;
  g_winsize.y = 768;
  _win.setPosition(sf::Vector2i(10, 10));
  createWindow(false);
  _win.setKeyRepeatEnabled(false);
  _win.setFramerateLimit(90);
  _gameState = SMenu;
  _prevIndex = 0;
  _menuIndex = 0;
  _ambiant.init(true);
}

GameEngine::~GameEngine()
{

}

bool GameEngine::initialize()
{
  _menus = std::vector<Menu *>();
  _menus.push_back(new MainMenu());
  _menus.push_back(new ProfileMenu());
  _menus.push_back(new SettingsMenu());
  return (true);
}

void GameEngine::createWindow(bool fullscreen)
{
  extern sf::Vector2i g_winsize;

  if (_win.isOpen() == true)
    _win.close();
  if (fullscreen == true)
    _win.create(sf::VideoMode(g_winsize.x, g_winsize.y, 32), "RaceDriver", sf::Style::Fullscreen);
  else
    _win.create(sf::VideoMode(g_winsize.x, g_winsize.y, 32), "RaceDriver", sf::Style::Titlebar);
}

MusicBox &GameEngine::getMusicBox()
{
  return (_ambiant);
}

bool GameEngine::updateGame()
{
  return (true);
}

bool GameEngine::updateMenu(sf::Event event)
{
  int status;

  if (_menuIndex != Settings)
  {
    if ((status = _menus[_menuIndex]->update(event)) >= 0)
      _menuIndex = status;
  }
  else
  {
    if ((status = reinterpret_cast<SettingsMenu *>(_menus[_menuIndex])->update(event, *this)) >= 0)
      _menuIndex = status;
  }
  if (status == -2)
    return (false);
  return (true);
}

bool GameEngine::update()
{
  sf::Event	event;

  _ambiant.update();
  while (_win.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      _win.close();
      return (false);
    }
    switch (_gameState)
    {
      case SMenu:
        if (updateMenu(event) == false)
          return (false);
        break;
      case SGame:
        if (updateGame() == false)
          return (false);
        break;
    }
  }
  return (true);
}

void GameEngine::drawGame()
{

}

void GameEngine::draw()
{
  _win.clear();
  switch (_gameState)
    {
    case SMenu:
      _menus[_menuIndex]->draw(_win);
      break;
    case SGame:
      drawGame();
      break;
    }
  _win.display();
}
