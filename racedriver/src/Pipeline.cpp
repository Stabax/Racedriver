#include <Pipeline.hpp>
#include <iostream>

Pipeline::Pipeline()
{
  _paths.insert(std::make_pair("data", "Data/"));
  _paths.insert(std::make_pair("textures", "texture/"));
  _paths.insert(std::make_pair("fonts", "font/"));
}

Pipeline::~Pipeline()
{

}

int Pipeline::loadTextures(std::vector<std::string> toload)
{
  sf::Texture	loaded;

  for (size_t i = 0; i < toload.size(); i++)
    {
      if (!loaded.loadFromFile("./"+_paths["data"]+_paths["textures"]+toload[i]+".png"))
	return (1);
      _textures.insert(std::make_pair(toload[i], sf::Texture(loaded)));
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
  std::vector<std::string>	textures = {"carbon"};
  std::vector<std::string>	fonts = {"truckdriver"};


  if (loadTextures(textures) > 0
      || loadFonts(fonts) > 0)
    return (false);
  return (true);
}

sf::Texture &Pipeline::getTexture(std::string name)
{
  return (_textures[name]);
}

sf::Font &Pipeline::getFont(std::string name)
{
  return (_fonts[name]);
}
