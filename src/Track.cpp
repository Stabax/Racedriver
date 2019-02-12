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
// Segment
//

Segment::Segment(const json &data)
 : gradient(data["gradient"].get<int>()), length(data["length"].get<int>()), curve(data["curve"].get<int>())
{
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
		_track.push_back(Segment(data["track"][i]));
		length += _track.back().length;
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

Segment &Track::getSegmentAt(const omni::Meter &at)
{
	size_t index = 0;
	omni::Meter total = 0;

	if (at > length) throw (std::runtime_error("Getting segment out of range"));
	while (at < total)
	{
		total += _track[index].length;
		index++;
	}
	return (_track[index]);
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