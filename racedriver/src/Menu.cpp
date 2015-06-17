#include <Menu.hh>

Menu::Menu(std::string title, std::vector<std::string> items, std::string font)
{
  extern sf::Vector2i	g_winsize;
  sf::Vector2f		pos;

  _cursor = 0;
  if (!_font.loadFromFile(font+".ttf"))
    {
      std::cerr << "Unable to load font file";
    }
  _title.setFont(_font);
  _title.setString(title);
  _title.setCharacterSize(100);
  pos.x = (static_cast<float>(g_winsize.x) / 2.0f) - (_title.getLocalBounds().width / 2.0f);
  pos.y = 10.0f;
  _title.setPosition(pos.x, pos.y);
  for (size_t i = 0; i < items.size(); i++)
    {
      _items.push_back(sf::Text());
      _items[i].setFont(_font);
      _items[i].setString(items[i]);
      _items[i].setCharacterSize(75);
      pos.x = (static_cast<float>(g_winsize.x) / 2.0f) - (_items[i].getLocalBounds().width / 2.0f);
      pos.y = 200.0f + (static_cast<float>(i) * 100.0f);
      _items[i].setPosition(pos.x, pos.y);
    }
}

Menu::~Menu()
{

}

bool Menu::update(sf::Event event)
{
  _items[_cursor].setStyle(0);
  if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Down)
	_cursor += 1;
      else if (event.key.code == sf::Keyboard::Up)
	_cursor -= 1;
    }
  if (_cursor < 0)
    _cursor = static_cast<unsigned int>(_items.size() - 1);
  else if (static_cast<unsigned int>(_cursor) >= _items.size())
    _cursor = 0;
  _items[_cursor].setStyle(sf::Text::Underlined);
  return (true);
}

void Menu::draw(sf::RenderWindow &win)
{
  win.draw(_title);
  for (size_t i = 0; i < _items.size(); i++)
    {
      win.draw(_items[i]);
    }
}
