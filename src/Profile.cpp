//Profiles.cpp
#include "Profile.hh"
#include "Menu.hh"

Profile::Profile(const json &data)
 : name(data["name"].get<std::string>()), difficulty(data["difficulty"].get<int>()), credits(data["credits"].get<int>()), garage(data["garage"])
{

}

Profile::~Profile()
{
}

Profile Profile::load(const std::string &path)
{
	DataFile save(path);

	if (!save.load())
	{
		throw std::runtime_error("Cannot load collection file:"+path);
	}
	return (Profile(save.getData()));
}

bool Profile::compatible(Profile& Player, const int& numeroBox, const char& rangNewPiece)
{
	bool compatible = false;
	int rangPiece = 0;
	int rangCarBox = 0;
	//Car *CarBox = Player.getBox(numeroBox);

	//rangCarBox = vRang(CarBox->rank);
	rangPiece = vRang(rangNewPiece);

	if(rangCarBox <= rangPiece)
	{
		compatible = true;
	}
	else
	{
		compatible = false;
	}
	return compatible;
}

void Profile::listerSauvegardes()
{
	int i = 1;
	std::string numeroSave;    // string which will contain the result
	std::string nomProfile;
	std::ostringstream oss;   // stream utilise pour la conversion
	bool ouvert = true;
	do
	{
		oss.str(""); //On vide le contenu de oss
		oss << i;      // on insere le int dans le stream oss
		numeroSave = oss.str(); // range le int dans la variable numeroSave
		std::ifstream fichier( "Saves/Profile" + numeroSave + ".save" );

		if(fichier)
		{
			for (size_t ligne = 1; ligne <= 2; ligne++) //le nom est stocké sur la deuxieme ligne
			{
				getline(fichier, nomProfile);
			}
			Terminal::get() << i << ". Profile " << i << ": " << nomProfile << "\n";
			i++; // on incremente
		}
		else
		{
			ouvert = false;
		}
	}while(ouvert);
	Terminal::get() << "\n"; // on separe le bloc de Profiles du choix annuler
}

int Profile::compterSauvegardes()
{
	int i = 1;
	std::string numeroSave;          // string which will contain the result
	std::ostringstream oss;   // stream utilise pour la conversion
	bool ouvert = true;

	do
	{
		oss.str(""); //On vide le contenu de oss
		oss << i;      // on insere le int dans le stream oss
		numeroSave = oss.str(); // range le int dans la variable numeroSave
 		std::ifstream fichier("Saves/Profile" + numeroSave + ".save");

		if(fichier)
		{
			i++; // on incremente
		}
		else
		{
			ouvert = false;
		}
	}while(ouvert);
	return i - 1; //Un tour de test supplementaire est fait, d'ou le -1
}

