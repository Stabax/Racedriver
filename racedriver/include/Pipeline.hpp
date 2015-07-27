#ifndef PIPELINE_HPP_
#define PIPELINE_HPP_

#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Pipeline
{
public:
  Pipeline();
  ~Pipeline();

  int		loadTextures(std::vector<std::string> toload);
  int		loadFonts(std::vector<std::string> toload);
  bool		load();

  sf::Texture	&getTexture(std::string name);
  sf::Font	&getFont(std::string name);

private:
  std::map<std::string, std::string>	_paths;
  std::map<std::string, sf::Texture>	_textures;
  std::map<std::string, sf::Font>	_fonts;

};

#endif
