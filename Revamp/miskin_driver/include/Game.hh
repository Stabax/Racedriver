#ifndef GAME_HH_
#define GAME_HH_

#include <SFML/Graphics.hpp>
#include "Console.hpp"
#include "string.h"

typedef enum e_gamestate {
  Menu,
  Play
} gamestate;

typedef struct s_engine
{
  sf::RenderWindow win;
  gamestate gs;
  Console *con;
} t_engine;

#endif /* !GAME_HH_ */
