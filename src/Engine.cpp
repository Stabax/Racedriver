#include "Engine.hh"
#include "Resolver.hh"

Engine::Engine() : stb::Engine()
{
	stb::Resolver<sf::Font>::addLocation("./Font/");
	stb::Resolver<sf::Texture>::addLocation("./Texture/");
	stb::Resolver<stb::GUIScreen>::addLocation("./Menus/");
	init();
}

Engine::~Engine()
{

}

bool Engine::update(const sf::Event &e)
{
	return (true);
}

void Engine::draw(sf::RenderWindow &win)
{

}