#ifndef RACE_HH_
#define RACE_HH_

#include <cmath>
#include <fstream>
#include "Track.hh"
#include "Profile.hh"
#include <omniunit.hh>

struct Concurrent
{
  Concurrent(std::string n, std::shared_ptr<Car> c);

  friend bool operator==(const Concurrent &a, const Concurrent &b);
  friend bool operator>(const Concurrent &a, const Concurrent &b);

  std::string name;
  std::shared_ptr<Car> car;
  omni::Meter position;
  bool out;
};

class Race
{
public:
  Race(std::shared_ptr<Car> pCar, Track &track);

  static void loadDrivers();

  bool preparations();
  void randomizeOpponents(size_t count);
  bool start();

  void compute();
  void render(int rtick);

  std::vector<int> calculerProbaAccident();

  static std::vector<std::string> driversCollection;

protected:
  std::vector<Concurrent> _players;
  std::shared_ptr<Track> _track;
};

void calculerScore(int score[8], const Car* Adversaire[7],  Car* Player1, const Track& Map);
void calculerProbaAccident(int probaAccident[8], Car* Adversaire[7], Car* Player1, const Track Map);

void faireCourseChampionnat(Track Map, Car* Player1);

#endif /* RACE_HH_ */
