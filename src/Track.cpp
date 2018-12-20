//Track.cpp
#include "Track.hh"
#include "Menu.hh"

//
// Entity
//

std::map<std::string, Entity> Entity::collection = std::map<std::string, Entity>();

Entity::Entity(Entity::Type t)
 : type(t)
{

}

void Entity::loadCollection()
{
	collection.emplace("curve", Entity(Curve));
}

//
// Step
//

Step::Step(const json &data)
 : gradient(data["gradient"].get<int>())
{
	for (size_t i = 0; i < data["entities"].size(); i++)
	{
		entities.push_back(Entity::collection.at(data["entities"][i].get<std::string>()));
	}
}

//
// Track
//

std::vector<Track> Track::collection = std::vector<Track>();

Track::Track(const json &data)
 : name(data["name"].get<std::string>()),
 	 climate(convertClimate(data["climate"].get<std::string>()))
{
	for (size_t i = 0; i < data["track"].size(); i++)
	{
		track.push_back(Step(data["track"][i]));
	}
}

Track::~Track()
{
}

Track::Climate Track::convertClimate(const std::string &climate)
{
	if (climate == "Mountain") return (Mountain);
	if (climate == "Desert") return (Desert);
	if (climate == "Sea") return (Sea);
	else return (Normal);
}

Track Track::selectTrack()
{
	auto it = collection.begin();
	int choice;

	Terminal::get().clearScreen();
	Terminal::get() << "======\n"
									<< "Choisissez un circuit:\n"
									<< "======\n";
	for (size_t i = 0; i < collection.size(); i++, it++)
	{
		Terminal::get() << i+1 << ". " << it->name << "\n";
	}
	Terminal::get() << "0. Retour\n";
	if ((choice = Menu::askChoice()) > 0)
	{
		return (collection[choice-1]);
	}
	throw (std::runtime_error("No track selected"));
}

int Track::getLength()
{
	return (track.size());
}

void Track::loadCollection()
{
	DataFile file("./Data/Tracks.json");

	if (!file.load())
	{
		throw (std::runtime_error("Error loading tracks"));
	}
	const json &data = file.getData();
	for (size_t i = 0; i < data["collection"].size(); i++)
	{
		collection.push_back(Track(data["collection"][i]));
	}
}