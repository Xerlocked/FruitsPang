#include "GridCell.h"

USING_NS_CC;

GridCell* GridCell::createCell(CellType Type, BoardPosition Pos)
{
	GridCell* cell = nullptr;

	try
	{
		cell = new GridCell();
		if (!cell->init())
			throw std::bad_alloc();
		cell->autorelease();
		cell->type = Type;
		cell->boardPosition = Pos;
		return cell;
	}
	catch (...)
	{
		CC_SAFE_DELETE(cell);
		throw;
	}
}

void GridCell::setType(CellType Type)
{
	this->type = Type;
	
	if (cellSprite != nullptr)
		cellSprite->setSpriteFrame(CellTypeName[static_cast<int>(type)]);

}

void GridCell::onEnter()
{
	Node::onEnter();

	setContentSize(m_CellSize);
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	cellSprite = Sprite::createWithSpriteFrameName(CellTypeName[static_cast<int>(type)]);
	cellSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	cellSprite->setPosition(m_CellSize * 0.5f);
	addChild(cellSprite, 0);
}
