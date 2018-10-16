//Profils.cpp
#include "Profil.hh"
#include "Menu.hh"

Profil::Profil(const std::string& uuid, const int& numero, const std::string& nom) : m_uuid(uuid), m_numero(numero), m_nom(nom), m_credits(2000), m_difficulte(3), m_nbBox(1), m_box({0}), m_nbCourses(0), m_victoires(0), m_defaites(0), m_accidents(0), m_creditsGagnes(0), m_voituresAchetees(0), m_nbCoursesCL(0), m_victoiresCL(0), m_defaitesCL(0), m_accidentsCL(0), m_creditsGagnesCL(0), m_sauvegardeAuto(false)
{

}

Profil::Profil(const std::string& uuid, const int& numero, const std::string& nom, const int& credits, const bool& sauvegardeAuto, const int& difficulte, const int& nbBox, const int& nbCourses, const int& victoires, const int& defaites, const int& accidents, const int& creditsGagnes, const int& nbCoursesCL, const int& victoiresCL, const int& defaitesCL, const int& accidentsCL, const int& creditsGagnesCL, const int& voituresAchetees) : m_uuid(uuid), m_numero(numero), m_nom(nom), m_credits(credits), m_difficulte(difficulte), m_nbBox(nbBox), m_box({0}), m_nbCourses(nbCourses), m_victoires(victoires), m_defaites(defaites), m_accidents(accidents), m_creditsGagnes(creditsGagnes), m_voituresAchetees(voituresAchetees), m_nbCoursesCL(nbCoursesCL), m_victoiresCL(victoiresCL), m_defaitesCL(defaitesCL), m_accidentsCL(accidentsCL), m_creditsGagnesCL(creditsGagnesCL), m_sauvegardeAuto(sauvegardeAuto)
{

}

Profil::~Profil()
{
	for (size_t i = 0; i < 5; i++)
	{
		if(m_box[i] != 0 )
		{
			delete m_box[i];
		}
	}
}

bool Profil::compatible(Profil& Player, const int& numeroBox, const char& rangNewPiece)
{
	bool compatible = false;
	int rangPiece = 0;
	int rangVoitureBox = 0;
	Voiture *VoitureBox = Player.getBox(numeroBox);

	rangVoitureBox = vRang(VoitureBox->getRang());
	rangPiece = vRang(rangNewPiece);

	if(rangVoitureBox >= rangPiece)
	{
		compatible = true;
	}
	else
	{
		compatible = false;
	}
	return compatible;
}

void Profil::listerSauvegardes()
{
	int i = 1;
	std::string numeroSave;    // string which will contain the result
	std::string nomProfil;
	std::ostringstream oss;   // stream utilise pour la conversion
	bool ouvert = true;
	do
	{
		oss.str(""); //On vide le contenu de oss
		oss << i;      // on insere le int dans le stream oss
		numeroSave = oss.str(); // range le int dans la variable numeroSave
		std::ifstream fichier( "Saves/Profil" + numeroSave + ".save" );

		if(fichier)
		{
			for (size_t ligne = 1; ligne <= 2; ligne++) //le nom est stocké sur la deuxieme ligne
			{
				getline(fichier, nomProfil);
			}
			Terminal::get() << i << ". Profil " << i << ": " << nomProfil << "\n";
			i++; // on incremente
		}
		else
		{
			ouvert = false;
		}
	}while(ouvert);
	Terminal::get() << "\n"; // on separe le bloc de profils du choix annuler
}

int Profil::compterSauvegardes()
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
 		std::ifstream fichier("Saves/Profil" + numeroSave + ".save");

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

