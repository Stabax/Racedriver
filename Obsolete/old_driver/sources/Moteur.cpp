
//Moteur.cpp

#include "Moteur.h"

//Constructeurs
Moteur::Moteur(const std::string& marque, const std::string& modele, const char& rang, const int& vitesse, const int& acceleration, const std::string& carburant)
 : m_marque(marque), m_modele(modele), m_prix(((getVitesse()+getAcceleration())*25)+(vRang(m_rang)*500)), m_rang(rang), m_vitesse(vitesse), m_acceleration(acceleration), m_typeCarburant(carburant), m_consommation(vitesse+acceleration), m_prixCarburant(Moteur::returnPrixCarburant(carburant))
{

}



//Destructeur
Moteur::~Moteur()
{

}



//Methodes statiques
Moteur* Moteur::chargerMoteur(const int& id, const std::string& marqueChargee)
{
	Moteur* MoteurCharge = 0; //moteur a creer
	std::string var=""; //contient les lignes du fichier
	std::string chemin = "Data/Moteurs/"+marqueChargee+".cdx";
	int idActuel = id + 1; //indique l'id actuellement lu dans le fichier

	std::ifstream engine(chemin.c_str());

	if(!engine)
	{
		error("Echec de lecture du fichier "+marqueChargee+".cdx");
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
			std::string modele=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			char rang=var[0];
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sVitesse=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sAcceleration=var.substr(0,curseur);
			var.erase(0,curseur+1);

			std::string carburant=var;

			int vitesse;
			int acceleration;
			std::istringstream iss(sVitesse);
			if (iss>>vitesse)
			{
			}
			else
			{
				error("Fichier corompu13.");
			}
			iss.clear();
			iss.str(sAcceleration);
			if (iss>>acceleration)
			{
			}
			else
			{
				error("Fichier corompu14.");
			}

			MoteurCharge = new Moteur(marqueChargee, modele, rang, vitesse, acceleration, carburant);
		}
		else
		{
			error("Fichier corompu15.");
		}
	}
	return MoteurCharge;
}


void Moteur::listerMoteurs(const std::string& marque)
{
	std::cout<<"Liste des moteurs "<< marque <<" :\n\n";

	std::string chemin ="Data/Moteurs/"+marque+".cdx";

	std::string var;

	std::ifstream flux(chemin.c_str());
	if(flux)
	{
		int curseur;
		std::cout<<"   |Modele     |Rang  |Vitesse  |Acceleration  |Carburant  |Prix |\n\n";
		while(std::getline(flux, var))
		{
				curseur=var.find_first_of(";");
				std::string id=var.substr(0,curseur);
				var.erase(0,curseur+1);

				curseur=var.find_first_of(";");
				std::string modele=var.substr(0,curseur);
				var.erase(0,curseur+1);

				curseur=var.find_first_of(";");
				char rang=var[0];
				var.erase(0,curseur+1);

				curseur=var.find_first_of(";");
				std::string sVitesse=var.substr(0,curseur);
				var.erase(0,curseur+1);

				curseur=var.find_first_of(";");
				std::string sAcceleration=var.substr(0,curseur);
				var.erase(0,curseur+1);

				std::string carburant=var;

				std::string espace1;
				std::string espace2;
				std::string espace3;
				std::string espace4;
				std::string espace5;
				std::string espaceRang="      "; //6 espaces



				if(modele.size()<12)
				{
					for (size_t i=0; i<12-modele.size(); i++)
					{
						espace1+=" ";
					}
				}

				if(sVitesse.size()<10)
				{
					for (size_t i = 0; i<10 - sVitesse.size(); i++)
					{
						espace2+=" ";
					}
				}

				if(sAcceleration.size()<15)
				{
					for (size_t i=0; i<15 - sAcceleration.size(); i++)
					{
						espace3+=" ";
					}
				}

				if(carburant.size()<12)
				{
					for (size_t i=0; i<12-carburant.size(); i++)
					{
						espace4+=" ";
					}
				}

				if(id.size()<3)
				{
					for (size_t i=0; i<3-id.size(); i++)
					{
						espace5+=" ";
					}
				}

				int vitesse;
				int acceleration;
				std::istringstream iss(sVitesse);
				if (iss>>vitesse)
				{
				}
				else
				{
					error("Fichier corompu16.");
				}
				iss.clear();
				iss.str(sAcceleration);
				if (iss>>acceleration)
				{
				}
				else
				{
					error("Fichier corompu17.");
				}

				int prix = ((vitesse + acceleration) * 25) + ( (vRang(rang)-1) * 500);


				std::cout<<id<<"."<<espace5<<modele<< espace1 <<rang<< espaceRang <<vitesse<< espace2 <<acceleration<< espace3 <<carburant<< espace4 << prix <<"c\n";

		}
	}
	else
	{
		error("Fichier corrompu");
	}
}


