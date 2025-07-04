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
	chess->init();//���̳�ʼ��
	while (true) {
		//����������
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

		//��AI��
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
