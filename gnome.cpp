#include "gnome.h"

Gnome::Gnome(char S,int C):Moving(S,C)
{
}


void Gnome::gnomeMove(int &y,int &x)
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