void Moteur::infoMoteur(const int& id, const std::string& marque, std::string& modele)
{
	std::string var; //contient les lignes du fichier
	std::string chemin ="Data/Moteurs/"+marque+".cdx";
	std::ifstream engine(chemin.c_str());

	if(!engine)
	{
		error("Echec de lecture du fichier "+marque+".cdx");
	}
	else
	{
		int idActuel; //indique l'id actuellement lu dans le fichier

		while(idActuel!=id && std::getline(engine, var))
		{
			std::istringstream iss(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				error("Fichier corrompu18");
			}
		}

		if(idActuel==id)
		{
			int curseur;
			var.erase(0,var.find_first_of(";")+1);

			curseur=var.find_first_of(";");
			modele=var.substr(0,curseur);
			var.erase(0,curseur+1);
		}
		else
		{
			error("Fichier corompu21.");
		}
	}
}


void Moteur::infoMoteur(const int& id, const std::string& marque, int& prix)
{
	std::string var = ""; //contient les lignes du fichier
	std::string chemin ="Data/Moteurs/"+marque+".cdx";
	std::ifstream engine(chemin.c_str());
	std::istringstream iss;
	int idActuel = 0; //indique l'id actuellement lu dans le fichier
	int curseur;

	int vitesse;
	int acceleration;

	std::string sVitesse;
	std::string sAcceleration;
	char rang;

	if(!engine)
	{
		error("Echec de lecture du fichier "+marque+".cdx");
	}
	else
	{
		while(idActuel!=id && std::getline(engine, var))
		{
			iss.str(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				error("Fichier corrompu18b");
			}
			iss.clear();
		}
		curseur = var.find_first_of(";");
		var.erase(0, curseur + 1); // On retire l'id
		if(idActuel==id)
		{

			curseur = var.find_first_of(";");
			var.erase(0, curseur + 1); // On retire le modele

			rang = var[0];
			var.erase(0, 2); // On retire le rang

			curseur = var.find_first_of(";");
			sVitesse = var.substr(0, curseur);
			var.erase(0, curseur + 1); // On retire la vitesse chargee

			curseur = var.find_first_of(";");
			sAcceleration = var.substr(0, curseur);
			var.erase(0, curseur + 1); // On retire l'accel chargee

			iss.str(sVitesse);
			if (iss>>vitesse)
			{
			}
			else
			{
				error("Fichier corompu19b.");
			}
			iss.clear();
			iss.str(sAcceleration);
			if (iss>>acceleration)
			{
			}
			else
			{
				error("Fichier corompu20b.");
			}

			prix = (((vitesse + acceleration) * 25) + ( (vRang(rang)-1)) * 500);
		}
		else
		{
			error("Fichier corompu21b.");
		}
	}
}


