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
      if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        std::string entry = ent->d_name;
        items.push_back(entry.substr(0, entry.find(".")));
      }
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
      if (static_cast<unsigned int>(_cursor) == _items.size() - 1)
        return (Main);
      else if (static_cast<unsigned int>(_cursor) == _items.size() - 2)
        return (NewProfile);
      else
        {
          /*load profile*/
        }
    }
	return (-1);
}

void ProfileMenu::draw(sf::RenderWindow &win)
{
  drawNav(win);
}
