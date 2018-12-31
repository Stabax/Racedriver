//Tires.cpp
#include "Tires.hh"
#include "Menu.hh"

Collection<Tires> Tires::collection = Collection<Tires>();

Tires::Tires(const json &data)
 : Part(data), _pressure(2.5f), _integrity(100), radius(data["radius"].get<int>()), _price(vRang(rank) * 1500)
{

}

Tires::~Tires()
{

}

void Tires::listerTires()
{
	Terminal::get() <<"   |Marque     |rang  |Prix  |\n\n";
	for (size_t i = 0; i < collection.size(); i++)
	{
		std::string espace = "      "; //6 espaces
		std::string espace2;
		if(collection[i].name.size() < 12)
		{
			for (size_t i = 0; i < 12 - collection[i].name.size(); i++)
			{
				espace2 += " ";
			}
		}
		Terminal::get() << i << "." << " " << collection[i].name << espace2 << collection[i].rank << espace << "PRIX" << "c\n";
	}
}

int Tires::getDurability() const
{
	return _integrity;
}


int Tires::getPrice() const
{
	return _price;
}

void Tires::setIntegrity(int value)
{
	_integrity = value;
}
