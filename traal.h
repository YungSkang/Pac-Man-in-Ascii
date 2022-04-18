#include "moving.h"

#ifndef traal_h
#define traal_h
class Traal : public Moving
{
	public:
	void traalMove(int&,int&);	//αλγόριθμος κίνησης Traal
	Traal(char S,int C);
}; 
#endif
