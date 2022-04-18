#ifndef moving_h
#define moving_h

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

class Moving
{
protected:
    	int cury;		//τρέχουσα θέση όντος στον άξονα y
    	int curx;		//τρέχουσα θέση όντος στον άξονα x
    	char Symbol;		//σύμβολο του όντος
    	int Color;		//χρώμα του όντος
public:
	Moving(char S,int C);	//Contstructor όντος
	char getSymbol();	
	int getColor();
	void setX(int );
	void setY(int );
	int  getX();
	int  getY();
};
#endif
