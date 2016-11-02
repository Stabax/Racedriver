#include <iostream>
#include "Game.hh"

Console::Console(sf::RenderWindow &win)
{
  int width = win.getSize().x;
  _height = win.getSize().y / 3;
  _margin = 7;
  
  _open = false;
  _font.loadFromFile(FONTFILE);
  _inputText.setFont(_font);
  _inputText.setCharacterSize(10);
  _inputText.setPosition(10, _height - 20);
  _geometry.push_back(sf::RectangleShape(sf::Vector2f(width, _height))); //Frame
  _geometry[0].setPosition(0, 0);
  _geometry[0].setFillColor(sf::Color(0, 51, 51, 200));
  _geometry.push_back(sf::RectangleShape(sf::Vector2f(width - 10, _height - 45))); //Content
  _geometry[1].setPosition(5, 5);
  _geometry[1].setFillColor(sf::Color(0, 102, 102, 180));
  _geometry.push_back(sf::RectangleShape(sf::Vector2f(width - 10, 30))); //Input box
  _geometry[2].setPosition(5, _height - 35);
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
  if (_margin + (FONTSIZE * _output.size()) < (_height - 45))
    _output.back().setPosition(sf::Vector2f(_margin, _margin + (FONTSIZE * _output.size())));
}

void Console::exec(std::string cmd)
{
  if (cmd == "exit")
    toggle();
}

void Console::grabInput(sf::Event &event)
{
  if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
    _input += static_cast<char>(event.key.code + 97);
  else if (event.key.code == sf::Keyboard::BackSpace && _input.size() > 0)
    _input.pop_back();
  else if (event.key.code == sf::Keyboard::Return)
    {
      _history.push_back(_input);
      writeLine(_input);
      exec(_input);
      _input.clear();
    }
}

bool Console::update(sf::Event &event)
{
  grabInput(event);
  _inputText.setString(_input);
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
  engine.win.draw(_inputText);
}
