echo -n "Les librairies et dépendances de Racedriver vont etre desinstallees"
echo ""
echo "suppression de /usr/lib/libsfml-system.so.1.6"
sudo rm /usr/lib/libsfml-system.so.1.6
echo "suppression de /usr/lib/libsfml-system.so.1.6 reussie"
echo "suppression de /usr/lib/libboost_system.so.1.48.0"
sudo rm /usr/lib/libboost_system.so.1.48.0
echo "suppression de /usr/lib/libboost_system.so.1.48.0 reussie"
echo "suppression de /usr/lib/libcurl.so.4.2.0"
sudo rm /usr/lib/libcurl.so.4.2.0
echo "suppression de /usr/lib/libcurl.so.4.2.0 reussie"
echo "suppression du dossier racedriver"
sudo rm -r ../racedriver
echo "Suppression effectuee avec succes !"
read -p "Appuyez sur [Entree] pour quitter." nothing
