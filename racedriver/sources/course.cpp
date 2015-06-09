
//course.cpp

#include"course.h"

bool preparatifsCourse(const Circuit& Map, const Profil& Player, Voiture*& VoiturePlayer, unsigned short int const& prix)
{
	unsigned short int prixCourse;
	bool paye = false;

	prixCourse = (VoiturePlayer->getConsommation() * 0.01f * Map.getTaille() * VoiturePlayer->getPrixCarburantMoteur());
	prixCourse += prix;

	if(Player.getCredits() < prixCourse)
	{
		error("Vous ne disposez pas d'assez de crédits pour payer les preparatifs.");
	}
	else
	{
		char verif;
		do
		{
			clrscreen(); //On flushe l'ancien ecran
			if(VoiturePlayer->getNiveauNitro() < VoiturePlayer->getNitroMax())
			{ 
				msg("Attention: Votre reservoir de nitro n'est pas plein.\n");	
			}
			if(VoiturePlayer->getDurabilitePneus() < 55)
			{ 
				msg("Attention: Pneus deteriores.\n");	
			}
			std::cout << "\nPreparatifs\n";
			std::cout << "====================\n";
			std::cout << "Credits: " << Player.getCredits() << "c\n";
			std::cout << "====================\n";
			std::cout << "Le montant total des preparatifs du circuit: " << Map.getNom() << "\n";
			std::cout << "S'elevent a " << prixCourse << "c\n\n";
			std::cout << "Souhaitez-vous vraiment faire cette course ? [O/n]\n";
			std::cout << "====================\n";
			std::cin >> verif;
			videKBuffer();
			if(verif == 'o' || verif == 'N')
			{
					clrscreen();
					paye = true;
			}
			else if(verif == 'o' || verif == 'N')
			{
					clrscreen();
					paye = false;
					error("Paiement annule par l'utilisateur");
			}
			else
			{
					clrscreen();
					saisieInvalide();
			} 
		}while(verif != 'o' && verif != 'N' && verif != 'o' && verif != 'N');
	}
	return paye;
}

std::string randNomAdversaire()
{
	std::string nomAdversaire;
	unsigned short int nbAdversaires = 0;
	unsigned short int ligneALire;

	if(1) //On separe les deux flux par un bloc
	{
		std::ifstream pilotestxt("Data/console/pilotes.txt");

		if(pilotestxt)
		{
			while(std::getline(pilotestxt, nomAdversaire))
			{
				nbAdversaires++;
			}
		}
	}
	std::ifstream pilotestxt("Data/console/pilotes.txt");

	if(pilotestxt == 0)
	{
		error("Echec de lecture du fichier pilotes.txt");
	}
	else
	{
		ligneALire = std::rand()%nbAdversaires; // on randomise
		for(unsigned short int ligne = 0; ligne <= ligneALire; ligne++)
		{
			std::getline(pilotestxt, nomAdversaire);
			nomAdversaire.erase(nomAdversaire.size() - 1, nomAdversaire.size()); //On delete le caractère de retour a la ligne
		}
	}
	
	return nomAdversaire;
}

bool antiCorruption(const std::string& chemin, const unsigned short int& nbLignes)
{
	unsigned short int lignesTotales = 0;
	std::string contenueLigne;

	std::ifstream fichier(chemin.c_str());

	if(fichier)
	{
		while(std::getline(fichier, contenueLigne))
		{
			lignesTotales++;
		}
	}
	else
	{
		error("Echec de lecture du fichier");
	}

	if(lignesTotales < nbLignes)
	{
		return false;
	}
	else
	{
		return true;
	}
}


