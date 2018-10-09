//Circuit.cpp
#include "Circuit.hh"

Circuit::Circuit(const std::string& nom, const int& taille, const int& virages, const int& climat, const int& difficulte, const int& denivele) : m_nom(nom), m_taille(taille), m_virages(virages), m_meteo(Circuit::construireMeteo(climat)), m_vent(Circuit::construireVent()), m_climat(Circuit::construireClimat(climat)), m_difficulte(difficulte), m_denivele(denivele)
{
}

Circuit::~Circuit()
{
}

void Circuit::chargerCircuit(const int& id, Circuit*& CircuitCourant)
{
	bool trouve = false;
	std::string circuitCharge; //Variable de lecture de ligne
	std::istringstream iss;
	std::ifstream tracks("Data/Tracks.map");

	if(!tracks.is_open()) //Si la lecture echoue
	{
		error("Echec de lecture du fichier tracks.map");
	}
	else
	{
		for (int boucle = 0; boucle < id; ++boucle)
		{
			std::getline(tracks, circuitCharge);
		}

		iss.clear();
		int curseur;
		curseur = circuitCharge.find_first_of(";"); //strpos() recherche la position du premier point virgule
		std::string nomCharge;
		nomCharge = circuitCharge.substr(0, curseur);
		circuitCharge.erase(0, curseur + 1); // On retire le nom du circuit charge

		int tailleChargee;
		curseur = circuitCharge.find_first_of(";");
		iss.str(circuitCharge.substr(0, curseur));
		iss >> tailleChargee;
		circuitCharge.erase(0, curseur + 1);
		iss.clear();

		int viragesCharges;
		curseur = circuitCharge.find_first_of(";");
		iss.str(circuitCharge.substr(0, curseur));
		iss >> viragesCharges;
		circuitCharge.erase(0, curseur + 1);
		iss.clear();

		int meteoChargee;
		curseur = circuitCharge.find_first_of(";");
		iss.str(circuitCharge.substr(0, curseur));
		iss >> meteoChargee;
		circuitCharge.erase(0, curseur + 1);
		iss.clear();

		int difficulte;
		curseur = circuitCharge.find_first_of(";");
		iss.str(circuitCharge.substr(0, curseur));
		iss >> difficulte;
		circuitCharge.erase(0, curseur + 1);
		iss.clear();

		int denivele;
		curseur = circuitCharge.find_first_of(";");
		iss.str(circuitCharge.substr(0, curseur));
		iss >> denivele;
		circuitCharge.erase(0, curseur + 1);
		iss.clear();

		trouve = true;
		CircuitCourant = new Circuit(nomCharge, tailleChargee, viragesCharges, meteoChargee, difficulte, denivele); //On construit le circuit charge
	}
	if(trouve == false)
	{
		error("Le circuit n'existe pas");
	}
}

int Circuit::listerCircuits()
{
	int nombreCircuits = 0; //id du circuit
	std::istringstream iss;
	std::ifstream tracks("Data/Tracks.map");

	if(!tracks.is_open()) //Si la lecture echoue
	{
		error("Echec de lecture du fichier tracks.map"); //Le fichier ne peut être charge, on affiche une erreur
	}
	else
	{
		std::string circuitCharge = ""; //ligne lue dans le fichier

		while(std::getline(tracks, circuitCharge))
		{
			int curseur;
			curseur = circuitCharge.find_first_of(";");
			std::string nomCharge;
			nomCharge = circuitCharge.substr(0, curseur);
			circuitCharge.erase(0, curseur + 1); // On retire le nom du circuit charge

			int tailleChargee;
			curseur = circuitCharge.find_first_of(";");
			iss.str(circuitCharge.substr(0, curseur));
			iss >> tailleChargee;
			circuitCharge.erase(0, curseur + 1);
			iss.clear();

			int viragesCharges;
			curseur = circuitCharge.find_first_of(";");
			iss.str(circuitCharge.substr(0, curseur));
			iss >> viragesCharges;
			circuitCharge.erase(0, curseur + 1);
			iss.clear();

			int climatCharge;
			curseur = circuitCharge.find_first_of(";");
			iss.str(circuitCharge.substr(0, curseur));
			iss >> climatCharge;
			circuitCharge.erase(0, curseur + 1);
			iss.clear();

			int difficulte;
			curseur = circuitCharge.find_first_of(";");
			iss.str(circuitCharge.substr(0, curseur));
			iss >> difficulte;
			circuitCharge.erase(0, curseur + 1);
			iss.clear();

			int denivele;
			curseur = circuitCharge.find_first_of(";");
			iss.str(circuitCharge.substr(0, curseur));
			iss >> denivele;
			circuitCharge.erase(0, curseur + 1);
			iss.clear();

			std::string climatString;
			if(climatCharge == 1)
			{
				climatString = "Sec";
			}
			else if(climatCharge == 2)
			{
				climatString = "Humide";
			}
			else if(climatCharge == 3)
			{
				climatString = "Neigeux";
			}
			else if(climatCharge == 4)
			{
				climatString = "Glacial";
			}

			nombreCircuits++;
			std::cout << "|-" << nombreCircuits << ". " << nomCharge << " [" << tailleChargee << " Km / " << viragesCharges << " Virages, Denivele: " << denivele <<"m] (" << climatString << "), {Difficulte: "<< difficulte <<"}\n";
		}
		std::cout << "\n"; //on separe le blocs de circuits de l'option retour
	}
	return nombreCircuits;
}

