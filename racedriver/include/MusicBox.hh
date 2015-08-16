#ifndef MUSICBOX_HH_
#define MUSICBOX_HH_

#ifndef WIN32
    #include <sys/types.h>
#endif
#include <cstring>
#include <dirent.h>
#include <Pipeline.hpp>
#include <Menus/Menu.hh>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <time.h>

class MusicBox
{
public:
  MusicBox();
  ~MusicBox();

  void init(bool state);
  int LPlay();
  void toggle(bool state);
  std::vector<std::string> generate();
  sf::Music &getMusic();

  void update();

private:
  bool                      _active;
  std::vector<std::string>  _playlist;
  size_t                    _current;
  sf::Music                 _music;
};

#endif
