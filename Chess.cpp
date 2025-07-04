#include "Chess.h"
#include<math.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>
#include<iostream>



Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = JY;

	chessMap = vector<vector<int>>(gradeSize+1, vector<int>(gradeSize+1, 0));
}

void Chess::init()
{
	//������Ϸ����
	initgraph(991, 980);

	//��ʾ����ͼƬ
	loadimage(0, "fl\\qipan.jpg");
	//���ſ�ʼbgm
	mciSendString("open \"fl\\�������й¶�ҡ��.mp3\" alias BGM", NULL, 0, NULL);
	mciSendString("setaudio BGM volume to 200", NULL, 0, 0);  // 20% ����
	mciSendString("play BGM", NULL, 0, NULL);

	
	loadimage(&chessJY, "fl\\jy1.jpg", chessSize, chessSize, true);
	loadimage(&chessJY2, "fl\\jy2.jpg", chessSize, chessSize, true);
	loadimage(&chessJL, "fl\\jl1.jpg", chessSize, chessSize, true);
	loadimage(&chessJL2, "fl\\jl2.jpg", chessSize, chessSize, true);
	//��������
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			this->chessMap[i][j] = 0;
		}
	}
	playerFlag = true;
}

//�������
double dist(int x, int y)
{
	return sqrt(x * x + y * y);
}

//�ж�����
bool Chess::clickBorad(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int left_x = x - margin_x - col * chessSize;
	int right_x = chessSize - left_x;
	int up_y = y - margin_y - row * chessSize;
	int down_y = chessSize - up_y;
	int standardset = chessSize * 0.4;
	bool flag = false;
	do
	{
		if (dist(left_x, up_y) <= standardset)
		{
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0)
			{
				flag = true;
			}
			break;
		}
		if (dist(left_x, down_y) <= standardset)
		{
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0)
			{
				flag = true;
			}
			break;
		}
		if (dist(right_x, up_y) <= standardset)
		{
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0)
			{
				flag = true;
			}
			break;
		}
		if (dist(right_x, down_y) <= standardset)
		{
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0)
			{
				flag = true;
			}
			break;
		}

	} while (0);
	return flag;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

	if (kind == JL) {
		putimage(x, y, &chessJL2, NOTSRCERASE);
		putimage(x, y, &chessJL,SRCINVERT);
	}
	else {
		putimage(x, y, &chessJY2, NOTSRCERASE);
		putimage(x, y, &chessJY, SRCINVERT);
	}
	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessSize()
{
	return chessSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	//checkWin()-��������Ƿ����Ӯ��
	if (checkWin()) {
		Sleep(1000);
		if (playerFlag == 1) {	
			mciSendString("stop BGM", NULL, 0, NULL);
			mciSendString("open \"fl\\ʹһ�������ڰ���.mp3\" alias BGM2", NULL, 0, NULL);
			mciSendString("setaudio BGM2 volume to 200", NULL, 0, 0);  
			mciSendString("play BGM2", NULL, 0, NULL);
			loadimage(0, "fl/JY.jpg"); 
		}
		else {	
			mciSendString("stop BGM", NULL, 0, NULL);
			mciSendString("open \"fl\\ʹһ�������ڰ���.mp3\" alias BGM2", NULL, 0, NULL);
			mciSendString("setaudio BGM2 volume to 200", NULL, 0, 0);  
			mciSendString("play BGM2", NULL, 0, NULL);
			loadimage(0, "fl/jlhs2.jpg");
		}

		_getch();	//��ͣ ͷ�ļ�#include<conio.h>
		return true;
	}

	return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
	chessMap[pos->row][pos->col] = playerFlag ? JY : JL;
	playerFlag = !playerFlag;	
	//lastPos = *pos;
	lastPos.row = pos->row;
	lastPos.col = pos->col;
}

bool Chess::checkWin()
{
	//������ӵ��λ��
	int row = lastPos.row;
	int col = lastPos.col;
	int color = chessMap[row][col]; //��ǰ������ɫ

	for (int y = -1; y < 1; y++) {	//�ĸ�����ѭ�����ӣ�������5���������ӣ���Ӯ
		for (int x = -1; x <= 1; x++) {
			if (y == 0 && x == 0)continue;
			if (y == 0 && x == -1)continue;
			int sum = 0;	//�÷������Ӹ���

			//����������ͬ
			for (int i = 1; i <= 4; i++) {
				int curRow = row + i * y;
				int curCol = col + i * x;
				if (chessMap[curRow][curCol] == color) {	//��ɫ������ͬ�����Ӹ���+1
					sum++;
				}
				else {
					break;
				}
			}

			//�������Ӹ���
			for (int i = 1; i <= 4; i++) {
				int curRow = row - i * y;
				int curCol = col - i * x;
				if (chessMap[curRow][curCol] == color) {	//��ɫ������ͬ�����Ӹ���+1
					sum++;
				}
				else {
					break;
				}
			}

			if (sum >= 4) {	//�����Ӹ�������4����ʤ��
				return true;
			}
		}
	}
	return false;
}