bool Profil::chargerProfil(const int& numeroSave, Profil*& ProfilCharge)
{
	bool statut = false; // true si la lecture de fichier est une reussite, false si elle echoue.
	int ligne = 1;
	int box = 0;
	std::string ligneChargee; //Variable de lecture de ligne

	std::string numeroProfil;
	std::string saveContent = ""; //variable qui contient la totalité d'un fichier de sauvegarde

	std::string stringSaveLock; //string de hash
	std::string stringLockLock; //idem

	std::ostringstream oss;   // stream utilise pour la conversion

	oss << numeroSave;      // on insere le int dans le stream oss
	numeroProfil = oss.str(); // range le int dans la variable numeroSave

	std::string cheminFichier = "Saves/Profil" + numeroProfil + ".save";
	std::string cheminLock = "Saves/Profil" + numeroProfil + ".lock";

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
			int idMoteurCharge;
			int idSpoilerCharge;
			int idPriseAirChargee;
			char rangCharge;
			int nitroMaxChargee;
			int aerodynamismeVoitureCharge;
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

					ProfilCharge = new Profil(uuidCharge, numeroSave, nomCharge, creditsCharges, difficulteChargee, nbBoxCharges, coursesChargees, victoiresChargees, defaitesChargees, accidentsCharges, creditsGagnesCharges, voituresAcheteesChargees, coursesChargeesCL, victoiresChargeesCL, defaitesChargeesCL, accidentsChargesCL, creditsGagnesChargesCL, sauvegardeAuto); // ON construit l'objet charge
					ligne++;
				}
				else if(ligne >= 7 && ligne <= 11)
				{
					 //ligne 6 a 10 - Voiture Box 0 a 4
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
						iss >> idMoteurCharge; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> idSpoilerCharge; // on convertit la string recuperee plus haut en entier
						ligneChargee.erase(0, tailleString + 1); // On retire les pneus charges
						iss.clear(); //on flushe l'objet

						tailleString = ligneChargee.find_first_of(";");
						iss.str(ligneChargee.substr(0, tailleString));
						iss >> idPriseAirChargee; // on convertit la string recuperee plus haut en entier
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
						iss >> aerodynamismeVoitureCharge; // on convertit la string recuperee plus haut en entier
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

						ProfilCharge->setBox(box, marqueChargee, modeleCharge, idMoteurCharge, idSpoilerCharge, idPriseAirChargee, rangCharge, nitroMaxChargee, aerodynamismeVoitureCharge , idTiresCharges, pneusCharges, etat);
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
	return statut;
}

void Profil::supprimerProfil(const int& numeroSave)
{
	bool test;
	bool fail = false;
	std::string numeroProfil;
	std::string numeroNewProfil;
	std::ostringstream oss;   // stream utilise pour la conversion
	std::string cheminFichier;
	std::string newCheminFichier;
	std::string cheminLock;
	std::string newCheminLock;
	int nbSaves = compterSauvegardes();

	oss << numeroSave;      // on insere le int dans le stream oss
	numeroProfil = oss.str(); // range le int dans la variable numeroSave
	cheminFichier = "Saves/Profil" + numeroProfil + ".save";
	cheminLock = "Saves/Profil" + numeroProfil + ".lock";
	if(remove(cheminFichier.c_str()))
	{
		Terminal::get().clearScreen();
		Menu::error("Impossible de supprimer le profil");
		fail = true;
	}
	if(remove(cheminLock.c_str()))
	{
		Terminal::get().clearScreen();
		Menu::error("Impossible de supprimer le verrou du profil");
		fail = true;
	}
	if(nbSaves > numeroSave)
	{
		for (int i = numeroSave; i < nbSaves; i++)
		{
			oss.str("");
			oss << i;      // on insere le int dans le stream oss
			numeroNewProfil = oss.str(); // range le int dans la variable numeroProfil
			newCheminFichier = "Saves/Profil" + numeroNewProfil + ".save";
			newCheminLock = "Saves/Profil" + numeroNewProfil + ".lock";

			oss.str("");
			oss << i + 1;
			numeroNewProfil = oss.str();
			cheminFichier = "Saves/Profil" + numeroNewProfil + ".save";
			cheminLock = "Saves/Profil" + numeroNewProfil + ".lock";

			test = rename(cheminFichier.c_str(), newCheminFichier.c_str()); //On decale toutes les saves d'un cran
			if(test == 1)
			{
				Terminal::get().clearScreen();
				Menu::error("Impossible de renommer les profils suivants.");
				fail = true;
			}
			test = rename(cheminLock.c_str(), newCheminLock.c_str()); //On decale tous les locks d'un cran
			if(test == 1)
			{
				Terminal::get().clearScreen();
				Menu::error("Impossible de renommer les verrous des profils suivants.");
				fail = true;
			}
		}
	}
	if(fail == false)
	{
		Terminal::get().clearScreen();
		Menu::msg("Profil"+numeroProfil+" supprime avec succes !");
	}
}