bool Profile::chargerProfile(const int& numeroSave, Profile*& ProfileCharge)
{
	/*
	bool statut = false; // true si la lecture de fichier est une reussite, false si elle echoue.
	int ligne = 1;
	int box = 0;
	std::string ligneChargee; //Variable de lecture de ligne

	std::string numeroProfile;
	std::string saveContent = ""; //variable qui contient la totalité d'un fichier de sauvegarde

	std::string stringSaveLock; //string de hash
	std::string stringLockLock; //idem

	std::ostringstream oss;   // stream utilise pour la conversion

	oss << numeroSave;      // on insere le int dans le stream oss
	numeroProfile = oss.str(); // range le int dans la variable numeroSave

	std::string cheminFichier = "Saves/Profile" + numeroProfile + ".save";
	std::string cheminLock = "Saves/Profile" + numeroProfile + ".lock";

	std::ifstream save(cheminFichier.c_str());

	std::ifstream lockFichier(cheminLock.c_str());

	if(!save) //Si la lecture echoue
	{
		Menu::error("Echec de lecture du fichier de sauvegarde");
		statut = false; //Le fichier ne peut être charge, donc la fonction renvoie un echec
	}
	else if(!lockFichier)
	{
		Menu::error("Echec de lecture du fichier de verouillage de la sauvegarde");
		statut = false; //Le fichier ne peut être charge, donc la fonction renvoie un echec
	}
	else
	{
		//On assigne les valeurs aux différents hashs.
		getline(lockFichier, stringLockLock); //On recupere le contenu dans le lock

		Terminal::get() << saveContent;
		stringSaveLock = getHashFromFile(cheminFichier); //On recupere le hash du fichier

		if(stringSaveLock != stringLockLock) //On compare
		{
			Menu::error("Fichier de sauvegarde inutilisable.");
			statut = false; //Le fichier ne peut être charge, donc la fonction renvoie un echec
		}
		else
		{
			std::istringstream iss; //Objet de conversion String > int

			//variables de chargement
			int tailleString;

			std::string uuidCharge;
			std::string nomCharge;
			int creditsCharges;
			int difficulteChargee;
			int nbBoxCharges;

			int coursesChargees;
			int victoiresChargees;
			int defaitesChargees;
			int accidentsCharges;
			int creditsGagnesCharges;

			int coursesChargeesCL;
			int victoiresChargeesCL;
			int defaitesChargeesCL;
			int accidentsChargesCL;
			int creditsGagnesChargesCL;

			int voituresAcheteesChargees;
			bool sauvegardeAuto;

			//Chargement voitures/box
			std::string marqueChargee;
			std::string modeleCharge;
			int idEngineCharge;
			int idSpoilerCharge;
			int idAirIntakeChargee;
			char rangCharge;
			int nitroMaxChargee;
			int aerodynamismeCarCharge;
			int idTiresCharges;
			int pneusCharges;
			int etat;

			while(getline(save, ligneChargee))
			{
				if(ligne == 1)
				{
					//ligne 1 - uuid (id unique)
					uuidCharge = ligneChargee;
					ligne++;
				}
				else if(ligne == 2)
				{
					//ligne 2 - nom
					nomCharge = ligneChargee;
					ligne++;
				}
				else if(ligne == 3)
				{
					 //ligne 3 - credits
					iss.str(ligneChargee); // On extrait une variable et on la stocke dans la variable de conversion "iss".
					iss >> creditsCharges; // on convertit la string recuperee plus haut en entier
					iss.clear(); //on flushe l'objet
					ligne++;
				}
				else if(ligne == 4)
				{
					//ligne 4 - sauvegarde auto, Difficulte;nombre de box possedes
					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee);
					iss >> sauvegardeAuto;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee);
					iss >> difficulteChargee;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee);
					iss >> nbBoxCharges;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					ligne++;
				}
				else if(ligne == 5)
				{
					 //ligne 5 - victoires;defaites;accidents
					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> coursesChargees;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> victoiresChargees;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> defaitesChargees;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> accidentsCharges;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> creditsGagnesCharges;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> voituresAcheteesChargees;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					ligne++;
				}
				else if(ligne == 6)
				{
					 //ligne 5 - victoires;defaites;accidents
					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> coursesChargeesCL;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> victoiresChargeesCL;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> defaitesChargeesCL;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> accidentsChargesCL;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> creditsGagnesChargesCL;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					tailleString = ligneChargee.find_first_of(";");
					iss.str(ligneChargee.substr(0, tailleString));
					iss >> voituresAcheteesChargees;
					iss.clear();
					ligneChargee.erase(0, tailleString + 1);

					ProfileCharge = new Profile(uuidCharge, numeroSave, nomCharge, creditsCharges, difficulteChargee, nbBoxCharges, coursesChargees, victoiresChargees, defaitesChargees, accidentsCharges, creditsGagnesCharges, voituresAcheteesChargees, coursesChargeesCL, victoiresChargeesCL, defaitesChargeesCL, accidentsChargesCL, creditsGagnesChargesCL, sauvegardeAuto); // ON construit l'objet charge
					ligne++;
				}
				else if(ligne >= 7 && ligne <= 11)
				{
					 //ligne 6 a 10 - Car Box 0 a 4
					if(ligneChargee[0] != 0)
					{
						tailleString = ligneChargee.find_first_of(";"); //find first of recherche la position du premier point virgule
						marqueChargee = ligneChargee.substr(0, tailleString);
						ligneChargee.erase(0, tailleString + 1); // On retire la marque charge

						tailleString = ligneChargee.find_first_of(";");
						modeleCharge = ligneChargee.substr(0, tailleString);
						ligneChargee.erase(0, tailleString + 1); // On retire le modele charge

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> idEngineCharge; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> idSpoilerCharge; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> idAirIntakeChargee; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						rangCharge = ligneChargee[0];
						ligneChargee.erase(0, 2); // On retire le rang charge

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> nitroMaxChargee; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> aerodynamismeCarCharge; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> idTiresCharges; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire la durabilité des pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> pneusCharges; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> etat; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						ProfileCharge->setBox(box, marqueChargee, modeleCharge, idEngineCharge, idSpoilerCharge, idAirIntakeChargee, rangCharge, nitroMaxChargee, aerodynamismeCarCharge , idTiresCharges, etat);
						box++;
						ligne++;
					}
					else
					{
						box++;
						ligne++;
					}
				}
			}
		}
		ligne -= 1; //On remet la valeur de ligne au nombre exact lu
		if(ligne == 11)
		{
			statut = true; //tout c'est bien passe
		}
		else
		{
			statut = false; //echec du chargement
			Menu::error("Fichier de sauvegarde corrompu.");
		}
	}
	return statut;*/
}

