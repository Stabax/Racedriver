#include <MusicBox.hh>

MusicBox::MusicBox()
{
  _current = 0;
  _active = false;
  _playlist = generate();
  LPlay();
  _music.stop();
}

MusicBox::~MusicBox()
{

}

int MusicBox::LPlay()
{
  extern Pipeline g_pipeline;

  if (!_music.openFromFile("./"+g_pipeline.getPath("data")+g_pipeline.getPath("music")+_playlist[_current]+".ogg"))
    return (-1);
  _music.play();
  return (0);
}

void MusicBox::toggle(bool state)
{
  if (state == _active)
    return;
  if (state == true)
  {
    _active = false;
    _music.stop();
  }
  else
  {
    _active = true;
    _playlist = generate();
    LPlay();
  }

}

std::vector<std::string> MusicBox::generate()
{
  extern Pipeline g_pipeline;
  std::vector<std::string> pl;
  struct dirent *ent;
  std::string path = "./"+g_pipeline.getPath("data")+g_pipeline.getPath("music");
  DIR *dir;

  if ((dir = opendir(path.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
      if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        std::string entry = ent->d_name;
        pl.push_back(entry.substr(0, entry.find(".")));
      }
  }
  closedir(dir);
  return (pl);
}

sf::Music &MusicBox::getMusic()
{
  return (_music);
}

void MusicBox::update()
{
  if (_active == false)
    return;
  if (_music.getStatus() != sf::Music::Playing)
  {
    _current += 1;
    if (_current >= _playlist.size())
    {
      _playlist = generate();
      _current = 0;
    }
    LPlay();
  }
}
