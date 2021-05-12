/// <summary>
/// Fruits Node Class
/// <summary>
#ifndef BLOCK_H
#define BLOCK_H

#include "cocos2d.h"
#include "Global.h"

class Block : public cocos2d::Node
{
public:
	static Block* createBlock(BlockType Type, BoardPosition pos);
	void setActive(bool isActive);
	void Blink(int times = 3);
	BoardPosition boardPos;
	BlockType getType() noexcept{ return type; }

	void setType(BlockType Type);

	void explode();

	virtual void onEnter();

private:
	BlockType type;
	cocos2d::Sprite* blockSprite;
};

#endif // !BLOCK_H