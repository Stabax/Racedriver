#ifndef TRACK_HH_
#define TRACK_HH_

#include <string>
#include <vector>
#include "DataFile.hh"
#include "Game.hh"

// Entity types
struct Entity {
	enum Type {
		Curve
	};

	static std::map<std::string, Entity::Type> collection;
}

class Track
{
public:
	enum Climate {
		Normal,
		Mountain,
		Desert,
		Sea
	};

	Track(const json &data);
	~Track();

	Climate convertClimate(const std::string &climate);
	int getSegmentRatio();

	static Track selectTrack();
	static void loadCollection();

	static std::vector<Track> collection;

	std::string name;
	int length;
	int curves;
	Climate climate;
};

#endif /* !TRACK_HH_ */
