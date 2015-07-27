#include <SFML/System.hpp>
#include <GameEngine.hpp>

sf::Vector2i	g_winsize;
Pipeline	g_pipeline;

int		main(int argc, char **argv)
{
  GameEngine	Game;

  static_cast<void> (argc);
  static_cast<void> (argv);
  if (!g_pipeline.load()
      || !Game.initialize())
    return (EXIT_FAILURE);
  while (Game.update() == true)
    {
      Game.draw();
    }
  return (EXIT_SUCCESS);
}
