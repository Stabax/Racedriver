#ifndef OPTIONSMENU_HH_
#define OPTIONSMENU_HH_

#include <Menus/Menu.hh>

class OptionsMenu : public Menu
{
public:
  OptionsMenu(std::string font, int csize, std::string bg, std::string nav);
  ~OptionsMenu();

  float getBiggestWidth() const;
  void setPosition(sf::Rect<int> pos, bool center);

  void initLabel(std::string title, std::vector<std::string> items, std::vector<std::pair<std::vector<std::string>, int> > values);

  void updateNav(sf::Event event);

  virtual int update(sf::Event event) = 0;
  virtual void draw(sf::RenderWindow &win) = 0;

protected:
  std::vector<std::pair<std::vector<std::string>, int> > _values;
  std::vector<std::string>                              _stritems;
  int                                                   _hcursor;
};

#endif
