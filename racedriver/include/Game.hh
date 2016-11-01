#ifndef GAME_HH_
#define GAME_HH_

#include <SFML/Graphics.hpp>
#include "string.h"
#include "Console.hpp"

typedef enum e_gamestate {
  Menu,
  Play,  
} gamestate;

typedef struct s_engine
{
  sf::RenderWindow win;
  Console *con;
  gamestate gs;
} t_engine;

#endif /* !GAME_HH_ */
