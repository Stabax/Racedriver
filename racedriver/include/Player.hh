#ifndef PLAYER_HH_
#define PLAYER_HH_

#include <string>
#include <default.hh>

class Player
{
public:
  Player();
  ~Player();

private:
  std::string	_name;
  long		_money;
};

#endif
