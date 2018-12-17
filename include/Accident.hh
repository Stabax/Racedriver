#ifndef ACCIDENT_HH_
#define ACCIDENT_HH_

#include <string>
#include "DataFile.hh"

struct Accident
{
  Accident(const json &data);

  static void loadCollection();

  static std::vector<Accident> collection;

  int damage;
  std::string message;
};

#endif /* !ACCIDENT_HH_ */