void Moteur::infoMoteur(const int& id, const std::string& marque, std::string& modele, int& vitesse, int& acceleration)
{
	std::string var; //contient les lignes du fichier
	std::string chemin ="Data/Moteurs/"+marque+".cdx";
	std::ifstream engine(chemin.c_str());
	int idActuel = 0; //indique l'id actuellement lu dans le fichier
	int curseur = 0;
	std::istringstream iss;

	//Variables dont on va avoir besoin lors du chargement:
	std::string sVitesse;
	std::string sAcceleration;

	if(!engine)
	{
		error("Echec de lecture du fichier "+marque+".cdx");
	}
	else
	{
		while(idActuel!=id && std::getline(engine, var))
		{
			curseur = var.find_first_of(";");
			iss.str(var.substr(0, curseur));
			if(iss >> idActuel)
			{
			}
			else
			{
				error("Fichier corrompu18");
			}
			iss.clear();
		}
		var.erase(0, curseur + 1); //On supprime l'id de la ligne
		if(idActuel==id)
		{
			curseur = var.find_first_of(";");
			modele = var.substr(0, curseur);
			var.erase(0, curseur + 1); // On retire le modele charge

			curseur = var.find_first_of(";");
			var.erase(0, curseur + 1); // On retire le rang

			curseur = var.find_first_of(";");
			sVitesse = var.substr(0, curseur);
			var.erase(0, curseur + 1); // On retire la vitesse chargee

			curseur = var.find_first_of(";");
			sAcceleration = var.substr(0, curseur);
			var.erase(0, curseur + 1); // On retire l'accel chargee

			iss.str(sVitesse);
			if(iss>>vitesse)
			{
			}
			else
			{
				error("Fichier corompu19.");
			}
			iss.clear();
			iss.str(sAcceleration);
			if(iss>>acceleration)
			{
			}
			else
			{
				error("Fichier corompu20.");
			}
		}
		else
		{
			error("Fichier corompu21.");
		}
	}
}


void Moteur::infoMoteur(const int& id, const std::string& marque, std::string& modele, int& vitesse, int& acceleration, char& rang, int& prix)
{
	std::string var; //contient les lignes du fichier
	std::string chemin ="Data/Moteurs/"+marque+".cdx";
	std::ifstream engine(chemin.c_str());
	int curseur;

	if(!engine)
	{
		error("Echec de lecture du fichier "+marque+".cdx");
	}
	else
	{
		int idActuel; //indique l'id actuellement lu dans le fichier

		while(idActuel!=id && std::getline(engine, var))
		{
			std::istringstream iss(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				error("Fichier corrompu18");
			}
		}

		if(idActuel==id)
		{

			var.erase(0,var.find_first_of(";")+1);

			curseur=var.find_first_of(";");
			modele=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			rang=var[0];
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sVitesse=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sAcceleration=var.substr(0,curseur);
			var.erase(0,curseur+1);

			std::istringstream iss(sVitesse);
			if (iss>>vitesse)
			{
			}
			else
			{
				error("Fichier corompu19.");
			}
			iss.clear();
			iss.str(sAcceleration);
			if (iss>>acceleration)
			{
			}
			else
			{
				error("Fichier corompu20.");
			}

			prix = ((vitesse + acceleration) * 25) + ( (vRang(rang)-1) * 500);
		}
		else
		{
			error("Fichier corompu21.");
		}
	}
}


int Moteur::compterMoteurs(const std::string& marque)
{

	std::string chemin ="Data/Moteurs/"+marque+".cdx";
	std::ifstream engine(chemin.c_str());
	int id; //indique l'id actuellement lu dans le fichier
	int nbMoteur=0;
	std::string var;

	if(engine)
	{
		while(std::getline(engine, var))
		{
			 //on lit dans le fichier
			std::istringstream iss(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>id)
			{
				nbMoteur++;
			}
			else
			{
				error("Fichier corrompu22");
			}
			//on utilise while(std::getline(flux, string) pour "Tant qu'il y a une ligne a lire"
		}
	}
	else
	{
		error("Fichier corrompu23");
	}
	return nbMoteur;
}


float Moteur::returnPrixCarburant(const std::string& carburant)
{
	if(carburant=="Diesel")
	{
		return 5.0f;
	}
	else if(carburant=="SP95")
	{
		return 8.0f;
	}
	else if(carburant=="GPL")
	{
		return 11.0f;
	}
	else
	{
	 	throw std::string("Erreur, le carburant " + carburant + " n'existe pas !");
	}
}



//Accesseurs et Mutateurs
std::string Moteur::getModele() const
{
	return m_modele;
}


std::string Moteur::getMarque() const
{
	return m_marque;
}


char Moteur::getRang() const
{
	return m_rang;
}


float Moteur::getVitesse() const
{
	return m_vitesse;
}


float Moteur::getAcceleration() const
{
	return m_acceleration;
}


std::string Moteur::getTypeCarburant() const
{
	return m_typeCarburant;
}


float Moteur::getConsommation() const
{
	return m_consommation;
}


int Moteur::getPrix() const
{
	return m_prix;
}


float Moteur::getPrixCarburant() const
{
	return m_prixCarburant;
}



//Methodes
	//Aucune



//Operateurs methodes
	//Aucun
