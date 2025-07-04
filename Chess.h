#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//表示落子位置
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

typedef enum {
	JL = -1,  //镜流为-1
	JY = 1   //景元为1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//棋盘初始化
	void init();

	//判断是否点击有效且将有效的位置保存在pos中
	bool clickBorad(int x, int y, ChessPos* pos);

	void chessDown(ChessPos* pos, chess_kind_t kind);

	//获取棋盘大小
	int getGradeSize();

	//获取棋子大小
	int getChessSize();

	//获取指定位置是景元还是镜流还是空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	bool checkOver();//检查棋局是否结束
	//表示当前该谁落子
	int playerFlag;	//现在该谁落子  ture JY   false JL

private:
	IMAGE chessJY;//景元棋子
	IMAGE chessJY2;
	IMAGE chessJL;//镜流棋子
	IMAGE chessJL2;

	int gradeSize;//棋盘大小
	int margin_x;//棋盘左侧边界
	int margin_y;//棋盘顶部边界
	float chessSize ;//棋子大小（即棋盘一个方块的边长)

	//存储当前棋局棋子分布  0:空白  -1：镜流  1：景元
	vector<vector<int>> chessMap;

	

	void updateGameMap(ChessPos* pos);	//更新棋盘

	bool checkWin(); //如果胜负已分，就返回true，否则返回false

	ChessPos lastPos;	//最近落子点的位置
};


