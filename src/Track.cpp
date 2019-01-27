//Track.cpp
#include "Track.hh"
#include "Menu.hh"

//
// Entity
//

std::map<std::string, Entity> Entity::collection = std::map<std::string, Entity>();

Entity::Entity(Entity::Type t, int v)
 : type(t), value(v)
{

}

void Entity::loadCollection()
{
	collection.emplace("curve", Entity(Curve, 70));
}

//
// Step
//

Step::Step(const json &data)
 : gradient(data["gradient"].get<int>()), length(data["length"].get<int>())
{
	for (size_t i = 0; i < data["entities"].size(); i++)
	{
		try {
			entities.push_back(Entity::collection.at(data["entities"][i].get<std::string>()));
		} catch(std::exception &e) {
			Menu::alert("Unknown entity");
		}
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

int Track::getLength()
{
	return (track.size());
}

void Track::loadCollection()
{
	std::string path = "./Data/Tracks/";
	std::vector<std::string> tracks = DataFile::getFolderContents(path, ".json");
	for (size_t i = 0; i < tracks.size(); i++)
	{
		DataFile file(path+tracks[i]);

		if (!file.load())
		{
			throw (std::runtime_error("Error loading tracks"));
		}
		collection.push_back(Track(file.getData()));
	}
}