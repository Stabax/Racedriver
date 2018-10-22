//Tires.cpp
#include "Tires.hh"
#include "Menu.hh"

std::map<std::string, Tires> Tires::collection = std::map<std::string, Tires>();

Tires::Tires(const json &data)
 : Part(data), _durability(100), _price(vRang(rank) * 1500)
{

}

Tires::~Tires()
{

}

void Tires::listerTires()
{
	int index = 1;
	Terminal::get() <<"   |Marque     |rang  |Prix  |\n\n";
	for (auto it = collection.begin(); it != collection.end(); it++)
	{
		const Tires &tire = it->second;
		std::string espace="      "; //6 espaces
		std::string espace2;
		if(tire.name.size() < 12)
		{
			for (size_t i = 0; i < 12 - tire.name.size(); i++)
			{
				espace2+=" ";
			}
		}
		Terminal::get() << index << "." << " " << tire.name << espace2 << tire.rank << espace << "PRIX" << "c\n";
		++index;
	}
}

int Tires::getDurability() const
{
	return _durability;
}


int Tires::getPrice() const
{
	return _price;
}

void Tires::setDurability(int value)
{
	_durability = value;
}
