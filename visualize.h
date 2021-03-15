#ifndef visualize
#define visualize

#include <ncurses.h>
#include <iostream>
//#include "visualize.h"


void startScreen()
{
	initscr();
    cbreak();
    noecho();
}

void endScreen()
{
	endwin();
}



#endif
