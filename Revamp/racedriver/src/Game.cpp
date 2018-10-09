#include "Game.hh"

/*
  Checks for arguments when launching the program
 */
void setLaunchOptions(t_engine &engine, int argc, char **argv)
{
  for (short i = 0; i < argc; i++)
    if (strcmp(argv[i], "-console") == 0)
      engine.con->toggle();
}

/*
  Initializes Game Engine struct
 */
bool init(t_engine &engine)
{
  engine.win.create(sf::VideoMode(1024, 768), "RaceDriver");
  engine.win.setVerticalSyncEnabled(false);
  engine.win.setFramerateLimit(90);
  engine.con = new Console(engine.win);
  return (true);
}

/*
  This loop is activated anytime a key is pressed
 */
bool updateKeyboard(t_engine &engine, sf::Event &event)
{
  if (engine.con->isOpen())
    if (!engine.con->update(event))
      return (false);
  return (true);
}

/*
  Highest Game Loop. If exited, program will quit.
 */
bool update(t_engine &engine)
{
  sf::Event event;
  
  if (!engine.win.isOpen())
    return (false);
  while (engine.win.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	return (false);
      if (event.type == sf::Event::KeyPressed)
	if (!updateKeyboard(engine, event))
	  return (false);
    }
  return (true);
}

/*
  Highest Draw Loop. Anything placed here will be drawn on next loop.
 */
void draw(t_engine &engine)
{
  engine.win.clear();
  engine.con->draw(engine);
  engine.win.display();
}

/*
  Main, call initialization and game logic loops.
 */
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
