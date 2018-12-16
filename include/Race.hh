#ifndef RACE_HH_
#define RACE_HH_

#include <cmath>
#include <fstream>
#include "Track.hh"
#include "Profile.hh"

class Race
{
public:
  Race(Car &pCar);

  static void loadDrivers();
  static void loadCrash();

  bool preparations();
  void randomizeOpponents(int count);
  bool start();


  std::vector<int> calculerScore();
  std::vector<int> calculerProbaAccident();

  static std::vector<std::string> crashCollection;
  static std::vector<std::string> driversCollection;

protected:
  std::vector<std::pair<std::string, std::shared_ptr<Car>>> players;
  std::shared_ptr<Car> playerCar;
  std::shared_ptr<Track> track;
};

void calculerScore(int score[8], const Car* Adversaire[7],  Car* Player1, const Track& Map);
void calculerProbaAccident(int probaAccident[8], Car* Adversaire[7], Car* Player1, const Track Map);

void faireCourseChampionnat(Track Map, Car* Player1);

#endif /* RACE_HH_ */
