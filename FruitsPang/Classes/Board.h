#ifndef BOARD_H
#define BOARD_H

#include "cocos2d.h"
#include "Global.h"
#include "Block.h"
#include "GridCell.h"

class Board : public cocos2d::Layer
{
public:
	Board() = default;
	~Board() = default;
	Board(const Board&) = default;

public:
	GridCell* cells[MAX_ROW][MAX_COL];
	Block* blocks[MAX_ROW][MAX_COL];

	static Board* createBoard(int rows, int cols); // ���� ����

	void removeAllBlocks(); // ��� ��� ����
	void generateRandomBlock(); // ������� ����
	void generateCell();
	Block* getBlockForPosition(cocos2d::Vec2 pos); // ����� ��ġ ���
	bool isNeighbours(Block* first, Block* second); // �̿��ϴ°�?
	void swapBlock(Block* first, Block* second); // ��� ��ü
	
	bool checkForMatch(Block* block); 
	int findMatch(Block* block, std::vector<Block*>& matches, bool isRoot = true);
	
	void removeBlockAt(BoardPosition pos); // Ư����� ����
	void fillBlanks(); // ��� ä���
	void resolveMatchForBlocks(std::vector<Block*> blocks); 

	std::vector<BoardMove> findAvailableMove();

	virtual void onEnter();
	bool isBusy() noexcept{ return busy; }

private:
	bool busy;
	int binaryX[8] = { 0, 1, 0, -1, 0, 2, 0, -2 };
	int binaryY[8] = { 1, 0, -1, 0, 2, 0, -2, 0 };
};

#endif // !BOARD_H
