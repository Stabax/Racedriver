#include "Input.hh"
#include "Terminal.hh"

Input::Input()
 : InputManager()
{

}

Input::~Input()
{

}

Key Input::getInput()
{
  switch (getch())
  {
    case KEY_LEFT:
      return (Key(Key::Code::Left));
    case KEY_RIGHT:
      return (Key(Key::Code::Right));
    case KEY_UP:
      return (Key(Key::Code::Up));
    case KEY_DOWN:
      return (Key(Key::Code::Down));
      break;
    case KEY_ENTER:
    case '\n':
    case '\r':
      return (Key(Key::Code::Down));
    case KEY_BACKSPACE:
    case '\b':
      return (Key(Key::Code::Backspace));
  }
  return (Key());
}