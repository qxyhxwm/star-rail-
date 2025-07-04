#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//��ʾ����λ��
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

typedef enum {
	JL = -1,  //����Ϊ-1
	JY = 1   //��ԪΪ1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//���̳�ʼ��
	void init();

	//�ж��Ƿ�����Ч�ҽ���Ч��λ�ñ�����pos��
	bool clickBorad(int x, int y, ChessPos* pos);

	void chessDown(ChessPos* pos, chess_kind_t kind);

	//��ȡ���̴�С
	int getGradeSize();

	//��ȡ���Ӵ�С
	int getChessSize();

	//��ȡָ��λ���Ǿ�Ԫ���Ǿ������ǿհ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	bool checkOver();//�������Ƿ����
	//��ʾ��ǰ��˭����
	int playerFlag;	//���ڸ�˭����  ture JY   false JL

private:
	IMAGE chessJY;//��Ԫ����
	IMAGE chessJY2;
	IMAGE chessJL;//��������
	IMAGE chessJL2;

	int gradeSize;//���̴�С
	int margin_x;//�������߽�
	int margin_y;//���̶����߽�
	float chessSize ;//���Ӵ�С��������һ������ı߳�)

	//�洢��ǰ������ӷֲ�  0:�հ�  -1������  1����Ԫ
	vector<vector<int>> chessMap;

	

	void updateGameMap(ChessPos* pos);	//��������

	bool checkWin(); //���ʤ���ѷ֣��ͷ���true�����򷵻�false

	ChessPos lastPos;	//������ӵ��λ��
};


