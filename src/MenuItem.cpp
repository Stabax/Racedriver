#include "MenuItem.hh"
#include "ScriptEngine.hh"
#include "Menu.hh"

//MenuItem

MenuItem::MenuItem(xml_node &data)
 : _id(data.attribute("id").value()), _label(data.first_child().value())
{
}

MenuItem::MenuItem(std::string label)
 : _label(label)
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

void MenuItem::select()
{
  throw(std::runtime_error("MenuItem should not be selected"));
}

void MenuItem::render()
{
  Terminal::get() << _label << "\n";
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
    Menu::Goto(_target);
    break;
  case Script:
    ScriptEngine::run(_target);
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

void MenuInput::render()
{
  MenuItem::render();
  //Implement logic
}