int Circuit::construireMeteo(const int& climat)
//le constructeur ne peut pas mettre de conditions dans la liste d'initialisation , donc on le fait ici
{
	int meteo = std::rand()%12;
	if(climat == 1)
	{
		if(meteo == 0 || meteo == 1 || meteo == 2 || meteo == 3)
		{
			meteo = 1; //Ensoleille
		}
		else if(meteo == 4 || meteo == 5 || meteo == 6)
		{
			meteo = 2; //Pluvieux
		}
		else if(meteo == 7 || meteo == 8 || meteo == 9)
		{
			meteo = 4; //Neigeux
		}
		else if(meteo == 10 || meteo == 11)
		{
			meteo = 6; //Verglace
		}
	}
	else if(climat == 2)
	{
		if(meteo == 0 || meteo == 1 || meteo == 2 )
		{
			meteo = 1; //Ensoleille
		}
		else if( meteo == 3 || meteo == 4 || meteo == 5 || meteo == 6)
		{
			meteo = 2; //Pluvieux
		}
		else if(meteo == 7 || meteo == 8 || meteo == 9)
		{
			meteo = 4; //Neigeux
		}
		else if(meteo == 10 || meteo == 11)
		{
			meteo = 6; //Verglace
		}
	}
	else if(climat == 3)
	{
		if(meteo == 0 || meteo == 1)
		{
			meteo = 1; //Ensoleille
		}
		else if(meteo == 2 || meteo == 3 || meteo == 4)
		{
			meteo = 2; //Pluvieux
		}
		else if(meteo == 5 || meteo == 6 || meteo == 7 || meteo == 8)
		{
			meteo = 4; //Neigeux
		}
		else if(meteo == 9 || meteo == 10 || meteo == 11)
		{
			meteo = 6; //Verglace
		}
	}
	else if(climat == 4)
	{
		if(meteo == 0 || meteo == 1  )
		{
			meteo = 1; //Ensoleille
		}
		else if(meteo == 2 || meteo == 3 || meteo == 4 )
		{
			meteo = 2; //Pluvieux
		}
		else if(meteo == 5 || meteo == 6 || meteo == 7 )
		{
			meteo = 4; //Neigeux
		}
		else if(meteo == 8 || meteo == 9 || meteo == 10 || meteo == 11)
		{
			meteo = 6; //Verglace
		}
	}
	return meteo;
}

int Circuit::construireVent()
{
//le constructeur ne peut pas mettre de conditions dans la liste d'initialisation , donc on le fait ici
	int vent = std::rand()%3;
	if(vent == 0)
	{
		vent = 1;
	}
	else if(vent == 1)
	{
		vent = 3;
	}
	else if(vent == 2)
	{
		vent = 5;
	}

	return vent;
}

std::string Circuit::construireClimat(const int& climat)
{
	if(climat == 1)
	{
		return "Sec";
	}
	else if(climat == 2)
	{
		return "Humide";
	}
	else if(climat == 3)
	{
		return "Neigeux";
	}
	else if(climat == 4)
	{
		return"Glacial";
	}
	else
	{
		return "ERREUR: mauvaise lecture du climat";
	}
}

std::string Circuit::getNom() const
{
	return m_nom;
}

int Circuit::getTaille() const
{
	return m_taille;
}

int Circuit::getVirages() const
{
	return m_virages;
}


int Circuit::getMeteo() const
{
	return m_meteo;
}


int Circuit::getVent() const
{
	return m_vent;
}


int Circuit::getDifficulte() const
{
	return m_difficulte;
}


int Circuit::getDenivele() const
{
	return m_denivele;
}