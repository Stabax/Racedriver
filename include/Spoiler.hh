
//Spoiler.h

#ifndef SPOILER_HH_
#define SPOILER_HH_

#include <string>
#include <sstream>
#include <sol.hpp>
#include "Part.hpp"
#include "Collection.hpp"
#include "algos.hh"

class Spoiler : public Part
{
public:
	Spoiler(const json &data);
	~Spoiler();

	std::string getAerodynamic();
	static void expose(sol::environment &lua);

  static const std::string getPath() { return ("Spoilers"); };


	static Collection<Spoiler> collection;

	omni::Percent aerodynamic;
};

#endif /* SPOILER_HH_ */
