#ifndef MENU_HH_
#define MENU_HH_

#include <vector>
#include <string>

class Menu
{
public:
  Menu(std::string title, std::vector<std::string> items);
  ~Menu();

  bool update();
  void draw();

private:
  int				_cursor;
  std::string			_title;
  std::vector<std::string>	_items;

};

#endif
