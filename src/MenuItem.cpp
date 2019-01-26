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
  else if (strcmp(data.name(),"Select") == 0)
  {
    el = std::make_shared<MenuSelect>(data);
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
  case Cpp:
    _cppCallback();
    break;
  }
}

bool MenuButton::isSelectable()
{
  return (true);
}

void MenuButton::bind(std::function<void(void)> &callback)
{
  _type = Cpp;
  _cppCallback = callback;
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

void MenuInput::setData(const std::string data)
{
  _data = data;
}

void MenuInput::render()
{
  MenuItem::render();
  Terminal::get() << ": " + _data;
  _dataPos = Terminal::get().getCursorPos();
}

//MenuSelect

MenuSelect::MenuSelect(xml_node &data)
 : MenuItem(data), _cursor(0)
{
  _label = data.attribute("Text").value();
	for (pugi::xml_node el = data.first_child(); el; el = el.next_sibling())
  {
		if (strcmp(el.name(), "Option") == 0 ) _values.push_back(std::make_pair<std::string, std::string>(el.first_child().value(), el.attribute("Value").value()));
  }
}

void MenuSelect::select()
{
  int input;

  Menu::active->render(); //Render once
  while ((input = getch()) != KEY_ENTER && input != '\r' && input != '\n')
  {
    if (input == KEY_LEFT) --_cursor;
    else if (input == KEY_RIGHT) ++_cursor;
    if (_cursor < 0) _cursor = _values.size()-1;
    if (_cursor >= _values.size()) _cursor = 0;
    Terminal::get().clearScreen();
    Menu::active->render(); //Request render to update input
  }
  Terminal::get().clearScreen(); //Clear screen for menu redraw
}

bool MenuSelect::isSelectable()
{
  return (true);
}

std::string MenuSelect::getData()
{
  return (_values[_cursor].second);
}

void MenuSelect::setData(const std::string data)
{
  auto value = std::find_if(_values.begin(), _values.end(),
    			[=] (std::pair<std::string, std::string> p) { return (p.second == data); });
  if (value == _values.end()) throw (std::runtime_error("Value: " + data + " does not exist in select"));
  _cursor = value - _values.begin();
}

void MenuSelect::render()
{
  MenuItem::render();
  Terminal::get() << "    <" + _values[_cursor].first + ">";
}