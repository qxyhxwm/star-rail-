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
	//创建游戏窗口
	initgraph(991, 980);

	//显示棋盘图片
	loadimage(0, "fl\\qipan.jpg");
	//播放开始bgm
	mciSendString("open \"fl\\在银河中孤独摇滚.mp3\" alias BGM", NULL, 0, NULL);
	mciSendString("setaudio BGM volume to 200", NULL, 0, 0);  // 20% 音量
	mciSendString("play BGM", NULL, 0, NULL);

	
	loadimage(&chessJY, "fl\\jy1.jpg", chessSize, chessSize, true);
	loadimage(&chessJY2, "fl\\jy2.jpg", chessSize, chessSize, true);
	loadimage(&chessJL, "fl\\jl1.jpg", chessSize, chessSize, true);
	loadimage(&chessJL2, "fl\\jl2.jpg", chessSize, chessSize, true);
	//棋盘清零
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			this->chessMap[i][j] = 0;
		}
	}
	playerFlag = true;
}

//计算距离
double dist(int x, int y)
{
	return sqrt(x * x + y * y);
}

//判断落子
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
	//checkWin()-检查棋盘是否出现赢棋
	if (checkWin()) {
		Sleep(1000);
		if (playerFlag == 1) {	
			mciSendString("stop BGM", NULL, 0, NULL);
			mciSendString("open \"fl\\使一颗心免于哀伤.mp3\" alias BGM2", NULL, 0, NULL);
			mciSendString("setaudio BGM2 volume to 200", NULL, 0, 0);  
			mciSendString("play BGM2", NULL, 0, NULL);
			loadimage(0, "fl/JY.jpg"); 
		}
		else {	
			mciSendString("stop BGM", NULL, 0, NULL);
			mciSendString("open \"fl\\使一颗心免于哀伤.mp3\" alias BGM2", NULL, 0, NULL);
			mciSendString("setaudio BGM2 volume to 200", NULL, 0, 0);  
			mciSendString("play BGM2", NULL, 0, NULL);
			loadimage(0, "fl/jlhs2.jpg");
		}

		_getch();	//暂停 头文件#include<conio.h>
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
	//最近落子点的位置
	int row = lastPos.row;
	int col = lastPos.col;
	int color = chessMap[row][col]; //当前落子颜色

	for (int y = -1; y < 1; y++) {	//四个方向循环数子，若大于5个连续的子，则赢
		for (int x = -1; x <= 1; x++) {
			if (y == 0 && x == 0)continue;
			if (y == 0 && x == -1)continue;
			int sum = 0;	//该方向连子个数

			//正向连子相同
			for (int i = 1; i <= 4; i++) {
				int curRow = row + i * y;
				int curCol = col + i * x;
				if (chessMap[curRow][curCol] == color) {	//颜色连续相同则连子个数+1
					sum++;
				}
				else {
					break;
				}
			}

			//反向连子个数
			for (int i = 1; i <= 4; i++) {
				int curRow = row - i * y;
				int curCol = col - i * x;
				if (chessMap[curRow][curCol] == color) {	//颜色连续相同则连子个数+1
					sum++;
				}
				else {
					break;
				}
			}

			if (sum >= 4) {	//若连子个数大于4，则胜利
				return true;
			}
		}
	}
	return false;
}
