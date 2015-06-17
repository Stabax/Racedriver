#ifndef MENU_HH_
#define MENU_HH_

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Menu
{
public:
  Menu(std::string title, std::vector<std::string> items, std::string font);
  ~Menu();

  bool update(sf::Event);
  void draw(sf::RenderWindow &);

private:
  sf::Font			_font;
  int				_cursor;
  sf::Text			_title;
  std::vector<sf::Text>		_items;

};

#endif
