#include "Input.hh"
#include "Terminal.hh"

Input::Input()
 : InputManager()
{

}

Input::~Input()
{

}

InputManager::Keys Input::getInput()
{
  switch (getch())
  {
    case KEY_LEFT:
      return (InputManager::Keys::Left);
      break;
    case KEY_RIGHT:
      return (InputManager::Keys::Right);
      break;
    case KEY_UP:
      return (InputManager::Keys::Up);
      break;
    case KEY_DOWN:
      return (InputManager::Keys::Down);
      break;
    case KEY_ENTER:
    case '\n':
    case '\r':
      return (InputManager::Keys::Enter);
      break;
    case KEY_BACKSPACE:
    case '\b':
      return (InputManager::Keys::Backspace);
      break;
  }
  return (InputManager::Keys::None);
}