void Profile::supprimerProfile(const int& numeroSave)
{
	bool test;
	bool fail = false;
	std::string numeroProfile;
	std::string numeroNewProfile;
	std::ostringstream oss;   // stream utilise pour la conversion
	std::string cheminFichier;
	std::string newCheminFichier;
	std::string cheminLock;
	std::string newCheminLock;
	int nbSaves = compterSauvegardes();

	oss << numeroSave;      // on insere le int dans le stream oss
	numeroProfile = oss.str(); // range le int dans la variable numeroSave
	cheminFichier = "Saves/Profile" + numeroProfile + ".save";
	cheminLock = "Saves/Profile" + numeroProfile + ".lock";
	if(remove(cheminFichier.c_str()))
	{
		Terminal::get().clearScreen();
		Menu::error("Impossible de supprimer le Profile");
		fail = true;
	}
	if(remove(cheminLock.c_str()))
	{
		Terminal::get().clearScreen();
		Menu::error("Impossible de supprimer le verrou du Profile");
		fail = true;
	}
	if(nbSaves > numeroSave)
	{
		for (int i = numeroSave; i < nbSaves; i++)
		{
			oss.str("");
			oss << i;      // on insere le int dans le stream oss
			numeroNewProfile = oss.str(); // range le int dans la variable numeroProfile
			newCheminFichier = "Saves/Profile" + numeroNewProfile + ".save";
			newCheminLock = "Saves/Profile" + numeroNewProfile + ".lock";

			oss.str("");
			oss << i + 1;
			numeroNewProfile = oss.str();
			cheminFichier = "Saves/Profile" + numeroNewProfile + ".save";
			cheminLock = "Saves/Profile" + numeroNewProfile + ".lock";

			test = rename(cheminFichier.c_str(), newCheminFichier.c_str()); //On decale toutes les saves d'un cran
			if(test == 1)
			{
				Terminal::get().clearScreen();
				Menu::error("Impossible de renommer les Profiles suivants.");
				fail = true;
			}
			test = rename(cheminLock.c_str(), newCheminLock.c_str()); //On decale tous les locks d'un cran
			if(test == 1)
			{
				Terminal::get().clearScreen();
				Menu::error("Impossible de renommer les verrous des Profiles suivants.");
				fail = true;
			}
		}
	}
	if(fail == false)
	{
		Terminal::get().clearScreen();
		Menu::msg("Profile"+numeroProfile+" supprime avec succes !");
	}
}

