#include "Control.h"

Control::Control(Man* man, AI* ai, Chess* chess,FirstPage* page)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	this->page = page;

	man->init(chess,page);
	ai->init(chess,page);
}


void Control::play()
{
	chess->init();//棋盘初始化
	while (true) {
		//先由棋手走
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

		//由AI走
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
