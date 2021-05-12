#include "Block.h"

USING_NS_CC;

Block* Block::createBlock(BlockType Type, BoardPosition pos)
{
	Block* block = new Block();

	if (block->init())
	{
		block->autorelease();
		block->type = Type;
		block->boardPos = pos;

		return block;
	}

	return nullptr;
}

void Block::setActive(bool isActive)
{
	if (isActive)
	{
		blockSprite->setContentSize(blockSprite->getContentSize() * 0.25f);
	}
	
}

void Block::Blink(int times)
{
}

void Block::setType(BlockType Type)
{
	this->type = Type;

	if (blockSprite != nullptr && Type != BlockType::NONE)
		blockSprite->setSpriteFrame(BlockTypeName.at(Type));

}

void Block::explode()
{
}

void Block::onEnter()
{
	Node::onEnter();

	setContentSize(m_BlockSize);
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	blockSprite = Sprite::createWithSpriteFrameName(BlockTypeName.at(type));
	blockSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	blockSprite->setPosition(m_BlockSize * 0.5f);
	addChild(blockSprite, 1);
}
