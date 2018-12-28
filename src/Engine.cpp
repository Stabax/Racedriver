#include "Engine.hpp"

Collection<Engine> Engine::collection = Collection<Engine>();

Engine::Engine(const json &data)
 : Part(data), power(data["power"].get<int>()), energy(Diesel), price((power*25)+(vRang(rank)*500))
{

}

std::string Engine::info()
{
	return (Part::info() + " " + std::to_string(power));
}