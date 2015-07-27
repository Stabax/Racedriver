#ifndef MENU_HH_
#define MENU_HH_

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Pipeline.hpp>
#include <MenuHandle.hh>

class Menu
{
public:
  Menu(std::string title, std::vector<std::pair<std::string, int (MenuHandle::*)()>> items, std::string font, std::string bg);
  ~Menu();

  int update(sf::Event, MenuHandle *handle);
  void draw(sf::RenderWindow &);

private:
  sf::Sprite				_background;
  int					_cursor;
  sf::Text				_title;
  std::vector<sf::Text>			_items;
  std::vector<int (MenuHandle::*)()>	_funcs;

};

#endif
