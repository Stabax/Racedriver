//Tires.cpp
#include "Tires.hh"
#include "Menu.hh"

std::vector<Tires> Tires::collection = std::vector<Tires>();

Tires::Tires(const std::string& marque, const char& rang, const int& usure)
 : _brand(marque), _rank(rang), _durability(usure), _price(vRang(_rank) * 1500)
{

}

Tires::Tires(const json &data)
 : _brand(data["name"].get<std::string>()), _rank(data["rank"].get<std::string>()[0]), _durability(100), _price(vRang(_rank) * 1500)
{

}

Tires::~Tires()
{

}

bool Tires::loadCollection()
{
	DataFile collectionFile("./Data/composants/tires.json");

	if (!collectionFile.load())
	{
		throw ("Fichier corrumpu");
		return (false);
	}
	collectionFile.copyTo(Tires::collection);
	return (true);
}

Tires* Tires::chargerTires(const int& id, const int& usure)
{
	Tires* TiresCharge = 0; //Tires a creer
	std::string var=""; //contient les lignes du fichier
	std::string chemin = "Data/composants/pneus.cdx";
	int idActuel = id + 1; //indique l'id actuellement lu dans le fichier

	std::ifstream engine(chemin.c_str());

	if(!engine)
	{
		Menu::error("Echec de lecture du fichier pneus.cdx");
	}
	else
	{
		while(idActuel!=id && std::getline(engine, var))
		{
			std::istringstream iss(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				Menu::error("Fichier corrompu12");
			}
			//on utilise while(std::getline(flux, string) pour "Tant qu'il y a une ligne a lire"
		}

		if(idActuel==id)
		{
			int curseur;
			var.erase(0,var.find_first_of(";")+1);

		      curseur=var.find_first_of(";");
			std::string marque=var.substr(0,curseur);
			var.erase(0,curseur+1);

			char rang = var[0];

			TiresCharge = new Tires(marque, rang, usure);
		}
		else
		{
			Menu::error("Fichier corompu15.");
		}
	}
	return TiresCharge;
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

std::string Tires::getMarque() const
{
	return _brand;
}

int Tires::getDurabilite() const
{
	return _durability;
}


int Tires::getPrix() const
{
	return _price;
}

char Tires::getRang() const
{
	return _rank;
}

void Tires::setDurabilite(int value)
{
	_durability = value;
}
