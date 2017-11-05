#ifndef ENGINE_HH_
#define ENGINE_HH_

#include "Engine.hpp"

class Engine : public stb::Engine
{
public:
	Engine();
	~Engine();

	virtual bool update(const sf::Event &e);
	virtual void draw(sf::RenderWindow *win);
};

#endif /* !ENGINE_HH_ */