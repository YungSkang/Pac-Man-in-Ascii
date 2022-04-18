#ifndef hiscore_h
#define hiscore_h

#include <fstream>
#include <string.h>

class HiScore
{
   private:
   std::string tempname;				//προσωρινή αποθήκευση ονόματος παίκτη
   struct LD						//αποθήκευση πληροφοριών παίκτη
   {
   	std::string UserName;				//Όνομα παίκτη
   	int  UserScore;					//Βαθμός παίκτη
   }Info[5];
     
   public:    	
   HiScore& operator<< (std::string);		
   void operator<< (int );
   void insertLeaderBoard(int argc,char **argv);	//εισαγωγή πίνακα High Score ή σε περίπτωση που δεν υπάρχει αρχικοποίηση ενός
   void ShowLeaderBoard();				//εμφάνιση του πίνακα High Score
   void exportLeaderBoard(int argc,char **argv);	//αντιγραφή του πίνακα High Score στο δυαδικό αρχείο ld.bin
   int getLast();					//επιστροφή σκορ τελευταίου παίκτη ώστε σε περίπτωση μεγαλύτερου σκορ από τον παίκτη να καταταχθεί

};
#endif