void Profil::sauvegarderProfil()
{
	std::string sNumeroSave;
	std::string nomFichier;
	std::string nomLock;
	std::ostringstream oss;   // stream utilise pour la conversion int > string

	oss << m_numero;      // on insere le int dans le stream oss
	sNumeroSave = oss.str(); // range le int dans la variable numeroSave
	oss << ""; //equivalent de iss.clear()
	nomFichier = "Saves/Profil" + sNumeroSave + ".save";
	if(1) //on crée un bloc supplémentaire
	{
		std::ofstream save(nomFichier.c_str());
		if(save)	//si la lecture reussit
		{
			save << m_uuid << "\n"; //l'identifiant du profil
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
			save << m_box[i]->getMarque() << ";" << m_box[i]->getModele() << ";" << m_box[i]->getIdMoteur() << ";" << m_box[i]->getIdSpoiler() << ";" << m_box[i]->getIdPriseAir() << ";" << m_box[i]->getRang() << ";" << m_box[i]->getNitroMax() << ";" << m_box[i]->getAerodynamismeVoiture() << ";" << m_box[i]->getIdTires() <<";"<< m_box[i]->getDurabiliteTires() <<";"<< m_box[i]->getEtat() << "\n";
				}
			}
		}
		else
		{
			Menu::error("Impossible d'ecraser le fichier de profil");
		}
	}
	//Une fois la sauvegarde faite on crée le Lock
	nomLock = "Saves/Profil" + sNumeroSave + ".lock";
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
	}
}

void Profil::creerProfil(std::string& nom, Profil*& ProfilCree)
{
	int numeroSave = compterSauvegardes() + 1;
	std::string sNumeroSave;
	std::string nomFichier;
	std::ostringstream oss;

	oss << numeroSave;      // on insere le int dans le stream oss
	sNumeroSave = oss.str(); // range le int dans la variable numeroSave

	nomFichier = "Saves/Profil" + sNumeroSave + ".save";

	std::string uuid = generateUuid(); //On génére un identifiant unique au profil.
	ProfilCree = new Profil(uuid, numeroSave, nom); //On construit le profil cree (la partie boost est la conversion en string de l'uuid)
	Terminal::get().clearScreen();
	Terminal::get() << "Creation de votre Profil\n";
	Terminal::get() << "===============\n\n";
	Terminal::get() << "Profil" << numeroSave << " cree avec succes !\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Appuyez sur Entree pour continuer...\n";
	getch();
}

std::string Profil::getUuid() const
{
	return m_uuid;
}

int Profil::getNumero() const
{
	return m_numero;
}

std::string Profil::getNom() const
{
	return m_nom;
}

int Profil::getCredits() const
{
	return m_credits;
}

int Profil::getNbBox() const
{
	return m_nbBox;
}

Voiture* Profil::getBox(const int& numeroBox) const
{
	return m_box[numeroBox];
}

int Profil::getNbCourses() const
{
	return m_nbCourses;
}

int Profil::getVictoires() const
{
	return m_victoires;
}

int Profil::getDefaites() const
{
	return m_defaites;
}

int Profil::getAccidents() const
{
	return m_accidents;
}

float Profil::getVDRatio() const
{
	float ratio;
	if( m_defaites != 0)
	{
		ratio = static_cast<int>(m_victoires / m_defaites);
	}
	else
	{
		ratio = m_victoires;
	}
	return ratio;
}

int Profil::getCreditsGagnes() const
{
	return m_creditsGagnes;
}

int Profil::getVoituresAchetees() const
{
	return m_voituresAchetees;
}


int Profil::getDifficulte() const
{
	return m_difficulte;
}


bool Profil::getSauvegardeAuto() const
{
	return m_sauvegardeAuto;
}

std::string Profil::getDifficulteString() const
{
	std::string difficulte;

	if(m_difficulte==1)
	{
		difficulte = "DEBUTANT";
	}
	else if(m_difficulte==2)
	{
		difficulte = "FACILE";
	}
	else if(m_difficulte==3)
	{
		difficulte = "NORMAL";
	}
	else if(m_difficulte==4)
	{
		difficulte = "DIFFICILE";
	}
	else
	{
		difficulte = "EXPERT";
	}

	return difficulte;
}

void Profil::setBox(const int& numeroBox, const std::string& marque, const std::string& modele, const int& idMoteur, const int& idSpoiler, const int& idPriseAir, const char& rang, const int& nitroMax, const int& aerodynamismeVoiture, const int& idTires, const int& pneus, const int& etat)
{
	m_box[numeroBox] = new Voiture(marque, modele, idMoteur, idSpoiler, idPriseAir, rang, nitroMax, aerodynamismeVoiture, idTires, pneus, etat);
}

void Profil::setBox(const int& numeroBox, Voiture* Voiture)
{
	m_box[numeroBox] = Voiture;
}

void Profil::setBox(const int& numeroBox)
{
	m_box[numeroBox] = 0;
}

void  Profil::setMoteurVoiture(const int& numeroBox, Moteur* newMoteur, const int& idMoteur)
{
	m_box[numeroBox]->setMoteur(newMoteur, idMoteur);
}

void Profil::setDifficulte(const int& newDifficulte)
{
	m_difficulte = newDifficulte;
}


