echo -n "Les librairies et dépendances de Racedriver vont être installees"
echo ""
sudo chmod +x Data/racedriver_a0.2.2
echo "racedriver est maintenant executable"
sudo chmod +x racedriver.sh
echo "racedriver.sh est maintenant executable"
sudo chmod +x uninstall.sh
echo "uninstall.sh est maintenant executable"
echo "installation de libsfml-system.so.1.6"
sudo cp lib/libsfml-system.so.1.6 /usr/lib/libsfml-system.so.1.6
echo "installation de libsfml-system.so.1.6 reussie"
echo "Installation effectuee avec succes"
read -p "Appuyez sur [Entree] pour quitter." nothing
