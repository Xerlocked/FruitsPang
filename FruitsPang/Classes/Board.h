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

	static Board* createBoard(int rows, int cols); // 보드 생성

	void removeAllBlocks(); // 모든 블록 제거
	void generateRandomBlock(); // 랜덤블록 생성
	void generateCell();
	Block* getBlockForPosition(cocos2d::Vec2 pos); // 블록의 위치 얻기
	bool isNeighbours(Block* first, Block* second); // 이웃하는가?
	void swapBlock(Block* first, Block* second); // 블록 교체
	
	bool checkForMatch(Block* block); 
	int findMatch(Block* block, std::vector<Block*>& matches, bool isRoot = true);
	
	void removeBlockAt(BoardPosition pos); // 특정블록 제거
	void fillBlanks(); // 빈곳 채우기
	void resolveMatchForBlocks(std::vector<Block*> blocks); 

	std::vector<BoardMove> findAvailableMove();

	void Blink();

	virtual void onEnter();
	bool isBusy() noexcept{ return busy; }

private:
	bool busy;
};

#endif // !BOARD_H
