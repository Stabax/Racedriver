#ifndef TRACK_HH_
#define TRACK_HH_

#include <string>
#include <vector>
#include <omniunit.hh>
#include "DataFile.hh"
#include "Game.hh"


struct Entity {
	enum Type {
		Curve
	};

	Entity(Type t, int v);

	static void loadCollection();

	static std::map<std::string, Entity> collection;

	Type type;
	int value;
};


struct Segment {
	Segment(const json &data);

	omni::Meter gradient;
	omni::Meter length;
	omni::Degree curve;
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
	omni::Meter getLength();

	static void loadCollection();

	static std::vector<Track> collection;

	std::string name;
	std::vector<Segment> track;
	omni::Meter length;
	Climate climate;
};

#endif /* !TRACK_HH_ */