void Profil::setSauvegardeAuto(const bool& valeur)
{
	m_sauvegardeAuto = valeur;
}


void Profil::ajouterCreditsGagnes(const int& somme)
{
	m_creditsGagnes += somme;
}

void Profil::ajouterVoitureAchetee()
{
	m_voituresAchetees++;
}

void Profil::ajouterCredits(const int& somme)
{
	m_credits += somme;
}

void Profil::ajouterCourse()
{
	m_nbCourses++;
}

void Profil::ajouterVictoire()
{
	m_victoires++;
}

void Profil::ajouterDefaite()
{
	m_defaites++;
}

void Profil::ajouterAccident()
{
	m_accidents++;
}

bool Profil::boxVide(int numeroBox)
{
	bool vide;
	if(m_box[numeroBox] == 0)
	{
		vide = true;
	}
	else
	{
		vide = false;
	}
	return vide;
}

void Profil::acheterBox()
{
	bool paye;
	std::string sNbBox;
	std::ostringstream oss;   // stream utilise pour la conversion

	paye = payer(m_nbBox * 20000);
	if(paye == true)
	{
		m_nbBox += 1;

		oss << m_nbBox;      // on insere le int dans le stream oss
		sNbBox = oss.str(); // range le int dans la variable numeroSave
		Menu::msg("Box "+sNbBox+" achete avec succes !");
	}
}

void Profil::changerNom(const std::string& newNom)
{
	m_nom = newNom;
}

bool Profil::payer(const int& prix)
{
	bool paye;
	if(prix > m_credits)
	{
		Menu::error("Vous ne disposez pas d'assez de Credits !");
		paye = false;
	}
	else
	{
		m_credits -= prix;
		paye = true;
	}
	return paye;
}

bool operator!=(Profil& Player, Profil& Player2)
{
	bool modifie = false;
	bool boxModifie[5] = { false };
	Voiture* Voiture1 = 0;
	Voiture* Voiture2 = 0;

	if(Player.getUuid() == Player2.getUuid() && Player.getNumero() == Player2.getNumero() && Player.getNom() == Player2.getNom() && Player.getCredits() == Player2.getCredits() && Player.getNbBox() == Player2.getNbBox() && Player.getNbCourses() == Player2.getNbCourses() && Player.getVictoires() == Player2.getVictoires() && Player.getDefaites() == Player2.getDefaites() && Player.getAccidents() == Player2.getAccidents() && Player.getCreditsGagnes() == Player2.getCreditsGagnes() && Player.getVoituresAchetees() == Player2.getVoituresAchetees() && Player.getDifficulte() == Player2.getDifficulte() && Player.getSauvegardeAuto() == Player2.getSauvegardeAuto()) //On utilise les accesseurs pour comparer
	{
		for (int numeroBox = 0; numeroBox < Player.getNbBox(); numeroBox++)
		{
			Voiture1 = Player.getBox(numeroBox);
			Voiture2 = Player.getBox(numeroBox);
			if(Voiture1 != 0)
			{
				if(Voiture1->getMarque() == Voiture2->getMarque() && Voiture1->getModele() == Voiture2->getModele() && Voiture1->getRang() == Voiture2->getRang() && (Voiture1->getAcceleration() - Voiture2->getAcceleration()) < FLT_EPSILON && (Voiture1->getVitesse() - Voiture2->getVitesse()) < FLT_EPSILON && (Voiture1->getAerodynamisme() - Voiture2->getAerodynamisme()) < FLT_EPSILON && Voiture1->getDurabiliteTires() == Voiture2->getDurabiliteTires() && (Voiture1->getAccelerationMoteur() - Voiture2->getAccelerationMoteur()) < FLT_EPSILON && (Voiture1->getVitesseMoteur() - Voiture2->getVitesseMoteur()) < FLT_EPSILON && Voiture1->getNomMoteur() == Voiture2->getNomMoteur())
				{
					boxModifie[numeroBox] = false; //Attributs et voiture identiques dans la partie et le fichier.
				}
				else
				{
					boxModifie[numeroBox] = true;
				}
			}
			else
			{
				if(Player.getBox(numeroBox) == Player.getBox(numeroBox))
				{
					boxModifie[numeroBox] = false;
				}
				else
				{
					boxModifie[numeroBox] = true;
				}
			}
		}
		if(boxModifie[0] == true || boxModifie[1] == true || boxModifie[2] == true || boxModifie[3] == true || boxModifie[4] == true) //Si l'un des boxs est modifié
		{
			modifie = true;
		}
		else
		{
			modifie = false;
		}
	}
	else
	{
		modifie = true;
	}
	return modifie;
}