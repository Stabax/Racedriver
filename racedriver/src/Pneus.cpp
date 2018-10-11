//Pneus.cpp
#include "Pneus.hh"

Pneus::Pneus(const std::string& marque, const char& rang, const int& usure)
 : m_marque(marque), m_rang(rang), m_durabilite(usure), m_prix(vRang(m_rang)*1500)
{

}

Pneus::~Pneus()
{

}

Pneus* Pneus::chargerPneus(const int& id, const int& usure)
{
	Pneus* PneusCharge = 0; //Pneus a creer
	std::string var=""; //contient les lignes du fichier
	std::string chemin = "Data/composants/pneus.cdx";
	int idActuel = id + 1; //indique l'id actuellement lu dans le fichier

	std::ifstream engine(chemin.c_str());

	if(!engine)
	{
		error("Echec de lecture du fichier pneus.cdx");	
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
				error("Fichier corrompu12");
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

			PneusCharge = new Pneus(marque, rang, usure);
		}
		else
		{
			error("Fichier corompu15.");
		}
	}
	return PneusCharge;
}

void Pneus::listerPneus()
{
	std::string chemin ="Data/composants/pneus.cdx";

	std::string var;
	int prixPneus=0;

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

std::string Pneus::getMarque() const
{
	return m_marque;
}

int Pneus::getDurabilite() const
{
	return m_durabilite;
}


int Pneus::getPrix() const
{
	return m_prix;
}

char Pneus::getRang() const
{
	return m_rang;
}

void Pneus::setDurabilite(const int& valeur)
{
	m_durabilite=valeur;
}
