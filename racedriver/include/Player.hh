#ifndef PLAYER_HH_
#define PLAYER_HH_

#include <string>
#include <vector>
#include <default.hh>

enum Difficulty {
  Easy,
  Normal,
  Hard,
  Expert
};

class Player
{
public:
  Player(std::string name);
  ~Player();

  static Player *loadGame();

private:
  std::string		_name;
  long			_credits;
  Difficulty		_difficulty;
  int			_boxCount;
  std::vector<void *>	_boxs;

};

#endif
