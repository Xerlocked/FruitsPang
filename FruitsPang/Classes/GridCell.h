/// <summary>
/// ±×¸®µå
/// <summary>
#ifndef GRID_CELL_H
#define GRID_CELL_H

#include "cocos2d.h"
#include "Global.h"

class GridCell : public cocos2d::Node
{
public:
	static GridCell* createCell(CellType Type, BoardPosition Pos);
	BoardPosition boardPosition;
	CellType getType() noexcept { return type; }

	void setType(CellType Type);

	virtual void onEnter();

private:
	CellType type;
	cocos2d::Sprite* cellSprite = nullptr;
	
	GridCell() = default;
	GridCell(const GridCell&) = default;
	virtual ~GridCell() = default;
};

#endif // !GRID_CELL_H
