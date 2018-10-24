//algos.h
#ifndef ALGOS_HH_
#define ALGOS_HH_

#include <string>
#include <fstream>

enum Rank {
  D,
  C,
  B,
  A,
  S
};

Rank charToRank(char c);
int vRang(char rang);
char vRangInverse(int valeur);
std::string generateUuid();

#endif /* !ALGOS_HH_ */