
//Launcher.cpp

#include "unistd.h"
#include "launcher.h"
 

void miseAJour()
{		
	//supprime le zip potentiellement présent
	std::remove("Update/update.zip");

	std::ifstream config("Data/config.ini");
	if(config)	//si le fichier config.cdg existe
	{
		std::string ligneChargee;
		std::istringstream iss;	//convertion string to int
		int OS = 2; //0 = linux, 1 = windows, 2 = bug
		
		std::getline(config, ligneChargee);
		iss.str(ligneChargee);	//charge l'OS
		iss >> OS;

		std::string version;	//version de l'utilisateur
		
		std::getline(config, ligneChargee);
		version = ligneChargee;	//charge la verion de l'utilisateur
	
		//si le fichier config est corrompu
		if(version.size() < 3 || version.size() > 5 || (OS != 1 && OS != 0) || version.find_first_of(".") != 1)
		{
			clrscreen();
			error("Fichier de configuration corompu");
			std::cout<<">La verification de la derniere version ne peut être effectuee.\n";
			std::cout<<">Vous allez jouer avec une version potentiellement obsolete de Racedriver.\n";
			std::cout<<">Appuyez sur [ENTREE] pour continuer.\n";
			videKBuffer();
		}
		//si tout va bien
		else
		{
			CURL *curlVersion = curl_easy_init(); //On crée un flux cURL et on "instancie" le flux
			CURLcode resVersion; //CURLcode est un type enum de Curl stockant un état d'erreur.
	
			//création et ouverture d'un fichier en ecriture
			FILE *versionFile = fopen("Update/version.cdx", "w"); 
			
			std::cout << ">Connexion au serveur distant...\n";
			//on indique l'url cible
			curl_easy_setopt(curlVersion, CURLOPT_URL, "http://racedriver.url.ph/bin/version");
			
			//on indique quelle est la fonction d'ecriture du fichier. on utilise celle de la bibliothèque standard
			curl_easy_setopt(curlVersion, CURLOPT_WRITEFUNCTION, fwrite);
			
			
			//on indique le fichier de destination chez le client
			curl_easy_setopt(curlVersion, CURLOPT_WRITEDATA, versionFile);

			std::cout << ">Recuperation des informations de mise a jour...\n\n";
			//on lance le flux (curl version ici) ==> telechargement du fichier
			//l'état du telechargement est stocké dans un type CURLcode (ici resVersion)
			resVersion = curl_easy_perform(curlVersion);
			
			//on libère les ressources utilisées
			curl_easy_cleanup(curlVersion);
			fclose(versionFile); //On ferme le fichier téléchargé car on en a plus besoin
			
			//si le téléchargement s'est mal dérroulé
			if(CURLE_OK != resVersion)
			{
				//echec du telechargement
				error("La recuperation du fichier de mise a jour a echoue. Verifiez votre connexion.");
				std::cout<<">La lecture du fichier de mise a jour est impossible.\n";
				std::cout<<">Vous jouerez avec une version potentiellement obsolete de Racedriver.\n";
				std::cout<<">Appuyez sur [ENTREE] pour continuer.\n";
				videKBuffer();
			}
			//si le telechargement s'est bien passé, on lit la version disponible
			else
			{
				std::ifstream latestVersion("Update/version.cdx");
				std::string stringLatestVersion;	//derniere version disponible
				std::getline(latestVersion, stringLatestVersion);

				//si la verion actuelle est differente de la version disponible, on telecharge la derniere version de racedriver	
				if(version != stringLatestVersion)
				{						
					std::string choix;
					do
					{
						msg("Votre client est obsolete, une mise a jour est disponible !");
						std::cout<<"Souhaitez vous telecharger la derniere version de Racedriver ? [O/n]\n";
						std::getline(std::cin, choix);
					}while(choix != "O" && choix != "o" && choix != "N" && choix != "n");
					 
					if(choix == "O" || choix == "o")
					{
						FILE *updateFile = fopen("Update/update.zip", "w");
						CURL *curlUpdate;
						CURLcode resUpdate;
						std::string binURL;

						curlUpdate = curl_easy_init();

						if(OS == 0) //Si on est sur linux, on dl la version linux
						{
							binURL = "http://racedriver.url.ph/bin/linux/"+stringLatestVersion+".zip";
						}
						else if(OS == 1) //Si on est sur windows on dl la version windows
						{
							binURL = "http://racedriver.url.ph/bin/windows/"+stringLatestVersion+".zip";
						}
					
						std::cout << "\n>Connexion au serveur distant...\n";
						curl_easy_setopt(curlUpdate, CURLOPT_URL, binURL.c_str());
						curl_easy_setopt(curlUpdate, CURLOPT_WRITEFUNCTION, fwrite);
						curl_easy_setopt(curlUpdate, CURLOPT_WRITEDATA, updateFile);

						std::cout << ">Telechargement de Racedriver...\n\n";
						resUpdate = curl_easy_perform(curlUpdate);

						curl_easy_cleanup(curlUpdate);
						fclose(updateFile);
					
						//echec du dl	
						if(CURLE_OK != resUpdate) 
						{				
							error("Le telechargement de la mise a jour a echoue.");
							std::cout<<">Vous jouerez avec une version obsolete de Racedriver.\n";
							std::cout<<">Appuyez sur [ENTREE] pour continuer.\n";
							videKBuffer();
						}
						//dl reussi
						else
						{			
						
						
							msg("Le client a ete mis a jour avec succes !");
							std::cout << ">Vous devez redemmarer le launcher pour appliquer les modifications.\n";
							if(OS == 0) //Si on est sur linux... car windows n'a pas install.sh
							{
								std::cout<<">N'oubliez pas de terminer l'installation en lançant \"install.sh\".";
								std::cout<<">Lisez le README pour plus de precisions.\n";
							}
							std::cout << ">Appuyez sur [Entree] pour quitter.";
							videKBuffer();
						
							//décompression du .zip téléchargé
							//opérateur ternaire: si OS == 0 (linux) on appelle execl pour unpack linux, sinon on appelle execl pour unpack.exe windows
							OS == 0 ? execl("Update/unpack", "unpack", "-qq", "-o", "Update/update.zip", NULL) : execl("Update/unpack.exe", "unpack.exe", "-qq", "-o", "Update/update.zip", NULL);
							
							//le programme se termine ici grace à l'apel à execl()
						}
					}
					else
					{
						std::cout<<">Vous jouerez avec une version obsolete de Racedriver.\n";
						std::cout<<">Appuyez sur [ENTREE] pour continuer.\n";
						videKBuffer();
					}						
				}
				else //Client a jour, on lance le jeu
				{
					msg("Le client est a jour !");
					std::cout << ">Appuyez sur [Entree] pour continuer.\n";
					videKBuffer();
				}
			}			
		}
	}
	//si on ne peut pas ouvrir config.ini
	else
	{
		clrscreen();
		error("Echec de lecture du fichier de configuration config.ini.");
		std::cout<<">La verification de la derniere version ne peut être effectuee.\n";
		std::cout<<">Vous allez jouer avec une version potentiellement obsolete de Racedriver.\n";	
		std::cout<<">Appuyez sur [ENTREE] pour continuer.\n";
		videKBuffer();
	}
}
