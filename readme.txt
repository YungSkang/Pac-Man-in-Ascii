~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~What is this?~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This was my University's Semester Project for OOP (= Object Oriented Programming) where we had to program
a PacMan ripoff in C++. The plot is that you are Harry (PacMan) and you have to collect all 10 gems to summon 
the final sacred Scroll. However, there are two evil monsters, Traal and Gnome, to destroy your plans and to guard the gems and the 
sacred Scroll.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~How does it work?~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The game works with the Ncurses library that helps with the window generation. Every time the player moves, a new frame is generated with
the new data. The monsters A.I. is pretty simple, monsters move randomly as long as they do not hit walls. The game has an unfinished 
LeaderBoard too where you can load it as a second argument.   

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~How do I run it?~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Run the code with a Linux Terminal.
Run : "g++ main.cpp engine.cpp  gnome.cpp hiscore.cpp moving.cpp potter.cpp traal.cpp -lncurses"
and then run: "./a.out map1.txt".
Please note that you can choose one of the available maps as the argument of the program or you can create your 
own ones. Just be carefull, walls are made with "*" and paths with " ". Also, please do not make rooms without 
doors, Pac-Man won't be able to reach some of the gems.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HAVE FUN!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
