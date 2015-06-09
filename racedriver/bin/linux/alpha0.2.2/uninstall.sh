echo -n "Les librairies et dépendances de Racedriver vont etre desinstallees"
echo "suppression de /usr/lib/libsfml-system.so.1.6"
sudo rm /usr/lib/libsfml-system.so.1.6
echo "suppression de /usr/lib/libsfml-system.so.1.6 reussie"
echo "suppression du dossier racedriver"
sudo rm -r ../racedriver
echo "Suppression effectuee avec succes !"
read -p "Appuyez sur [Entree] pour quitter." nothing
