#include <Pipeline.hpp>
#include <iostream>

Pipeline::Pipeline()
{
  _paths.insert(std::make_pair("data", "Data/"));
  _paths.insert(std::make_pair("saves", "Saves/"));
  _paths.insert(std::make_pair("music", "music/"));
  _paths.insert(std::make_pair("nav", "navigation/"));
  _paths.insert(std::make_pair("bg", "backgrounds/"));
  _paths.insert(std::make_pair("textures", "texture/"));
  _paths.insert(std::make_pair("fonts", "font/"));
}

Pipeline::~Pipeline()
{

}

int Pipeline::loadTextures(std::vector<std::pair<std::string, TType>> toload)
{
  sf::Texture	loaded;
  std::string path;

  for (size_t i = 0; i < toload.size(); i++)
    {
      path = "./"+_paths["data"]+_paths["textures"];
      if (toload[i].second == Tnav)
        path += _paths["nav"];
      else if (toload[i].second == Tbg)
        path += _paths["bg"];
      path += toload[i].first+".png";
      if (!loaded.loadFromFile(path))
	     return (1);
      _textures.insert(std::make_pair(toload[i].first, sf::Texture(loaded)));
    }
  return (0);
}

int Pipeline::loadFonts(std::vector<std::string> toload)
{
  sf::Font	loaded;

  for (size_t i = 0; i < toload.size(); i++)
    {
      if (!loaded.loadFromFile("./"+_paths["data"]+_paths["fonts"]+toload[i]+".ttf"))
	return (1);
      _fonts.insert(std::make_pair(toload[i], sf::Font(loaded)));
    }
  return (0);
}

bool Pipeline::load()
{
  std::vector<std::pair<std::string, TType>>	textures = {std::make_pair("carbon", Tbg),
    std::make_pair("graphite", Tnav)};
  std::vector<std::string>	fonts = {"truckdriver"};

  if (loadTextures(textures) > 0
      || loadFonts(fonts) > 0)
    return (false);
  return (true);
}

std::string &Pipeline::getPath(std::string keyword)
{
  return (_paths[keyword]);
}

sf::Texture &Pipeline::getTexture(std::string name)
{
  return (_textures[name]);
}

sf::Font &Pipeline::getFont(std::string name)
{
  return (_fonts[name]);
}
