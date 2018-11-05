#ifndef UTILS_HH_
#define UTILS_HH_

struct Point {
  int x;
  int y;

  Point (int x_ = 0, int y_ = 0)
   : x(x_), y(y_)
  {
  }
};

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

#endif /* !UTILS_HH_ */