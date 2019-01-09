#include "MenuItem.hh"
#include "ScriptEngine.hh"
#include "Menu.hh"

//MenuItem

MenuItem::MenuItem(xml_node &data)
 : _id(data.attribute("Id").value()), _label(data.first_child().value()), _hover(false)
{
}

MenuItem::MenuItem(std::string label)
 : _label(label), _hover(false)
{
}

std::shared_ptr<MenuItem> MenuItem::create(xml_node &data)
{
  std::shared_ptr<MenuItem> el;

  if (strcmp(data.name(), "Text") == 0) el = std::make_shared<MenuItem>(data);
	else if (strcmp(data.name(), "Sep") == 0) el = std::make_shared<MenuItem>("======");
  else if (strcmp(data.name(), "Button") == 0)
  {
    el = std::make_shared<MenuButton>(data);
  }
  else if (strcmp(data.name(),"Input") == 0)
  {
    el = std::make_shared<MenuInput>(data);
  }
  else if (strcmp(data.name(),"Script") == 0)
  {
    ScriptEngine::run(data.first_child().value());
    return (nullptr);
  }
  else throw(std::runtime_error("Error in XML"));
  return (el);
}

void MenuItem::toggleHover()
{
  _hover = !_hover;
}

bool MenuItem::isSelectable()
{
  return (false);
}


const std::string &MenuItem::getId()
{
  return (_id);
}

void MenuItem::select()
{
  throw(std::runtime_error("MenuItem should not be selected"));
}

void MenuItem::render()
{
  if (_hover) Terminal::get() << setColor(Terminal::Color::RedOnBlack);
  Terminal::get() << _label;
  if (_hover) Terminal::get() << resetAttrs();
}

//MenuButton

MenuButton::MenuButton(xml_node &data)
 : MenuItem(data), _target(data.attribute("Target").value()), _path(data.attribute("Path").value())
{
  if (strcmp(data.attribute("Type").value(), "Goto") == 0) _type = Goto;
  else if (strcmp(data.attribute("Type").value(), "Script") == 0) _type = Script;
  else if (strcmp(data.attribute("Type").value(), "Intern") == 0) _type = Intern;
  else throw (std::runtime_error("Unknown button type"));
}

void MenuButton::select()
{
  switch (_type)
  {
  case Goto:
  {
    Menu::goTo(_target, _path);
    break;
  }
  case Script:
    ScriptEngine::runScript(_target);
    break;
  case Intern:
    ScriptEngine::run(_target);
    break;
  }
}

bool MenuButton::isSelectable()
{
  return (true);
}

//MenuInput

MenuInput::MenuInput(xml_node &data)
 : MenuItem(data)
{

}

void MenuInput::select()
{
  int input;

  Menu::active->render(); //Render once
  Terminal::get().setCursor(2); //Block cursor
  Terminal::get().setCursorPos(_dataPos); //set cursor at end of input
  while ((input = getch()) != KEY_ENTER && input != '\r' && input != '\n')
  {
    if (_data.length() > 0 && (input == KEY_BACKSPACE || input == '\b')) _data.erase(--_data.end());
    else _data += input;
    Terminal::get().clearScreen();
    Menu::active->render(); //Request render to update input
    Terminal::get().setCursorPos(_dataPos); //set cursor at end of input
  }
  Terminal::get().clearScreen(); //Clear screen for menu redraw
  Terminal::get().setCursor(0); //Disable cursor
}

bool MenuInput::isSelectable()
{
  return (true);
}

std::string MenuInput::getData()
{
  return (_data);
}

void MenuInput::render()
{
  MenuItem::render();
  Terminal::get() << ": " + _data;
  _dataPos = Terminal::get().getCursorPos();
}