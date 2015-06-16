#include <GameEngine.hpp>

int		main(int argc, char **argv)
{
  GameEngine	Game;

  static_cast<void> (argc);
  static_cast<void> (argv);
  while (Game.update())
    {
      Game.draw();
    }
  return (EXIT_SUCCESS);
}
