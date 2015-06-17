#ifndef HUD_HH_
#define HUD_HH_

#include <SFML/Graphics.hpp>

class HUD
{
public:
  HUD();
  ~HUD();

  bool update(sf::Event event);
  void draw(sf::RenderWindow &);

private:

};

#endif
