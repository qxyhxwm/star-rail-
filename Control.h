#pragma once
#include"Man.h"
#include"AI.h"
#include"Chess.h"
#include"FirstPage.h"
class Control
{
public:
	Control(Man* man, AI* ai, Chess* chess,FirstPage* page);
	void play();

	
private:
	Man* man;
	AI* ai;
	Chess* chess;
	FirstPage* page;
};



