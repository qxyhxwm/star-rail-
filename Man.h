#pragma once
#include"Chess.h"
#include"FirstPage.h"
class Man
{
public:
	void init(Chess* chess,FirstPage* page);
	void go();

private:
	Chess* chess;
	FirstPage* page;
};

