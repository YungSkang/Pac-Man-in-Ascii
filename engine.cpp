#include "engine.h"
#include <cstring>
#include <iostream>


#define WALL_PAIR	7
#define EMPTY_PAIR	1
#define POTTER_PAIR	2
#define TRAAL_PAIR	3
#define GNOME_PAIR	4
#define GEM_PAIR	5
#define SCROLL_PAIR	6

Engine::Engine():P1(NULL),Score(0),F(NULL),Dead(FALSE),Win(FALSE),gemCount(0),level(0)
{
}

void Engine::insertMap(int argc,char **argv)
{
	if(argc==1)
		throw 1;
	F.open(argv[1]);
	std::string Buff;
   	do
    	{
       		if (!F.eof ())
       		{        	
   			getline(F,Buff);
    			map.push_back(Buff);
   		}
    	}while (!F.eof ());
    	int i,j;
    	checkMapSpace();
    	this->summonGems();
    	for(i=0; i < map.size()-1; i++)
    		for(j=0; j < std::strlen( map[1].c_str() ) ; j++)
    		{	
    			if(map[i][j]==' ')
    			{
    				attron(COLOR_PAIR(EMPTY_PAIR));
				mvaddch(i,j,map[i][j]);
				attroff(COLOR_PAIR(EMPTY_PAIR));
    			}
    			if(map[i][j]=='*')
    			{
    				attron(COLOR_PAIR(WALL_PAIR));
				mvaddch(i,j,map[i][j]);
				attroff(COLOR_PAIR(WALL_PAIR));
    			}
    			if(map[i][j]=='o')
    			{
    				attron(COLOR_PAIR(GEM_PAIR));
				mvaddch(i,j,map[i][j]);
				attroff(COLOR_PAIR(GEM_PAIR));
    			}
			refresh();
		}
	refresh();
	F.close();
}
	

bool Engine::checkSpace(int y,int x)
{
	return (map[y][x]==' ');
}

bool Engine::checkEnemy(int y,int x)
{
	bool checkmate=FALSE;
	if( (x == G1->getX()) && (y == G1->getY()) )
		checkmate=TRUE;
	if( (x == T1->getX()) && (y == T1->getY()) )
		checkmate=TRUE;
	return checkmate;
}

void Engine::bounds(int *y,int *x)
{
	*y=map.size();
	*x=std::strlen( map[1].c_str() );
} 

void Engine::summonGems()
{
	int i,bx,by,x,y;
	srand(time(0));
	this->bounds(&by,&bx);
	for(i=0;i<10;i++)
	{
		do
		{
			y= (rand() % (by));
			x= (rand() % (bx));
		}while(!( this->checkSpace(y,x) ) );
		map[y][x]='o';
		refresh();
	}	
}

void Engine::summonScroll()
{
	int i,bx,by,x,y;
	this->level+=1;
	if(this->level==1)
	{
		srand(time(0));
		this->bounds(&by,&bx);
		do
		{
			y= (rand() % (by));
			x= (rand() % (bx));
		}while(!( this->checkSpace(y,x) ) );
		map[y][x]='x';
		attron(COLOR_PAIR(SCROLL_PAIR));
		mvaddch(y,x,'x' );
		attroff(COLOR_PAIR(SCROLL_PAIR));
		refresh();
	}
}


void Engine::summonHero(Moving &ON)
{
	int y,x,bx,by;
	this->bounds(&by,&bx);
	do{
		y= (rand() % (by));
		x= (rand() % (bx));
	}while(!( this->checkSpace(y,x) ) );
	ON.setY(y);
	ON.setX(x);
	attron(COLOR_PAIR(ON.getColor()));
	mvaddch(y,x,ON.getSymbol() );
	attroff(COLOR_PAIR(ON.getColor()));

}