void chargerAdversaires(Voiture* Adversaire[7], unsigned short int difficulteProfil, unsigned short int difficulteCircuit)
{
	unsigned short int randomDifficulte;	//difficulté calculée en fonction de la difficulté du joueur
	unsigned short int difficulteTotale;	//difficulté pour calculer l'id et le rang de la voiture
	char compteurRang= 'D';				//rang, en fonction de la difficulté totale
	unsigned short int compteur = 0;		//permet de compter l'id de la voiture en fonction du fichier
	unsigned short int id = compteur;
	std::string temp;					//permet de stocker une ligne pour compter les lignes
	
	difficulteProfil *= (difficulteCircuit / 10);
	
	for(unsigned short int joueur = 0; joueur <= 6; ++joueur)
	{
		if(std::rand() % 2 == 0)	// 1/2 chances d'augmenter ou diminuer la difficulté du joueur
		{
			randomDifficulte = difficulteProfil - std::rand() % (difficulteProfil +1);
		}
		else
		{
			randomDifficulte = difficulteProfil + std::rand() % (difficulteProfil +1);
		}
		
		if(std::rand() % 2 == 0)	// 1/2 chances d'augmenter ou diminuer la difficulté du circuit
		{
			difficulteCircuit = difficulteCircuit - std::rand() % ((difficulteCircuit/10) +1);
		}
		else
		{
			difficulteCircuit = difficulteCircuit + std::rand() % ((difficulteCircuit/10) +1);
		}
		
		difficulteTotale = randomDifficulte + difficulteCircuit;

		std::ifstream D("Data/Voitures/D.cdx");
		std::ifstream C("Data/Voitures/C.cdx");
		std::ifstream B("Data/Voitures/B.cdx");
		std::ifstream A("Data/Voitures/A.cdx");
		std::ifstream S("Data/Voitures/S.cdx");
		
		if(difficulteTotale == 0)	//la difficulté peut valoir 0, et il ne faut pas car aucune voiture n'as 0 comme id
		{
			difficulteTotale = 1;
		}
		
		//on calcule le rang
		while(std::getline(D, temp) && (compteur < difficulteTotale))
		{
			compteurRang='D';
			++compteur;
			++id;			
		}
		C.seekg(0, std::ios::end);
		if(compteur<difficulteTotale && C.tellg() != 0)
		{
			C.seekg(0, std::ios::beg);
			id=0;
			while(std::getline(C, temp) && (compteur < difficulteTotale))
			{
				compteurRang='C';
				++compteur;	
				++id;		
			}
		}
		B.seekg(0, std::ios::end);
		if(compteur<difficulteTotale && B.tellg() != 0)
		{
			B.seekg(0, std::ios::beg);
			id=0;
			while(std::getline(B, temp) && (compteur < difficulteTotale))
			{
				compteurRang='B';
				++compteur;	
				++id;		
			}
		}
		A.seekg(0, std::ios::end);
		if(compteur<difficulteTotale && A.tellg() != 0)
		{
			A.seekg(0, std::ios::beg);
			id=0;
			while(std::getline(A, temp) && (compteur < difficulteTotale))
			{
				compteurRang='A';
				++compteur;	
				++id;		
			}
		}
		S.seekg(0, std::ios::end);
		if(compteur<difficulteTotale && S.tellg() != 0)
		{
			S.seekg(0, std::ios::beg);
			id=0;
			while(std::getline(S, temp) && (compteur < difficulteTotale))
			{
				compteurRang='S';
				++compteur;
				++id;			
			}
		}
		
		Adversaire[joueur] = Voiture::chargerVoiture(id, compteurRang);	//on instancie la voiture
		compteur = 0;	//on remet a 0 pour le joueur suivant
		id=0;		//on remet a 0 pour le joueur suivant
	}
}


void chargerMessagesAccidents(std::string messageAccident[8])
{
	unsigned short int random;
	unsigned short int exclu[8];
	unsigned short int nbLignes=0;
	
	if(1)
	{
		std::ifstream fichier("Data/console/accident.txt");
		while(std::getline(fichier, messageAccident[0]))
		{
			++nbLignes;
		}
	}
		
	for(unsigned short int compteur=0; compteur <=7; ++compteur)
	{
		std::ifstream fichier("Data/console/accident.txt");
		random = std::rand()%(nbLignes +1);
	
		while(random == exclu[0] || random == exclu[1] || random == exclu[2] || random == exclu[3] || random == exclu[4] || random == exclu[5] || random == exclu[6] || random == exclu[7])
		{
				random = std::rand()%(nbLignes +1);
		}
		
		exclu[compteur] = random;
	
		for(unsigned short int ligne = 1; ligne <=random; ++ligne)
		{
			std::getline(fichier, messageAccident[compteur]);
		}	
	}
}


