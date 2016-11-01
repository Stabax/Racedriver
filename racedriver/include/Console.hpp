#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

typedef struct s_engine t_engine;

class Console
{
public:
  Console(sf::RenderWindow &win);
  ~Console();

  //Display
  void show();
  void hide();
  void toggle();

  //Output
  void clear();

  //State
  bool isOpen();

  //Logic
  bool update();
  void draw(t_engine &engine);
  
private:
  bool _open;
  std::vector<sf::RectangleShape> _geometry;
  std::vector<std::string> _history;
};

#endif /* !CONSOLE_HPP_ */
