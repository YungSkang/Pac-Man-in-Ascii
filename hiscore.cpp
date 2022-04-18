#include "hiscore.h"
#include <ncurses.h>

using namespace std;
HiScore& HiScore::operator<< (string name)
{
	strcpy( const_cast<char*>( tempname.c_str() ), name.c_str());
	return *this;
}

void HiScore::operator<< (int score)
{
	int i,j,tempint;
	string tempchar;
	for(i=0;i<5;i++)
	{
		if(Info[i].UserScore < score)
		{
			for(j=3;j>=i;j--)
			{
	   			strcpy( const_cast<char*>(Info[j+1].UserName.c_str() ) , Info[j].UserName.c_str() );
	   			Info[j+1].UserScore = Info[j].UserScore;
			}
			Info[i].UserScore=score;
			strcpy( const_cast<char*>(Info[i].UserName.c_str() ) , tempname.c_str() );
			break;
		}
	}	
}

void HiScore::insertLeaderBoard(int argc,char **argv)
{
	int i;
	if( argc==2)
	{
		for(i=0;i<5;i++)
		{
			strcpy( const_cast<char*>(Info[i].UserName.c_str() ),"..........");
			Info[i].UserScore=0;
		}
			
	}
	else
	{
		ifstream HS;
		HS.open(argv[2], ios::in | ios::binary);	
		for(i=0;i<5;i++)
		{
			HS.read( (char*)&Info[i],sizeof(LD) );
			HS.close();
		}
    	}	
}

void HiScore::ShowLeaderBoard()
{
	int i,option=0;
	clear();
	initscr();
	attron(A_BOLD);
	printw("\t~~LEADERBOARD~~~\n");
	attroff(A_BOLD);
	refresh();
	printw("1. %s \t\t %d \n" ,Info[0].UserName.c_str() , Info[0].UserScore);
	refresh();
	printw("2. %s \t\t %d \n" ,Info[1].UserName.c_str() , Info[1].UserScore);
	refresh();
	printw("3. %s \t\t %d \n" ,Info[2].UserName.c_str() , Info[2].UserScore);
	refresh();
	printw("4. %s \t\t %d \n" ,Info[3].UserName.c_str() , Info[3].UserScore);
	refresh();
	printw("5. %s \t\t %d \n" ,Info[4].UserName.c_str() , Info[4].UserScore);
	refresh();
	getch();
			
}


void HiScore::exportLeaderBoard(int argc,char **argv)
{
	int i;
	ofstream HS;
	if(argc==3)
	{
		HS.open(argv[2], ios::out | ios::binary | ios::trunc);
		for(i = 0 ; i < 5 ; i++)
		{
			HS.write( (char*) &Info[i],sizeof(LD) );
		}
		HS.close();
	}
	else
	{
		HS.open("ld.bin", ios::out | ios::binary | ios::trunc);
		for(i = 0 ; i < 5 ; i++)
		{
			HS.write( (char*) &Info[i],sizeof(LD) );
		}
		HS.close();
	}
}

int HiScore::getLast()
{
	return Info[4].UserScore;
}














