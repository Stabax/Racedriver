#include "Game.hh"

void setLaunchOptions(t_engine &engine, int argc, char **argv)
{
  for (short i = 0; i < argc; i++)
    if (strcmp(argv[i], "-console") == 0)
      engine.con.show();
}

bool init(t_engine &engine)
{
  engine.win.create(sf::VideoMode(1024, 768), "RaceDriver");
  engine.win.setVerticalSyncEnabled(false);
  engine.win.setFramerateLimit(90);
  return (true);
}

bool update(t_engine &engine)
{
  sf::Event event;
  
  if (!engine.win.isOpen())
    return (false);
  while (engine.win.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	return (false);
    }
  return (true);
}

void draw(t_engine &engine)
{
  engine.win.clear();

  engine.win.display();
}

int main(int argc, char **argv)
{
  t_engine engine;

  if (!init(engine))
    return (1);
  setLaunchOptions(engine, argc, argv);
  while (update(engine))
    draw(engine);
  engine.win.close();
  return (0);
}
