#include <Menus/MainMenu.hh>

MainMenu::MainMenu() : Menu("truckdriver", 50, "carbon")
{
  extern sf::Vector2i g_winsize;
  std::vector<std::string> items = {"Play", "Options", "Quit"};
  sf::Rect<int> pos = {0, 150, g_winsize.x, g_winsize.y - 400};

  initLabel("Main Menu", items);
  setPosition(pos, true);
}

MainMenu::~MainMenu()
{

}

int MainMenu::update(sf::Event event)
{
  updateNav(event);
  if (event.type == sf::Event::KeyPressed
      && event.key.code == sf::Keyboard::Return)
    {
      switch (_cursor)
      {
        case 0:
          return (0);
          break;
        case 1:
          return (1);
          break;
        case 2:
          return (-2);
          break;
      }
    }
	return (-1);
}

void MainMenu::draw(sf::RenderWindow &win)
{
  drawNav(win);
}