std::string* chargerCommentaireMeteo(const unsigned short int& meteo)
{
	unsigned short int ligneSoleil = 0;
	unsigned short int lignePluie = 0;
	unsigned short int ligneNeige = 0;
	unsigned short int ligneGlace = 0;
	std::string *ligne = new std::string;
	size_t curseur;
	unsigned short int random;
	if(1)
	{
		std::ifstream fichier("Data/console/meteo.txt");
		
		while(std::getline(fichier, *ligne))
		{
			curseur = ligne->find_first_of(";");
			if(ligne->substr(0,curseur) == "1" && lignePluie == 0 && ligneNeige == 0 && ligneGlace == 0)
			{
				++ligneSoleil;
			}
			else if(ligne->substr(0,curseur) == "2" && ligneNeige == 0 && ligneGlace == 0)
			{
				++lignePluie;
			}
			else if(ligne->substr(0,curseur) == "3" && ligneGlace == 0)
			{
				++ligneNeige;
			}
			else if(ligne->substr(0,curseur) == "4")
			{
				++ligneGlace;
			}
			else
			{
				error("Le fichier meteo.txt est corrompu. Verifiez qu'il y ait des messages pour toutes les meteos (1,2,3,4), et qu'ils soient dans l'ordre croissant.");
				ligne->erase();
				ligne=0;
			}
		}
	}
	if(meteo == 1)
	{
		random = std::rand()%(ligneSoleil+1) ;
	}
	else if(meteo == 2)
	{
		random = (std::rand()%(lignePluie - ligneSoleil +1)) + ligneSoleil;
	}
	else if(meteo == 3)
	{
		random = (std::rand()%(ligneNeige - lignePluie+1)) + ligneNeige;
	}
	else
	{
		random = (std::rand()%(ligneGlace - ligneNeige+1)) + ligneGlace; 
	}
	random += 1;
	
	std::ifstream fichier("Data/console/meteo.txt");
	for(unsigned short int compteur = 1; compteur < random; ++compteur)
	{
		std::getline(fichier, *ligne);
	}
	ligne->erase(0,2);
	return ligne;//ligne est un pointeur pour qu'il y ait une erreur de segmentation si meteo.txt est mal rempli.
}


void calculerScore(unsigned short int score[8], Voiture* Adversaire[7], const Voiture* Player1, const Circuit& Map)
{
	score[0]=((Player1->getVitesse()/2)+(Player1->getAcceleration()*2/Map.getVirages()))*((std::rand()%26)+75)/100;
	
	for(unsigned short int i = 1; i <=6; i++)
	{
		score[i]=((Adversaire[i]->getVitesse()/2)+(Adversaire[i]->getAcceleration()*2/Map.getVirages()))*((std::rand()%26)+75)/100;
	}
}


void calculerProbaAccident(unsigned short int probaAccident[8], Voiture* Adversaire[7], const Voiture* Player1, const Circuit Map)
{
	probaAccident[0]=((((Map.getVirages()*Map.getMeteo())/(Player1->getDurabilitePneus()/8))+(Map.getVent()/(Player1->getAerodynamisme()*0.75)))/2) + std::rand()%5;
	
	for(unsigned short int i = 1; i <=6; i++)
	{
		probaAccident[i]=((((Map.getVirages()*Map.getMeteo())/(Adversaire[i]->getDurabilitePneus()/8))+(Map.getVent()/(Adversaire[i]->getAerodynamisme()*0.75)))/2) + std::rand()%5;
	}
}


