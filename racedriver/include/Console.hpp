#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define FONTSIZE	10
#define FONTFILE	"./Data/font/console.ttf"

typedef struct s_engine t_engine;

class Console
{
public:
  Console(sf::RenderWindow &win);
  ~Console();

  //Display
  void toggle();

  //State
  bool isOpen();

  //Output
  void clear();
  void writeLine(std::string str);
  void positionOutput();

  //Input
  void exec(std::string cmd);
  void grabInput(sf::Event &event);

  //Logic
  bool update(sf::Event &event);
  void draw(t_engine &engine);
  
private:
  bool _open;
  int _margin;
  unsigned int _height;
  sf::Font _font;
  std::vector<sf::RectangleShape> _geometry;
  std::vector<std::string> _history;
  std::vector<sf::Text> _output;
  sf::Text _inputText;
  std::string _input;
};

#endif /* !CONSOLE_HPP_ */
