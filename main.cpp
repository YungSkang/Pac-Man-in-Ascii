#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <vector>
#include <string.h>
#include "engine.h"


using namespace std;

int main(int argc, char** argv)
{	
	//ο παρακάτω έλεγχος γίνεται true παρόλο που το δικό μου terminal υποστηρίζει χρώματα
	/*if (!has_colors())
	{	
		cout<<"Your terminal does not support color" << endl; 
		exit(1);
	}*/
	int terminate;
	HiScore L;
	L.insertLeaderBoard(argc,argv);
	do
	{
		noecho();
		clear();
		initscr();
		terminate=0;
		attron(A_BOLD);
		attron(A_BLINK);
		printw("\t \t \t ~~~~~~Welcome to Potter-Man~~~~~~");
		attroff(A_BLINK);
		attroff(A_BOLD);
		printw("\n \n \n \n \n  \t \t            | Press Enter to continue | ");
		refresh();
		printw("\n \n \n \n \n  \t \t         | Press Space to see LeaderBoard | ");
		refresh();
		printw("\n \n \n \n \n  \t \t               | Press Esc to exit | ");	
		refresh();
		terminate=getch();
		if( terminate != 27 && terminate == ' ')
		{
			L.ShowLeaderBoard();
		}
		if( terminate != 27 && terminate != ' ')
		{
			refresh();
			clear();
			Engine PacMan;
			try
			{
				PacMan.StartGame(argc,argv,L);
			}
			catch(int exc)
			{
				clear();
				refresh();
				switch(exc)
				{
					case 1: cout << "ERROR:No map inserted as argument!\n";break;		//σε αυτά τα exceptions προσπάθησα να αλλάξω τον char array 
					case 2: cout << "ERROR:Not sufficient space to summon objects!\n";break;//του argv ωστε ο χρήστης να πληκτρολογεί ένα map.txt			
				}
				getch();
				terminate=27;
			}
			refresh();
		}
	}while(terminate != 27);
	
	L.exportLeaderBoard(argc,argv);
	endwin();
	return 0;
}
