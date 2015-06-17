#include <SFML/System.hpp>
#include <GameEngine.hpp>

sf::Vector2i	g_winsize;

int		main(int argc, char **argv)
{
  GameEngine	Game;

  static_cast<void> (argc);
  static_cast<void> (argv);
  while (Game.update() == true)
    {
      Game.draw();
    }
  return (EXIT_SUCCESS);
}
