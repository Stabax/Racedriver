#include "Game.hh"

Console::Console(sf::RenderWindow &win)
{
  int width = win.getSize().x;
  int height = win.getSize().y / 3;
  _margin = 7;
  
  _open = false;
  _font.loadFromFile(FONTFILE);
  _geometry.push_back(sf::RectangleShape(sf::Vector2f(width, height))); //Frame
  _geometry[0].setPosition(0, 0);
  _geometry[0].setFillColor(sf::Color(0, 51, 51, 200));
  _geometry.push_back(sf::RectangleShape(sf::Vector2f(width - 10, height - 45))); //Content
  _geometry[1].setPosition(5, 5);
  _geometry[1].setFillColor(sf::Color(0, 102, 102, 180));
  _geometry.push_back(sf::RectangleShape(sf::Vector2f(width - 10, 30))); //Input box
  _geometry[2].setPosition(5, height - 35);
  _geometry[2].setFillColor(sf::Color(0, 102, 102, 180));
}

Console::~Console()
{

}

void Console::toggle()
{
  _open = !_open;
}

bool Console::isOpen()
{
  return (_open);
}

void Console::clear()
{
  _output.clear();
}

void Console::writeLine(std::string str)
{
  _output.push_back(sf::Text(str, _font, FONTSIZE));
  positionOutput();
}

void Console::positionOutput()
{
  _output.back().setPosition(sf::Vector2f(_margin, _margin + (FONTSIZE * _output.size())));
}

void Console::grabInput(sf::Event &event)
{
}

bool Console::update(sf::Event &event)
{
  grabInput(event);
  return (true);
}

void Console::draw(t_engine &engine)
{
  if (!_open)
    return;
  for (size_t i = 0; i < _geometry.size(); i++)
    engine.win.draw(_geometry[i]);
  for (size_t i = 0; i < _output.size(); i++)
    engine.win.draw(_output[i]);
}
