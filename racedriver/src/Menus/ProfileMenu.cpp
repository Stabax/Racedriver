#include <Menus/ProfileMenu.hh>

ProfileMenu::ProfileMenu() : Menu("truckdriver", 50, "carbon", "graphite")
{
  extern Pipeline g_pipeline;
  extern sf::Vector2i g_winsize;
  std::vector<std::string> items = {"New Profile", "Quit"};
  sf::Rect<int> pos = {(g_winsize.x / 2) - 150, 200, 300, 400};
  struct dirent *ent;
  std::string path = "./"+g_pipeline.getPath("saves");
  DIR *dir;

  if ((dir = opendir(path.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
      items.push_back(std::string(ent->d_name));
  }
  std::rotate(items.begin(), items.begin() + 2, items.end());
  closedir (dir);
  initLabel("Choose a Profile", items);
  setPosition(pos, true);
}

ProfileMenu::~ProfileMenu()
{

}

int ProfileMenu::update(sf::Event event)
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

void ProfileMenu::draw(sf::RenderWindow &win)
{
  drawNav(win);
}
