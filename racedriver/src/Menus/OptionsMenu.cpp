#include <Menus/OptionsMenu.hh>

OptionsMenu::OptionsMenu(std::string font, int csize, std::string bg) : Menu(font, csize, bg)
{
  _hcursor = 0;
}

OptionsMenu::~OptionsMenu()
{

}

void OptionsMenu::initLabel(std::string title, std::vector<std::string> items, std::vector<std::pair<std::vector<std::string>, int>> values)
{
  _title.setString(title);
  _values = values;
  _stritems = items;
  for (size_t i = 0; i < items.size(); i++)
  {
    _items.push_back(sf::Text());
    _items[i].setString(items[i]+"\t"+values[i].first[0]);
    _items[i].setFont(*_title.getFont());
    _items[i].setCharacterSize(_title.getCharacterSize() / TITLE_FACTOR);
  }
}

void OptionsMenu::updateNav(sf::Event event)
{
  _items[_cursor].setStyle(0);
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Down)
    {
      _cursor += 1;
      _hcursor = _values[_cursor].second;
    }
    else if (event.key.code == sf::Keyboard::Up)
    {
      _cursor -= 1;
      _hcursor = _values[_cursor].second;
    }
    if (event.key.code == sf::Keyboard::Left)
      _hcursor -= 1;
    else if (event.key.code == sf::Keyboard::Right)
      _hcursor += 1;
    if (_cursor < 0)
      _cursor = static_cast<unsigned int>(_items.size() - 1);
    else if (static_cast<unsigned int>(_cursor) >= _items.size())
      _cursor = 0;
    if (_hcursor < 0)
      _hcursor = static_cast<unsigned int>(_values[_cursor].first.size() - 1);
    else if (static_cast<unsigned int>(_cursor) >= _values[_cursor].first.size())
      _hcursor = 0;
    _items[_cursor].setString(_stritems[_cursor]+"\t"+_values[_cursor].first[_hcursor]);
  }
  _items[_cursor].setStyle(sf::Text::Bold);
}
