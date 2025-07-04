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
		//��ȡ�������Ϣ
		msg = GetMouseMsg();

		
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBorad(msg.x, msg.y, &pos)) {
			break;
		}
	}

	

	//����
	if (page->getFlag() == -1)
	{
		chess->chessDown(&pos, JL);
	}
	else
	{
		chess->chessDown(&pos, JY);
	}
	
}
