#include "Utils.hh"
#include <iostream>

int vRang(char rang)
{
	int vRang = 0;
	switch(rang)
	{
		case 'D':
			vRang = 1;
			break;
		case 'C':
			vRang = 2;
			break;
		case 'B':
			vRang = 3;
			break;
		case 'A':
			vRang = 4;
			break;
		case 'S':
			vRang = 5;
			break;
		default:
			vRang = 0;
			break;
	}
	return vRang;
}

Rank charToRank(char c)
{
  switch (c)
  {
    case 'D':
      return (D);
    case 'C':
      return (C);
    case 'B':
      return (B);
    case 'A':
      return (A);
    case 'S':
      return (S);
    default:
      throw std::runtime_error("No such rank");
  }
}

char vRangInverse(int valeur)
{
	switch(valeur)
	{
		case 2:
			return 'C';
			break;

		case 3:
			return 'B';
			break;

		case 4:
			return 'A';
			break;

		case 5:
			return 'S';
			break;

		default:
			return 'D';
			break;
	}
}