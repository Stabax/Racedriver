//Track.cpp
#include "Track.hh"
#include "Menu/Menu.hh"

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

Segment::Segment(const omni::Meter &g, const omni::Meter &l, const omni::Degree &c)
 : gradient(g), length(l), curve(c)
{
}

Segment::Segment(const json &data)
 : gradient(data["gradient"].get<int>()), length(data["length"].get<int>()), curve(data["curve"].get<int>())
{
}

omni::Meter Segment::getRadius() const
{
	if (curve == omni::Degree(0)) return (omni::Meter(0));
	return (length / curve);
}

//
// Track
//

std::vector<Track> Track::collection = std::vector<Track>();

Track::Track(const json &data)
 : name(data["name"].get<std::string>()),
 	 climate(convertClimate(data["climate"].get<std::string>()))
{
	Orientation orientation = North;
	for (size_t i = 0; i < data["track"].size(); i++)
	{
		_track.push_back(Segment(data["track"][i]));
		orientation = static_cast<Orientation>(orientation + _track.back().curve.count() / 90);
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

Segment Track::getSegmentBetween(const omni::Meter &at, const omni::Meter &to)
{
	size_t index = 0;
	Segment newSegment;
	omni::Meter segBegin = 0, distance = to - at;
	omni::Meter segRemaining;

	if (at > length) throw (std::runtime_error("Getting segment out of range"));
	while (distance > omni::Meter(0))
	{
		while (index < _track.size() && at < segBegin)
		{
			segBegin += _track[index].length;
			index++;
		}
		segRemaining = _track[index].length - (at - segBegin);
		newSegment.length += segRemaining;
		newSegment.curve += (_track[index].curve / _track[index].length) * segRemaining;
		newSegment.gradient += (_track[index].gradient / _track[index].length) * segRemaining;
		distance -= segRemaining;
	}
	return (newSegment);
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