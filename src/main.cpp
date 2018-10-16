/**
===============

Ce programme est un jeu de course en console et en graphique.

Ce projet contient 16 fichiers sources et 15 fichiers d'en-tête.

Ce projet est compilé avec les options: -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wfloat-equal -Woverloaded-virtual -Winline -Os -s -O2

Les bibliothèques utilisées sont:
	-Boost-thread: pour les threads (car les threads de la bibliothèque standard ne sont pas supportés partout)
	-Boost-asio: pour le multijoueur
	-SFML: pour le graphique, le son et le temps
	-curl: pour télécharger les mises à jour depuis un FTP

Toutes les classes sont instanciées depuis des fichiers .cdx et le fichier mods.txt
Les différentes classes sont le coeur du jeu:
	-Circuit
	-Profil
	-Voiture
	-Moteur
	-PriseAir
	-Spoiler
	-Tires

Tout ce qui n'est pas objet ne sert qu'à faire:
	-des verifications (sauvegarde...)
	-des demandes (choix des menus...)
	-des calculs (courses...)

Les conventions de ce programme sont:
	-des majuscules au début des classes et des objets (pointeurs ou non)
	-les attributs commencent par m_
	-les threads commencent par t_
	-les variables globales non statiques sont dans l'espace de nommage GLOBAL
	-pour les entités composées de plusieurs mots, la premiere lettre est en minuscule, la premiere lettres des autres mots sont en majuscules. Exemple: maVariableDecimale
	-les using namespace sont prohibés
	-ce programme se veut portable, les fonctions system() sont donc prohibées
	-un pointeur qui n'a pas ou plus de cible doit pointer sur 0, (et non NULL, qui n'est pas portable).
	-toutes les variables ne sont pas définies dès le début d'une fonction: difficile à lire et utilise des ressources parfois inutiles.

===============
*/

#include <ctime>
#include <unistd.h>
#include "Game.hh"

namespace GLOBAL
{
	bool dureeNormale = true;
	bool donne100000Credits = false;
	bool toutGratuit = false;
	bool vainqueur = false;
	bool MeilleureVoiture = false;
	bool debloqueMap = false;
	bool debloqueAchievement = false;
}

int main(int argc, char **argv)
{
	Game racedriver;
	return (racedriver.main());
}
