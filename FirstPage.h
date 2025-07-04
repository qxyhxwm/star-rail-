#pragma once
#include<graphics.h>
#include"Chess.h"
class FirstPage
{
public:
	FirstPage(Chess* chess) :chess(chess)
	{
	}
	int CheckJL(int x, int y);
	int CheckJY(int x, int y);
	void ChooseFlag();
	int getFlag();

private:
	Chess* chess;
	int Flag=1;
	IMAGE chessJY;//景元棋子
	IMAGE chessJY2;
	IMAGE chessJL;//镜流棋子
	IMAGE chessJL2;
};

