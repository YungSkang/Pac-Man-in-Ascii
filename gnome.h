#ifndef gnome_h
#define gnome_h

#include "moving.h"



class Gnome : public Moving
{
	public:
	void gnomeMove(int&,int&);	//αλγόριθμος κίνησης Gnome
	Gnome(char S,int C);		//Gnome Constructor
};

#endif
