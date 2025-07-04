#pragma once
#include"Chess.h"
#include"FirstPage.h"
class AI
{
public:
	void init(Chess* chess,FirstPage* page);
	void go();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;

private:
	void calculateScore();
	ChessPos think();
	FirstPage* page;
};

