#include "Block.h"

USING_NS_CC;

Block* Block::createBlock(BlockType Type, BoardPosition pos)
{
	Block* block = nullptr;

	try
	{
		block = new Block();
		if (!block->init())
			throw std::bad_alloc();
		block->autorelease();
		block->type = Type;
		block->boardPosition = pos;
		return block;
	}
	catch (...)
	{
		CC_SAFE_DELETE(block);
		throw;
	}
}

void Block::setActive(bool isActive)
{
	if (isActive)
	{
		//blockSprite->setContentSize(blockSprite->getContentSize() * 1.5f);
	}
	
}

void Block::Blink()
{
	auto fadeout = FadeOut::create(3.0);
	auto reverse = fadeout->reverse();

	auto Seq = Sequence::create(fadeout, DelayTime::create(1.5f) , reverse, nullptr);

	auto actionRepeat = RepeatForever::create(Seq);

	blockSprite->runAction(actionRepeat);

}

void Block::setType(BlockType Type)
{
	this->type = Type;

	if (blockSprite != nullptr)
		blockSprite->setSpriteFrame(BlockTypeName[static_cast<int>(type)]);

}

void Block::explode()
{
}

void Block::onEnter()
{
	Node::onEnter();

	setContentSize(m_BlockSize);
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	blockSprite = Sprite::createWithSpriteFrameName(BlockTypeName[static_cast<int>(type)]);
	blockSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	blockSprite->setPosition(m_BlockSize * 0.5f);
	addChild(blockSprite, 1);
}
