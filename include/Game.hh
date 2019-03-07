#ifndef GAME_HH_
#define GAME_HH_

#include <memory>
#include "Terminal.hh"

#define GAME_VERSION  "a2.0.0"
#define SERVER "stabax.org"
#define PWD_SALT	"RaceDriver"

class Game
{
public:
  Game();
  ~Game();

  bool load();
  int main();
  void removeUpdatePackage();
  bool update();

  static std::unique_ptr<Game> instance; //Singleton handle

private:
};

#endif /* !GAME_HH_ */