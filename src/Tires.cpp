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
	std::string chemin ="Data/composants/pneus.cdx";

	std::string var;

	std::ifstream flux(chemin.c_str());
	if(flux)
	{
		int curseur;
		Terminal::get() <<"   |Marque     |rang  |Prix  |\n\n";
		while(std::getline(flux, var))
		{

			curseur=var.find_first_of(";");
			std::string id=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string marque=var.substr(0,curseur);
			var.erase(0,curseur+1);

			char rang = var[0];


			std::string espace2;
			std::string espace4="      "; //6 espaces
			std::string espace5;


			if(marque.size()<12)
			{
				for (size_t i=0; i<12-marque.size(); i++)
				{
					espace2+=" ";
				}
			}

			if(id.size()<3)
			{
				for (size_t i=0; i<3-id.size(); i++)
				{
					espace5+=" ";
				}
			}


			Terminal::get() << id << "." << espace5 << marque << espace2 << rang << espace4 << "PRIX" << "c\n";
		}
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
