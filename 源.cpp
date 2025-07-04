
#include<iostream>
#include"Control.h"
#include"FirstPage.h"
int main(void) {
	Man man;
	AI ai;
	
	Chess chess(19, 89, 86, 48);
	FirstPage page(&chess);
	page.ChooseFlag();
	Control game(&man, &ai, &chess,&page);

	game.play();

	return 0;
}



