#include "Menu.hh"

Menu::Menu(std::string title, std::vector<std::string> items) : _title(title), _items(items)
{
  _cursor = 0;
}

Menu::~Menu()
{

}

bool Menu::update()
{
  if (_cursor < 0)
    _cursor = static_cast<unsigned int>(_items.size() - 1);
  else if (static_cast<unsigned int>(_cursor) >= _items.size())
    _cursor = 0;
  return (true);
}

void Menu::draw()
{

}
