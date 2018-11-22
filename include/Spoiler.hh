
//Spoiler.h

#ifndef SPOILER_HH_
#define SPOILER_HH_

#include <string>
#include <sstream>
#include "Part.hpp"
#include "Collection.hpp"
#include "algos.hh"

class Spoiler : public Part
{
public:
	Spoiler(const json &data);
	~Spoiler();

	int getAerodynamic() const;
	int getPrice() const;

	static Collection<Spoiler> collection;

protected:
	int _aerodynamic;
	int _price;
};

#endif /* SPOILER_HH_ */
