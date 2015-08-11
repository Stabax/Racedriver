#include <Menus/MainMenu.hh>

MainMenu::MainMenu() : Menu("truckdriver", 50, "carbon", "graphite")
{
  extern sf::Vector2i g_winsize;
  std::vector<std::string> items = {"Play", "Options", "Quit"};
  sf::Rect<int> pos = {(g_winsize.x / 2) - 150, 200, 300, 400};

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
          return (1);
          break;
        case 1:
          return (2);
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