void faireCourseLibre(Circuit Map, Voiture* Player1, Profil& Player)
{
	if(Player1 == 0)
	{
		error("Vous n'avez pas de voiture disponible !");
	}
	else if(antiCorruption("Data/console/pilotes.txt", 7) == false)
	{
		error("Le fichier pilotes.txt ne contient pas assez d'informations.");
	}
	else if(antiCorruption("Data/console/accident.txt", 8) == false)
	{
		error("Le fichier accident.txt ne contient pas assez d'informations.");
	}
	else if(Player1->getEtat() < 20)
	{
		error("Votre vehicule est trop endommage pour concourir.");
	}
	else if(Player1->getDurabilitePneus() < 15)
	{
		error("Vos pneus sont trop uses pour concourir.");
	}
	else //Si tout va bien
	{
		if(Player1->getNiveauNitro() < Player1->getNitroMax())
		{ 
			msg("Attention: Votre reservoir de nitro n'est pas plein.\n");	
		}
		if(Player1->getDurabilitePneus() < 55)
		{ 
			msg("Attention: Pneus deteriores.\n");	
		}
		
		Voiture* Adversaire[7];
		chargerAdversaires(Adversaire, Player.getDifficulte(), Map.getDifficulte());
		
		std::string *commentaireMeteo = chargerCommentaireMeteo(Map.getMeteo());
		
		std::string messageAccident[8];
		chargerMessagesAccidents(messageAccident);
		
		//On initialise les noms des adversaires
		std::string nomJoueur[7];
		std::string pseudo;
		
		for(unsigned short int numero = 0; numero <= 6; numero++) 
		{
			pseudo = randNomAdversaire(); //On randomise un nom dans le tableau pseudo.
			while(pseudo == nomJoueur[0] || pseudo == nomJoueur[1] || pseudo == nomJoueur[2] || pseudo == nomJoueur[3] || pseudo == nomJoueur[4] || pseudo == nomJoueur[5] || pseudo == nomJoueur[6])
			{
				pseudo = randNomAdversaire(); //Tant que le pseudo a deja été tiré, on re-genere un nouveau
			}
			nomJoueur[numero] = pseudo;
		}
		
		
		std::cout << "Bienvenue à tous et a toutes ! Aujourd'hui va se derouler l'evenement tant attendu par tous les fans de sportives, tout le monde s'est reuni et l'ambiance est a son comble sur le circuit: " << Map.getNom() << ".\nOn m'annonce qu'il totalise " << Map.getTaille() << " Km, et comprend pas moins de " << Map.getVirages() << " virages serres !\n" << *commentaireMeteo << " D'autre part, il y a un vent de Force " << Map.getVent() << " dans l'enceinte du circuit.\n\nSans attendre passons tout de suite a la liste des Participants:\n\n";
				
		//on liste les concurants		
		for(unsigned short int numero = 0; numero <= 7; numero++)
		{
			if(numero == 0)
			{
				std::cout << Player.getNom() << " - " << Player1->getMarque() << " " << Player1->getModele() << "\n";
			}
			else
			{
				std::cout << nomJoueur[numero - 1] << " - " << Adversaire[numero - 1]->getMarque() << " " << Adversaire[numero - 1]->getModele() << "\n";
			}
		}
		
		
		delete commentaireMeteo;
		std::cout<<"\n\nPressez [ENTREE] pour commencer la course.\n";
		videKBuffer();	
		
		clrscreen();
		msg("Depart dans 3...");
		sf::Sleep(1.0f);
		clrscreen();
		msg("Depart dans 2...");
		sf::Sleep(1.0f);
		clrscreen();
		msg("Depart dans 1...");
		sf::Sleep(1.0f);
		clrscreen();
		msg("GO !");
		sf::Sleep(1.0f);
	
		unsigned short int score[8];
		unsigned short int probaAccident[8];
		
		//on calcule Score: celui qui a le plus grand est le vainqueur	
		calculerScore(score, Adversaire, Player1, Map); 
		
		//on calcule la probabilite que les voitures aient des accidents	
		calculerProbaAccident(probaAccident, Adversaire, Player1, Map);		

		//on calcule les voitures ayant un accident en fonction de la probabilite calculee precedement
		for(unsigned short int njoueur = 0; njoueur <= 7; njoueur++)
		{
			if(std::rand()%101 < probaAccident[njoueur])
			{
				score[njoueur]=0;
				if(njoueur == 0)
				{
					Player.ajouterAccident();
				}	
			}
			if(score[njoueur] == 0)
			{	
				if(njoueur == 0)
				{
					std::cout << "Le joueur " << Player.getNom() << " " << messageAccident[njoueur - 1] <<"\n";
				}
				else
				{			
					std::cout << "Le joueur " << nomJoueur[njoueur - 1]<< " " << messageAccident[njoueur - 1] <<"\n";
				}
			}
		}
		
		std::cout<<"\n\nPressez [ENTREE] pour voir les resultats.\n";
		videKBuffer();	

		unsigned short int scoreJoueur[8];
		
		scoreJoueur[0] = score[0];
		scoreJoueur[1] = score[1];
		scoreJoueur[2] = score[2];
		scoreJoueur[3] = score[3];		//variables pour suivre le joueur
		scoreJoueur[4] = score[4];
		scoreJoueur[5] = score[5];
		scoreJoueur[6] = score[6];
		scoreJoueur[7] = score[7];

		//classement des joueurs
		unsigned short int temp;
		while(score[0] < score[1] || score[1] < score[2] || score[2]<score[3] || score[3]<score[4] || score[4]<score[5] || score[5]<score[6] || score[6]<score[7])
		{
			for(unsigned short int i = 1;i <= 7;i++)
			{
				if( score[i - 1] < score[i])
				{
					temp = score[i - 1]; 	//On fait une copie de la variable score[X] dans temp
					score[i - 1] = score[i];	//On fait glisser vers la gauche le plus grand des chiffres
					score[i] = temp; 	//On remplace le chiffre qu'on a fait glisse par le chiffre de gauche
				}
			}
		}
		
		//on affiche les resultats
		bool exclu[8] = {false};
		bool placeExclue[8] = {false};
		unsigned short int joueur;
		std::cout<<"\n\n";		
		for(unsigned short int placeClassement = 0; placeClassement <=7 ;placeClassement++)
		{
			if(placeExclue[placeClassement] == true)
			{
				placeClassement += 1;
		
			}
			std::cout << "[" << placeClassement + 1 << "e] "; //On affiche le numéro de la place en début de ligne
			joueur = 0;

			if(exclu[0] == true)
			{
				while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
				{
					joueur++;
				}
			}
			while(score[placeClassement] != scoreJoueur[joueur] && joueur < 8) //On trouve le joueur correspondant au score de la place
			{
				joueur++;
				while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
				{
					joueur++;
				}
			
			}
			if(joueur == 0 && exclu[0] == false) //Si le joueur est le Joueur1 on affiche son nom
			{
				std::cout << Player.getNom() << " - " << score[placeClassement] << " Points.\n";
				exclu[0] = true;
			}
			else //Sinon on met des nom d'IA
			{
			
				std::cout << nomJoueur[joueur - 1] << " - " << score[placeClassement] << " Points.\n";
				exclu[joueur] = true;
			}
		

			if(joueur == 0 && placeClassement < 3) //Si le joueur finit sur le podium
			{
				Player.ajouterVictoire();
			}
			else if (joueur == 0 && placeClassement > 3 ) //sinon si il finit ailleurs
			{
				Player.ajouterDefaite();
			}
			placeExclue[placeClassement]=true;
			sf::Sleep(0.5f);
		}
	
		Player.ajouterCourse();
	
		std::cout<<"\n\nPressez [ENTREE] pour continuer.\n";
		videKBuffer();
		clrscreen();
	
		for(unsigned short int compteur = 0; compteur <= 6; ++compteur)
		{
			delete Adversaire[compteur];
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}


void faireCourseChampionnat(Circuit Map, Voiture* Player1, Profil& Player)
{
	if(Player1 == 0)
	{
		error("Vous n'avez pas de voiture disponible !");
	}
	else if(antiCorruption("Data/console/pilotes.txt", 7) == false)
	{
		error("Le fichier pilotes.txt ne contient pas assez d'informations.");
	}
	else if(antiCorruption("Data/console/accident.txt", 8) == false)
	{
		error("Le fichier pilotes.txt ne contient pas assez d'informations.");
	}
	else if(Player1->getEtat() < 20)
	{
		error("Votre vehicule est trop endommage pour concourir.");
	}
	else if(Player1->getDurabilitePneus() < 15)
	{
		error("Vos pneus sont trop uses pour concourir.");
	}
	else //Si tout va bien
	{
		if(preparatifsCourse(Map, Player, Player1))
		//REVOIR CE CALCUL
		{
			Player.payer(Player1->getConsommation() * 0.01f * Map.getTaille() * Player1->getPrixCarburantMoteur());
			Voiture* Adversaire[7];
			chargerAdversaires(Adversaire, Player.getDifficulte(), Map.getDifficulte());
			
			std::string *commentaireMeteo = chargerCommentaireMeteo(Map.getMeteo());
					
			std::string messageAccident[8];
			chargerMessagesAccidents(messageAccident);		
			
			//On initialise les noms des adversaires			
			std::string nomJoueur[7];
			std::string pseudo;
			for(unsigned short int numero = 0; numero <= 6; numero++) 
			{
				pseudo = randNomAdversaire(); //On randomise un nom dans le tableau pseudo.
				while(pseudo == nomJoueur[0] || pseudo == nomJoueur[1] || pseudo == nomJoueur[2] || pseudo == nomJoueur[3] || pseudo == nomJoueur[4] || pseudo == nomJoueur[5] || pseudo == nomJoueur[6])
				{
					pseudo = randNomAdversaire(); //Tant que le pseudo a deja été tiré, on re-genere un nouveau
				}
				nomJoueur[numero] = pseudo;
			}
	
	
			std::cout << "Bienvenue à tous et a toutes ! Aujourd'hui va se derouler l'evenement tant attendu par tous les fans de sportives, tout le monde s'est reuni et l'ambiance est a son comble sur le circuit: " << Map.getNom() << ".\nOn m'annonce qu'il totalise " << Map.getTaille() << " Km, et comprend pas moins de " << Map.getVirages() << " virages serres !\n" << *commentaireMeteo << " D'autre part, il y a un vent de Force " << Map.getVent() << " dans l'enceinte du circuit.\n\nSans attendre passons tout de suite a la liste des Participants:\n\n";
			
			//on liste les concurants		
			for(unsigned short int numero = 0; numero <= 7; numero++)
			{
				if(numero == 0)
				{
					std::cout << Player.getNom() << " - " << Player1->getMarque() << " " << Player1->getModele() << "\n";
				}
				else
				{
					std::cout << nomJoueur[numero - 1] << " - " << Adversaire[numero - 1]->getMarque() << " " << Adversaire[numero - 1]->getModele() << "\n";
				}
			}
	
	
			delete commentaireMeteo;
			std::cout<<"\n\nPressez [ENTREE] pour commencer la course.\n";
			videKBuffer();	
	
			clrscreen();
			msg("Depart dans 3...");
			sf::Sleep(1.0f);
			clrscreen();
			msg("Depart dans 2...");
			sf::Sleep(1.0f);
			clrscreen();
			msg("Depart dans 1...");
			sf::Sleep(1.0f);
			clrscreen();
			msg("GO !");
			sf::Sleep(1.0f);

			unsigned short int score[8];
			unsigned short int probaAccident[8];
			//on calcule Score: celui qui a le plus grand est le vainqueur	
			calculerScore(score, Adversaire, Player1, Map); 
	
			//on calcule la probabilite que les voitures aient des accidents	
			calculerProbaAccident(score, Adversaire, Player1, Map);		

			//on calcule les voitures ayant un accident en fonction de la probabilite calculee precedement
			for(unsigned short int njoueur = 0; njoueur <= 7; njoueur++)
			{
				if(std::rand()%101 < probaAccident[njoueur])
				{
					score[njoueur]=0;
					if(njoueur == 0)
					{
						Player.ajouterAccident();
						Player1->retirerEtat(16); //cette valeur changera selon le parchoque
					}	
				}
				if(score[njoueur] == 0)
				{	
					if(njoueur == 0)
					{
						std::cout << "Le joueur " << Player.getNom() << " " << messageAccident[njoueur - 1] <<"\n";
					}
					else
					{			
						std::cout << "Le joueur " << nomJoueur[njoueur - 1]<< " " << messageAccident[njoueur - 1] <<"\n";
					}
				}
			}
	
			std::cout<<"\n\nPressez [ENTREE] pour voir les resultats.\n";
			videKBuffer();	

			unsigned short int joueur;			
			unsigned short int scoreJoueur[8];
			scoreJoueur[0] = score[0];
			scoreJoueur[1] = score[1];
			scoreJoueur[2] = score[2];
			scoreJoueur[3] = score[3];		//variables pour suivre le joueur
			scoreJoueur[4] = score[4];
			scoreJoueur[5] = score[5];
			scoreJoueur[6] = score[6];
			scoreJoueur[7] = score[7];

			//classement des joueurs
			unsigned short int temp;
			while(score[0] < score[1] || score[1] < score[2] || score[2]<score[3] || score[3]<score[4] || score[4]<score[5] || score[5]<score[6] || score[6]<score[7])
			{
				for(unsigned short int i = 1;i <= 7;i++)
				{
					if( score[i - 1] < score[i])
					{
						temp = score[i - 1]; 	//On fait une copie de la variable score[X] dans temp
						score[i - 1] = score[i];	//On fait glisser vers la gauche le plus grand des chiffres
						score[i] = temp; 	//On remplace le chiffre qu'on a fait glisse par le chiffre de gauche
					}
				}
			}
	
			//on affiche les resultats
			bool exclu[8] = {false};
			bool placeExclue[8] = {false};
			std::cout<<"\n\n";		
			for(unsigned short int placeClassement = 0; placeClassement <=7 ;placeClassement++)
			{
				if(placeExclue[placeClassement] == true)
				{
					placeClassement += 1;
	
				}
				std::cout << "[" << placeClassement + 1 << "e] "; //On affiche le numéro de la place en début de ligne
				joueur = 0;

				if(exclu[0] == true)
				{
					while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
					{
						joueur++;
					}
				}
				while(score[placeClassement] != scoreJoueur[joueur] && joueur < 8) //On trouve le joueur correspondant au score de la place
				{
					joueur++;
					while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
					{
						joueur++;
					}
		
				}
				if(joueur == 0 && exclu[0] == false) //Si le joueur est le Joueur1 on affiche son nom
				{
					std::cout << Player.getNom() << " - " << score[placeClassement] << " Points.\n";
					exclu[0] = true;
				}
				else //Sinon on met des nom d'IA
				{
		
					std::cout << nomJoueur[joueur - 1] << " - " << score[placeClassement] << " Points.\n";
					exclu[joueur] = true;
				}
	

				if(joueur == 0 && placeClassement < 3) //Si le joueur finit sur le podium
				{
					Player.ajouterVictoire();
					Player.ajouterCredits(600 / (placeClassement + 1));
					Player.ajouterCreditsGagnes(600 / (placeClassement + 1));
				}
				else if (joueur == 0 && placeClassement > 3 ) //sinon si il finit ailleurs
				{
					Player.ajouterDefaite();
				}
				placeExclue[placeClassement]=true;
				sf::Sleep(0.5f);
			}

			Player.ajouterCourse();

			std::cout<<"\n\nPressez [ENTREE] pour continuer.\n";
			videKBuffer();
			clrscreen();

			for(unsigned short int compteur = 0; compteur <= 6; ++compteur)
			{
				delete Adversaire[compteur];
			}
			Player1->setPneus(-1 * (( Map.getTaille() + Map.getVirages() ) / 10));
			Player1->setNitro(-1 * (Map.getTaille() / 4));
		}
		if(Player.getSauvegardeAuto())
		{
			Player.sauvegarderProfil();
		}
	}
}  
