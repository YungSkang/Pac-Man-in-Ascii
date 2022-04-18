#ifndef engine_h
#define engine_h

#include <ncurses.h>
#include <fstream>
#include <string.h>
#include <vector>
#include "moving.h"
#include "potter.h"
#include "gnome.h"
#include "traal.h"
#include "hiscore.h"

class Engine
{
    	private:
	std::ifstream F;				//ανοιγμα αρχείου χάρτη
	std::vector<std::string> map;			//vector για την εκχώρηση του χάρτη 
	int Score;					//προσωρινή αποθήκευση του score του τρέχοντος παίκτη
	int gemCount;					//απαρίθμηση συγκεντρωμένων πετραδιών ώστε στα 10 να εμφανιστεί η περγαμηνή
	int level;					//flag ώστε η περγαμηνή να εμφανιστεί μόνο μια φορά κατα την διάρκεια μιας πίστας
	Gnome *G1;
	Potter *P1;
	Traal *T1;
	bool Dead;
	bool Win;
	int tempx,tempy;				//η θέση του Potter πριν γίνουν οι απαραίτητοι έλεγχοι και οι εκτυπώσεις
	bool suicidalFlag;				//flag σε περίπτωση που ο Potter έχει αυτοκτονικές τάσεις!
	bool flagGnomeG=FALSE;				//flag σε περίπτωση που το Gnome  πατήσει πάνω σε πετράδι
	bool flagGnomeS=FALSE;				//flag σε περίπτωση που το Gnome  πατήσει πάνω στην περγαμηνή
	bool flagTraalG=FALSE;				//flag σε περίπτωση που το Traal  πατήσει πάνω σε πετράδι
	bool flagTraalS=FALSE;				//flag σε περίπτωση που το Traal  πατήσει πάνω στην περγαμηνή
							//στις περιπτώσεις των προηγούμενων flag,αν γίνουν TRUE,στον επόμενο γύρο θα ξαναεμφανιστόυν τα πετράδια
    	public:    	
    	Engine();
    	void summonHero(Moving&);			//κλήρωση θέσης αντικειμένου κλάσης moving
    	void summonGems();				//κλήρωση θέσης πετραδιού
    	void summonScroll();				//κλήρωση θέσης περγαμηνής
	void insertMap(int argc,char **);		//εκχώρηση του χάρτη απο argv[1] σε vector 
	void checkMapSpace();				//έλεγχος επαρκείς χώρου για την κλήρωση των θέσεων				
	bool checkSpace(int,int);			//έλεγχος για χώρο
	void bounds(int*,int*);				//εύρεση ορίων του χάρτη
	bool checkEnemy(int ,int );			//έλεγχος αν βρίσκεται σε μια δεδομένη θέση τέρας
	bool checkWall(int ,int);			//έλεγχος αν βρίσκεται σε μια δεδομένη θέση τοίχος
	bool checkGem(int ,int );			//έλεγχος αν βρίσκεται σε μια δεδομένη θέση πετράδι
	bool checkScroll(int,int);			//έλεγχος αν βρίσκεται σε μια δεδομένη θέση η περγαμηνή
	void StartGame(int argc,char **,HiScore& );	//συνάρτηση που διαχειρίζεται την σειρά με την οποία θα κληθούν οι υπόλοιπες συναρτήσεις
	int getMove();					//εισαγωγή εντολής απο τον χρήστη και έλεγχος αν είναι έγκυρη
	void Bravo(bool);				//εμφάνιση ειδικού εφέ νίκης
	void GameOver(bool);				//εμφάνιση ειδικού εφέ νίκης
	bool getDead();					//έλεγχος αν ο παίκτης είναι νεκρός
	bool getWin(); 					//έλεγχος αν ο παίκτης πήρε την περγαμηνή
	void gnomeCinematics();				//έλεγχος για την κίνηση του Gnome
	void traalCinematics();				//έλεγχος για την κίνηση του Traal
	void ColorInitialization();			//αρχικοποίηση ζευγαριών χρωμάτων
};

#endif
