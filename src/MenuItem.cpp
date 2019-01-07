#include "MenuItem.hh"
#include "ScriptEngine.hh"
#include "Menu.hh"

//MenuItem

MenuItem::MenuItem(xml_node &data)
 : _id(data.attribute("id").value()), _label(data.first_child().value()), _hover(false)
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

void MenuItem::select()
{
  throw(std::runtime_error("MenuItem should not be selected"));
}

void MenuItem::render()
{
  if (_hover) Terminal::get() << setColor(Terminal::Color::RedOnBlack);
  Terminal::get() << _label << "\n";
  if (_hover) Terminal::get() << resetAttrs();
}

//MenuButton

MenuButton::MenuButton(xml_node &data)
 : MenuItem(data), _target()
{

}

void MenuButton::select()
{
  switch (_type)
  {
  case Goto:
    Menu::goTo("", _target);
    break;
  case Script:
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
  char input;

  while ((input = getch()) != '\n')
  {
    if (input == '\b') _data.erase(--_data.end());
    else _data += input;
  }
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
  //Implement logic
}