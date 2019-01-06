#include "MenuItem.hh"
#include "ScriptEngine.hh"

//MenuItem

MenuItem::MenuItem(xml_node &data)
 : _id(data.attribute("id").value()), _label(data.value())
{
}

std::shared_ptr<MenuItem> MenuItem::create(xml_node &data)
{
  if (strcmp(data.name(), "Button") == 0)
  {
    return (std::make_shared<MenuButton>(data));
  }
  else if (strcmp(data.name(),"Input") == 0)
  {
    return (std::make_shared<MenuInput>(data));
  }
  else throw(std::runtime_error("Error in XML"));
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
    //menu with id _target
    break;
  case Script:
    //ScriptEngine::run(); script with id _target
    break;
  }
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

std::string MenuInput::getData()
{
  return (_data);
}