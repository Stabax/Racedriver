//Track.cpp
#include "Track.hh"
#include "Menu.hh"

std::vector<Track> Track::collection = std::vector<Track>();

Track::Track(const json &data)
 : name(data["name"].get<std::string>()), length(data["length"].get<int>()), curves(data["curves"].get<int>()),
 	 climate(convertClimate(data["climate"].get<std::string>()))
{
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

	for (size_t i = 0; i < collection.size(); i++, it++)
	{
		Terminal::get() << i+1 << ". " << it->name << "\n";
	}
	Terminal::get() << "0. Retour\n";
	if ((choice = Menu::askChoice()) > 0)
	{
		return (collection[choice]);
	}
	throw (std::runtime_error("No track selected"));
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