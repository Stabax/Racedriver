#ifndef GAME_HH_
#define GAME_HH_

#include <SFML/Graphics.hpp>

typedef enum e_gamestate {
  Menu,
  Play,
  
} gamestate;

typedef struct s_engine
{
  sf::RenderWindow win;
} t_engine;

#endif /* !GAME_HH_ */
