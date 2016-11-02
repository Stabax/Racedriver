#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
  Menu();
  ~Menu();

  bool loadFromFile();

  void connectSlots(/* VARARGS*/);

  bool buildTitle();
  bool buildItems();
  void checkOverflow();
  
  bool update();
  void draw();
  
protected:
  int _cursor, _itemcount;
  std::vector<sf::Text> _items;
  sf::Font _font;
  sf::Sprite _background;
};

#endif /* !MENU_HPP_ */
