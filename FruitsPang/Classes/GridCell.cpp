#include "GridCell.h"

USING_NS_CC;

GridCell* GridCell::createCell(GridType Type, BoardPosition Pos)
{
	GridCell* cell = new GridCell();

	if (cell->init())
	{
		cell->autorelease();
		cell->type = Type;
		cell->boardPos = Pos;

		return cell;
	}

	return nullptr;
}

void GridCell::setType(GridType Type)
{
	this->type = Type;
	
	if (cellSprite != nullptr && Type != GridType::NONE)
		cellSprite->setSpriteFrame(GridTypeName.at(Type));

}

void GridCell::onEnter()
{
	Node::onEnter();

	setContentSize(m_CellSize);
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	cellSprite = Sprite::createWithSpriteFrameName(GridTypeName.at(type));
	cellSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	cellSprite->setPosition(m_CellSize * 0.5f);
	addChild(cellSprite, 0);
}