void Engine::StartGame(int argc,char** argv,HiScore& L)
{
	start_color();
	ColorInitialization();
	int select;				//εντολή χρήστη
	std::string uname;			//όνομα χρήστη
	this->insertMap(argc,argv);	
	G1 = new Gnome('G',GNOME_PAIR);
	P1 = new Potter('H',POTTER_PAIR);
	T1 = new Traal('T',TRAAL_PAIR);
	srand(time(0));
	this->summonHero(*P1);
	this->summonHero(*G1);
	this->summonHero(*T1);
	refresh();
	keypad(stdscr,TRUE);
	this->level=0;
	gemCount=0;
	curs_set(0);
	do
	{
		select=this->getMove();
		refresh();
		if(checkGem(tempy,tempx))
		{
			Score+=10;
			gemCount++;
			map[tempy][tempx]=' ';
		}
		if(checkScroll(tempy,tempx))
		{
			Score+=100;
			Win=TRUE;
			map[tempy][tempx]=' ';
		}
		if( this->gemCount == 10 )
			summonScroll();
		if(checkEnemy(tempy,tempx))
		{
			suicidalFlag=TRUE;
			Dead=TRUE;
		}
		gnomeCinematics();
		traalCinematics();
		if(checkEnemy(tempy,tempx))
		{
			Dead=TRUE;
		}
		if(!Dead)
		{
			attron(COLOR_PAIR(G1->getColor()));
			mvaddch(G1->getY(),G1->getX(),G1->getSymbol() );
			attroff(COLOR_PAIR(G1->getColor()));
	
			attron(COLOR_PAIR(T1->getColor()));
			mvaddch(T1->getY(),T1->getX(),T1->getSymbol() );
			attroff(COLOR_PAIR(T1->getColor()));
			
			attron(COLOR_PAIR(P1->getColor()));
			mvaddch(P1->getY(),P1->getX(),P1->getSymbol() );
			attroff(COLOR_PAIR(P1->getColor()));
		}
	}while(select!=27 and  Win != TRUE and Dead != TRUE);
	GameOver(Dead);
	Bravo(Win);
	if(Score > L.getLast() && select != 27)
	{
		do
		{
			clear();
			initscr();
			refresh();
			printw("Enter your Username(Only 10 characters long):");
			refresh();
			std::cin >> uname;
			refresh();
		}while( std::strlen( uname.c_str() ) > 10 );
		L << uname.c_str() << Score;
	}	
	delete P1,T1,G1;
	refresh();
}

bool Engine::checkWall(int y,int x)
{
	return (map[y][x]=='*');
}

bool Engine::checkGem(int y,int x)
{
	return (map[y][x]=='o');
}

bool Engine::checkScroll(int y,int x)
{
	return (map[y][x]=='x');
}


int Engine::getMove()
{
	int flag;		//περίπτωση που έγινε κίνηση πάνω σε τοίχο
	int select;
	do{
		select = getch();
		flag=0;	
		move( (this->P1)->getY() , (this->P1)->getX() );
		tempx=this->P1->getX();
		tempy=this->P1->getY();
		switch(select)
		{
			case KEY_UP : tempy--;break;
			case KEY_DOWN : tempy++;break;
			case KEY_LEFT: tempx--;break;
			case KEY_RIGHT: tempx++;break;
			case ' ' : noecho(); break;
			case 27  : noecho(); addch(P1->getSymbol() ); break;
			default  : noecho(); addch(P1->getSymbol() ); flag=1; break;
		}
		if(checkWall(tempy,tempx) )
			flag=1;
		else
		{
			this->P1->setX(tempx);
			this->P1->setY(tempy);
		}
	}while(flag==1);
	addch(' ');
	return select;
}


void Engine::GameOver(bool x)
{
	if(x)
	{
		clear();
		initscr();
		attron(COLOR_PAIR(TRAAL_PAIR));
		printw("\n \n \n \n \n \n \n \n \t \t \t              Game Over \n");
		if(suicidalFlag)
			printw("\t \t \t            Too suicidal! \n");
		attroff(COLOR_PAIR(TRAAL_PAIR));
		suicidalFlag=FALSE;
		getch();
	}
}

