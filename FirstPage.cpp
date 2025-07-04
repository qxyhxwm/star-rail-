#include "FirstPage.h"
#include"Chess.h"
#include<math.h>

int FirstPage::CheckJL(int x,int y)
{
	int res = 0;
	int Distance = sqrt((x - 276) * (x - 276) + (y - 496) * (y - 496));
	if (Distance <= chess->getChessSize())
	{
		res = 1;
	}
	return res;
}

int FirstPage::CheckJY(int x, int y)
{
	int res = 0;
	int Distance = sqrt((x - 276) * (x - 276) + (y - 948) * (y - 948));
	if (Distance <= chess->getChessSize())
	{
		res = 1;
	}
	return res;
	
}


void FirstPage::ChooseFlag()
{
	
	//创建游戏窗口
	initgraph(2304, 1440);
	int size = chess->getChessSize();
	loadimage(0, "fl\\fm.jpg", 2304, 1440);
	loadimage(&chessJY, "fl\\jy1.jpg", size, size);
	loadimage(&chessJY2, "fl\\jy2.jpg", size,size);
	loadimage(&chessJL, "fl\\jl1.jpg", size, size);
	loadimage(&chessJL2, "fl\\jl2.jpg", size, size);
	
	putimage(276, 496, &chessJL2, NOTSRCERASE);
	putimage(276, 496, &chessJL, SRCINVERT);
	
	putimage(276, 948, &chessJY2, NOTSRCERASE);
	putimage(276, 948, &chessJY, SRCINVERT);

	MOUSEMSG msg2;
	while (true)
	{
		msg2 = GetMouseMsg();
		if (msg2.uMsg == WM_LBUTTONDOWN && CheckJL(msg2.x,msg2.y)) {
			Flag = -1;
			break;
		}
		if (msg2.uMsg == WM_LBUTTONDOWN && CheckJY(msg2.x, msg2.y)) {
			Flag = 1;
			break;
		}
	}
	return;
}

int FirstPage::getFlag()
{
	return Flag;
}
