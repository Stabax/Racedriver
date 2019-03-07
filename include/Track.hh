#ifndef TRACK_HH_
#define TRACK_HH_

#include <string>
#include <vector>
#include <omniunit.hh>
#include <DataFile.hh>
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
	Segment(const omni::Meter &g = 0, const omni::Meter &l = 0, const omni::Degree &c = 0);
	Segment(const json &data);

	omni::Meter getRadius() const;

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

	enum Orientation {
		North,
		East,
		South,
		West
	};

	Track(const json &data);
	~Track();

	Climate convertClimate(const std::string &climate);
	Segment getSegmentBetween(const omni::Meter &at, const omni::Meter &to);

	static void loadCollection();

	static std::vector<Track> collection;

	std::string name;
	omni::Meter length;
	Climate climate;

private:
	std::vector<Segment> _track;
};

#endif /* !TRACK_HH_ */
