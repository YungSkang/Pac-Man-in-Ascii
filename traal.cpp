#include "traal.h"

Traal::Traal(char S,int C):Moving(S,C)
{
}


void Traal::traalMove(int &y,int &x)
{
	int random;
	random = (rand() % 4 +1);
	switch(random)
	{
		case 1: x--; break;
		case 2: x++; break;
		case 3: y--; break;
		case 4: y++; break;
	}
}
