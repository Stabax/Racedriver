#ifndef MENU_HH_
#define MENU_HH_

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Pipeline.hpp>

#define TITLE_FACTOR  1.75
#define TITLE_Y       10

/* function used to center drawables texts on screen */
inline float centerText(sf::Text &obj, char direction)
{
  extern sf::Vector2i	g_winsize;

  if (direction == 'X')
    return ((g_winsize.x / 2) - (obj.getLocalBounds().width / 2));
  else if (direction == 'Y')
    return ((g_winsize.y / 2) - (obj.getLocalBounds().height / 2));
  return (0);
}

class Menu
{
public:
  Menu(std::string font, int csize, std::string bg);
  ~Menu();

  void initLabel(std::string title, std::vector<std::string> items);
  void setPosition(sf::Rect<int> pos, bool center = true);

  void updateNav(sf::Event event);
  void drawNav(sf::RenderWindow &win);

  virtual int update(sf::Event event) = 0;
  virtual void draw(sf::RenderWindow &win) = 0;

protected:
  sf::Sprite                _background;
  std::vector<sf::Text>			_items;
  sf::Text				          _title;
  sf::Rect<int>             _position;
  int					              _cursor;
};

#endif
