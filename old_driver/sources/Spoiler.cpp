
//Spoiler.cpp

#include "Spoiler.h"


//Constructeurs
Spoiler::Spoiler(const std::string& modele, const char& rang, const unsigned short int& aerodynamisme):m_nom(modele), m_rang(rang), m_aerodynamisme(aerodynamisme)
{
}



//Destructeur
Spoiler::~Spoiler()
{

}



//Methodes statiques
Spoiler* Spoiler::chargerSpoiler(const unsigned short int& id)
{
	Spoiler* SpoilerCharge = 0; //Spoiler a creer
	std::string var=""; //contient les lignes du fichier
	std::string chemin = "Data/composants/spoiler.cdx";
	unsigned short int idActuel = id + 1; //indique l'id actuellement lu dans le fichier
	
	std::ifstream engine(chemin.c_str());
	
	if(engine==0)
	{
		error("Echec de lecture du fichier spoiler.cdx");	
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
			unsigned short int curseur;
			var.erase(0,var.find_first_of(";")+1);
			
			curseur=var.find_first_of(";");
			std::string modele=var.substr(0,curseur);
			var.erase(0,curseur+1);
			
			curseur=var.find_first_of(";");
			char rang=var[0];
			var.erase(0,curseur+1);
			
			std::string sAerodynamisme=var;

			unsigned short int aerodynamisme;

			std::istringstream iss;
			iss.str(sAerodynamisme);
			if (iss>>aerodynamisme)
			{
			}
			else
			{
				error("Fichier corompu14.");
			}
			
			SpoilerCharge = new Spoiler(modele, rang, aerodynamisme);
		}	
		else
		{
			error("Fichier corompu15.");
		}
	}
	return SpoilerCharge;
}


void Spoiler::infoSpoiler(const unsigned short int& id, unsigned int& prix)
{
	std::string var = ""; //contient les lignes du fichier
	std::string chemin ="Data/composants/spoiler.cdx";	
	std::ifstream engine(chemin.c_str());
	std::istringstream iss;
	unsigned short int idActuel = 0; //indique l'id actuellement lu dans le fichier
	unsigned short int curseur;	
	char rang;

	if(engine==0)
	{
		error("Echec de lecture du fichier spoiler.cdx");	
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
			var.erase(0, curseur + 1);
			
			rang = var[0];
			
			prix =  vRang(rang) * 300 + id * 100;
		}	
		else
		{
			error("Fichier corompu21b.");
		}
	}
}

void Spoiler::infoSpoiler(const unsigned short int& id, std::string& modele, char& rang, unsigned short int& aero, unsigned int& prix)
{
	std::string var = ""; //contient les lignes du fichier
	std::string chemin ="Data/composants/spoiler.cdx";	
	std::ifstream engine(chemin.c_str());
	std::istringstream iss;
	unsigned short int idActuel = 0; //indique l'id actuellement lu dans le fichier
	unsigned short int curseur;	

	if(engine==0)
	{
		error("Echec de lecture du fichier spoiler.cdx");	
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
			modele=var.substr(0,curseur); 
			var.erase(0, curseur + 1);
			
			curseur = var.find_first_of(";");
			rang=var[0]; 
			var.erase(0, curseur + 1);
			
			std::string sAero=var.substr(0,curseur);
			
			iss.clear();
			iss.str(sAero);
			if(iss >> aero)
			{
			}
			else
			{
				error("Fichier corrompu ta mere");
			}  
			
			prix =  vRang(rang) * 300 + id * 200;
			
		}	
		else
		{
			error("Fichier corompu21b.");
		}
	}
}
	
	
	
//Accesseurs et Mutateurs
std::string Spoiler::getNom() const
{
	return m_nom;
}


char Spoiler::getRang() const
{
	return m_rang;
}


unsigned short int Spoiler::getAerodynamisme() const
{
	return m_aerodynamisme;
}



//Methodes
	//Aucune
	
	
	
//Operateurs Methodes
	//Aucun









