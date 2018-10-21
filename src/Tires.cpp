//Tires.cpp
#include "Tires.hh"
#include "Menu.hh"

std::vector<Tires> Tires::collection = std::vector<Tires>();

Tires::Tires(const std::string& marque, const char& rang, const int& usure)
 : Part(), _name(marque), _rank(rang), _durability(usure), _price(vRang(_rank) * 1500)
{

}

Tires::Tires(const json &data)
 : Part(), _name(data["name"].get<std::string>()), _rank(data["rank"].get<std::string>()[0]), _durability(100), _price(vRang(_rank) * 1500)
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
		std::string espace="      "; //6 espaces
		std::string espace2;
		if(collection[i].getName().size() < 12)
		{
			for (size_t i = 0; i < 12 - collection[i].getName().size(); i++)
			{
				espace2+=" ";
			}
		}
		Terminal::get() << i << "." << " " << collection[i].getName() << espace2 << collection[i].getRank() << espace << "PRIX" << "c\n";
	}
}

std::string Tires::getName() const
{
	return _name;
}

int Tires::getDurability() const
{
	return _durability;
}


int Tires::getPrice() const
{
	return _price;
}

char Tires::getRank() const
{
	return _rank;
}

void Tires::setDurability(int value)
{
	_durability = value;
}
