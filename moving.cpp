#include "moving.h"

Moving::Moving(char S,int C):Symbol(S),Color(C)
{

}

char Moving::getSymbol()
{
	return Symbol;
}

int Moving::getColor()
{
	return Color;
}

void Moving::setX(int x)
{
	curx=x;
}

void Moving::setY(int y)
{
	cury=y;
}

int Moving::getX()
{
	return curx;
}

int Moving::getY()
{
	return cury;
}


