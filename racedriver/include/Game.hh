#ifndef GAME_HH_
#define GAME_HH_

#include <memory>
#include "Terminal.hh"

#define SERVER_PATH "http://racedriver.url.ph/"

class Game
{
public:
  Game();
  int main();
  void error(const std::string &str);
  void msg(const std::string &str);
  void removeUpdatePackage();
  void update();

  static std::unique_ptr<Game> instance; //Singleton handle
private:
  Terminal _term;
};

#endif /* !GAME_HH_ */