void Profile::sauvegarderProfile()
{
	/*
	std::string sNumeroSave;
	std::string nomFichier;
	std::string nomLock;
	std::ostringstream oss;   // stream utilise pour la conversion int > string

	oss << m_numero;      // on insere le int dans le stream oss
	sNumeroSave = oss.str(); // range le int dans la variable numeroSave
	oss << ""; //equivalent de iss.clear()
	nomFichier = "Saves/Profile" + sNumeroSave + ".save";
	if(1) //on crée un bloc supplémentaire
	{
		std::ofstream save(nomFichier.c_str());
		if(save)	//si la lecture reussit
		{
			save << m_uuid << "\n"; //l'identifiant du Profile
			save << m_nom << "\n"; // le nom
			save << m_credits << "\n"; // les credits
			save << m_sauvegardeAuto << ";"<< m_difficulte << ";" << m_nbBox << "\n"; //Difficulté / Nombre de box deverouillés
			save << m_nbCourses << ";" << m_victoires << ";" << m_defaites << ";" << m_accidents << ";" << m_creditsGagnes << ";" << m_voituresAchetees << "\n"; //On inscrit les stats totaux dans le fichier
			save << m_nbCoursesCL << ";" << m_victoiresCL << ";" << m_defaitesCL << ";" << m_accidentsCL << ";" << m_creditsGagnesCL << "\n"; //On inscrit les stats totaux dans le fichier
			for (size_t i = 0; i < 5; i++)
			{
				if(m_box[i] == 0)
				{
					save << "0" << "\n";
				}
				else
				{
					//save << m_box[i]->manufacturer << ";" << m_box[i]->name << ";" << m_box[i]->getIdEngine() << ";" << m_box[i]->getIdSpoiler() << ";" << m_box[i]->getIdAirIntake() << ";" << m_box[i]->rank << ";" << m_box[i]->getNitroMax() << ";" << m_box[i]->getAerodynamismeCar() << ";" << m_box[i]->getIdTires() <<";"<< m_box[i]->getTires()->getDurability() <<";"<< m_box[i]->getEtat() << "\n";
				}
			}
		}
		else
		{
			Menu::error("Impossible d'ecraser le fichier de Profile");
		}
	}
	//Une fois la sauvegarde faite on crée le Lock
	nomLock = "Saves/Profile" + sNumeroSave + ".lock";
	std::ofstream lock(nomLock.c_str()); //flux d'écriture dans le lock
	std::string ligneChargee;
	std::string saveContent;

	if(!lock)
	{
		Menu::error("Impossible de lire le lock en ecriture.");
	}
	else
	{
		lock << getHashFromFile(nomFichier); //On inscrit le lock dans le fichier
	}*/
}

void Profile::creerProfile(std::string& nom, Profile*& ProfileCree)
{
	/*
	int numeroSave = compterSauvegardes() + 1;
	std::string sNumeroSave;
	std::string nomFichier;
	std::ostringstream oss;

	oss << numeroSave;      // on insere le int dans le stream oss
	sNumeroSave = oss.str(); // range le int dans la variable numeroSave

	nomFichier = "Saves/Profile" + sNumeroSave + ".save";

	std::string uuid = generateUuid(); //On génére un identifiant unique au Profile.
	ProfileCree = new Profile(uuid, numeroSave, nom); //On construit le Profile cree (la partie boost est la conversion en string de l'uuid)
	*/
	Terminal::get().clearScreen();
	Terminal::get() << "Creation de votre Profile\n";
	Terminal::get() << "===============\n\n";
	Terminal::get() << "Profile cree avec succes !\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Appuyez sur Entree pour continuer...\n";
	getch();
}


bool Profile::payer(const int& prix)
{
	bool paye;
	if(prix > credits)
	{
		Menu::error("Vous ne disposez pas d'assez de Credits !");
		paye = false;
	}
	else
	{
		credits -= prix;
		paye = true;
	}
	return paye;
}