void Engine::Bravo(bool x)
{
	if(x)
	{
		clear();
		initscr();
		attron(COLOR_PAIR(GEM_PAIR));
		printw("\n \n \n \n \n \n \n \n \t \t \t \t       WIN! \n");
		attroff(COLOR_PAIR(GEM_PAIR));
		getch();
	}
}

bool Engine::getDead()
{
	return Dead;
}
bool Engine::getWin()
{
	return Win;
} 

void Engine::gnomeCinematics()
{
	int gx,gy;
	do
	{
		gx=G1->getX();
		gy=G1->getY();
		G1->gnomeMove(gy,gx);
	}while(checkWall(gy,gx) or checkEnemy(gy,gx));
	if(flagGnomeS||flagGnomeG)
	{
		if(flagGnomeS)
		{
			flagGnomeS=FALSE;
			attron(COLOR_PAIR(SCROLL_PAIR));
			mvaddch(G1->getY(),G1->getX(),'x');
			attroff(COLOR_PAIR(SCROLL_PAIR));
		}
		if(flagGnomeG)
		{
			flagGnomeG=FALSE;
			attron(COLOR_PAIR(GEM_PAIR));
			mvaddch(G1->getY(),G1->getX(),'o' );
			attroff(COLOR_PAIR(GEM_PAIR));
		}
	}
	else
	{
		move(G1->getY(),G1->getX());
		addch(' ');
	}
	if(checkScroll(gy,gx)) 
		flagGnomeS=TRUE;
	if(checkGem(gy,gx))
		flagGnomeG=TRUE;
	G1->setY(gy);
	G1->setX(gx);
}

void Engine::traalCinematics()
{
	int tx,ty;
	do
	{
		tx=T1->getX();
		ty=T1->getY();
		T1->traalMove(ty,tx);
	}while(checkWall(ty,tx) or checkEnemy(ty,tx));
	if(flagTraalS||flagTraalG)
	{
		if(flagTraalS)
		{
			flagTraalS=FALSE;
			attron(COLOR_PAIR(SCROLL_PAIR));
			mvaddch(T1->getY(),T1->getX(),'x');
			attroff(COLOR_PAIR(SCROLL_PAIR));
		}
		if(flagTraalG)
		{
			flagTraalG=FALSE;
			attron(COLOR_PAIR(GEM_PAIR));
			mvaddch(T1->getY(),T1->getX(),'o' );
			attroff(COLOR_PAIR(GEM_PAIR));
		}
	}
	else
	{
		move(T1->getY(),T1->getX());
		addch(' ');
	}
	if(checkScroll(ty,tx)) 
		flagTraalS=TRUE;
	if(checkGem(ty,tx))
		flagTraalG=TRUE;
	T1->setY(ty);
	T1->setX(tx);
}

void Engine::checkMapSpace()
{
	int i,j,mapSpace;
	mapSpace=0;
	for(i = 0;i < map.size() ; i++)
	{	for(j = 0 ; j < std::strlen( map[1].c_str() ); j++)
		{	
			if(map[i][j]==' ')
				mapSpace++;
		}
	}
	if(mapSpace < 13)	//13 είναι ο μέγιστος αριθμός πρόσθετων αντικειμένων που θα υπάρξουν στον χάρτη (10 πετράδια +2 τέρατα +1 Μπάμπης)
		throw 2;	
}

void Engine::ColorInitialization()
{
	init_pair(EMPTY_PAIR, COLOR_BLACK, COLOR_BLACK);
	init_pair(WALL_PAIR, COLOR_WHITE, COLOR_WHITE);
	init_pair(POTTER_PAIR, COLOR_CYAN, COLOR_BLACK);
	init_pair(GNOME_PAIR, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(TRAAL_PAIR, COLOR_RED, COLOR_BLACK);
	init_pair(GEM_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(SCROLL_PAIR, COLOR_YELLOW, COLOR_BLACK);	
}










