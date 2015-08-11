#include <Menus/OptionsMenu.hh>

OptionsMenu::OptionsMenu(std::string font, int csize, std::string bg, std::string nav) : Menu(font, csize, bg, nav)
{
  _hcursor = 0;
}

OptionsMenu::~OptionsMenu()
{

}

float OptionsMenu::getBiggestWidth() const
{
  int best = 0;
  int count;

  for (size_t i = 0; i < _stritems.size(); i++)
  {
    for (size_t j = 0; j < _values[i].first.size(); j++)
    {
      count = (_stritems[i].length() + _values[i].first[j].length());
      if (best < count)
        best = count;
    }
  }
  return ((_title.getCharacterSize() / TITLE_FACTOR) * best);
}

void OptionsMenu::setPosition(sf::Rect<int> pos, bool center)
{
  extern sf::Vector2i	g_winsize;
  float spacing = (pos.height - ((_items.size() - 1) * _items[0].getLocalBounds().height) - 30) / (_items.size() - 1);

  _position = pos;
  _title.setPosition(centerText(_title, 'X'), TITLE_Y);
  _navbg.setScale(sf::Vector2f(pos.width / _navbg.getLocalBounds().width, pos.height / _navbg.getLocalBounds().height));
  _navbg.setPosition(pos.left, pos.top);
  for (size_t i = 0; i < _items.size(); i++)
  {
    if (center == true || i == _items.size() - 1)
      _items[i].setPosition(pos.left + ((pos.width / 2) - (_items[i].getLocalBounds().width / 2)),
        pos.top + 10 + (i * spacing));
    else
      _items[i].setPosition(pos.left + 10,
        pos.top + 10 + (i * spacing));
  }
}

void OptionsMenu::initLabel(std::string title, std::vector<std::string> items, std::vector<std::pair<std::vector<std::string>, int>> values)
{
  _title.setString(title);
  _values = values;
  _stritems = items;
  for (size_t i = 0; i < items.size(); i++)
  {
    _items.push_back(sf::Text());
    if (i == items.size() - 1)
      _items[i].setString(items[i]);
    else
      _items[i].setString(items[i]+"\t\t"+values[i].first[0]);
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
    else if (static_cast<unsigned int>(_hcursor) >= _values[_cursor].first.size())
      _hcursor = 0;
    _items[_cursor].setString(_stritems[_cursor]+"\t"+_values[_cursor].first[_hcursor]);
  }
  _items[_cursor].setStyle(sf::Text::Bold);
}
