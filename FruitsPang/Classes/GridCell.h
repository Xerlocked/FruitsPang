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
	static GridCell* createCell(GridType Type, BoardPosition Pos);
	BoardPosition boardPos;
	GridType getType() noexcept { return type; }

	void setType(GridType Type);

	virtual void onEnter();

private:
	GridType type;
	cocos2d::Sprite* cellSprite;
};

#endif // !GRID_CELL_H
