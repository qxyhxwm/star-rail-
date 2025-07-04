#include "Man.h"

void Man::init(Chess* chess,FirstPage* page)
{
	this->chess = chess;
	this->page = page;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;

	while (true) {
		//获取鼠标点击消息
		msg = GetMouseMsg();

		
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBorad(msg.x, msg.y, &pos)) {
			break;
		}
	}

	

	//落子
	if (page->getFlag() == -1)
	{
		chess->chessDown(&pos, JL);
	}
	else
	{
		chess->chessDown(&pos, JY);
	}
	
}
