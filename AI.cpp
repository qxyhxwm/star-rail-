#include "AI.h"
#include<ctime>

void AI::init(Chess* chess,FirstPage* page)
{
	this->chess = chess;
	this->page = page;

	for (int i = 0; i < chess->getGradeSize(); i++) {
		vector<int> row;
		for (int j = 0; j < chess->getGradeSize(); j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(600);	//AI停顿
	//落子
	if (page->getFlag() == -1)
	{
		chess->chessDown(&pos, JY);
	}
	else
	{
		chess->chessDown(&pos, JL);
	}
	
}

void AI::calculateScore()
{
	int personNum = 0;	
	int aiNum = 0;	
	int emptyNum = 0;	
	int dx[] = { -1,-1,0,1 };
	int dy[] = { 0,1,1,1 };
	//清零
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			//对每个点进行计算
			if (chess->getChessData(row, col)) continue;	//若有棋，则无需计算

			for (int y = -1; y < 1; y++) {
				for (int x = -1; x <= 1; x++) {
					if ((y == 0 && x == -1) || (y == 0 && x == 0)) continue;
					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					//假设黑棋在该位置落子，会构成什么棋形
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {	//若当前为黑子
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {	//若当前为空白
							emptyNum++;
						}
						else {
							break;
						}
					}

					//反向继续计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
						}
						else {
							break;
						}
					}

					if (personNum == 1) {	//连2
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4) {
						scoreMap[row][col] += 20000;
					}

					//假设白棋在该位置落子，会构成什么棋形
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}
					//反向计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (aiNum == 0) {
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {	
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;
						}
					}
					else if (aiNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum >= 4) {
						scoreMap[row][col] += 30000;
					}

				}
			}

		}
	}
}

ChessPos AI::think()
{
	calculateScore();

	int maxScore = 0;
	vector<ChessPos> maxPoints;

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessData(row, col)) continue;

			if (scoreMap[row][col] > maxScore) {
				maxScore = scoreMap[row][col];
				maxPoints.clear();
				maxPoints.push_back(ChessPos(row, col));
			}
			else if (scoreMap[row][col] == maxScore) {
				maxPoints.push_back(ChessPos(row, col));
			}
		}
	}

	//若分值最大的数不止一个，则随机取一个落子
	srand(time(NULL));
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
