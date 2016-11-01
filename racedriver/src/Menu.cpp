#include "Menu.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{

}

bool Menu::loadFromFile()
{
  return (false);
}

void Menu::checkOverflow()
{
  if (_cursor < 0)
    _cursor = _itemcount;
  else if (_cursor > _itemcount)
    _cursor = 0;
}

bool Menu::update()
{
  checkOverflow();
  return (true);
}

void Menu::draw()
{

}
