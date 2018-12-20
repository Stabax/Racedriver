#ifndef TRACK_HH_
#define TRACK_HH_

#include <string>
#include <vector>
#include "DataFile.hh"
#include "Game.hh"


struct Entity {
	enum Type {
		Curve
	};

	Entity(Type t);

	static void loadCollection();

	static std::map<std::string, Entity> collection;
	Type type;
};


struct Step {
	Step(const json &data);

	std::vector<Entity> entities;
	int gradient;
};


struct Track
{
	enum Climate {
		Normal,
		Mountain,
		Desert,
		Sea
	};

	Track(const json &data);
	~Track();

	Climate convertClimate(const std::string &climate);
	int getLength();

	static Track selectTrack();
	static void loadCollection();

	static std::vector<Track> collection;

	std::string name;
	std::vector<Step> track;
	Climate climate;
};

#endif /* !TRACK_HH_ */
