#include "Board.h"

USING_NS_CC;

Board* Board::createBoard(int rows, int cols)
{
	Board* board = new Board();

	if (board->init())
	{
		board->autorelease();

		board->setContentSize(Size(rows * m_CellSize.width, cols * m_CellSize.height));
		board->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

		return board;
	}

	return nullptr;
}

void Board::removeAll()
{
	stopAllActions();
	busy = false;

	for (int col = 0; col < MAX_COL; col++)
	{
		for (int row = 0; row < MAX_ROW; row++)
		{
			if (blocks[row][col] != nullptr)
			{
				removeChild(blocks[row][col]);
				blocks[row][col] = nullptr;
			}
		}

	}

}

void Board::generateRandomBlock()
{
	for (int col = 0; col < MAX_COL; col++)
	{
		for (int row = 0; row < MAX_ROW; row++)
		{
			Block* block = Block::createBlock((BlockType)random((int)BlockType::APPLE, (int)BlockType::BANANA), { row, col });

			while(checkForMatch(block) == true)
				block->setType((BlockType)random((int)BlockType::APPLE, (int)BlockType::BANANA));

			block->setPosition(row * m_BlockSize.width + m_BlockSize.width * 0.5f,
				col * m_BlockSize.height + m_BlockSize.height * 0.5f);

			addChild(block, 1);
			blocks[row][col] = block;

		}

	}
}

Block* Board::getBlockForPosition(cocos2d::Vec2 pos)
{
	unsigned int row = (unsigned int)ceil((pos.x - getPosition().x) / m_BlockSize.width) - 1;
	unsigned int col = (unsigned int)ceil((pos.y - getPosition().y) / m_BlockSize.height) - 1;

	CCASSERT((col < MAX_COL&& row < MAX_ROW), "INCORRECT ROW/COL, INDEX OUT OF RANGE");

	if (blocks[row][col])
		return blocks[row][col];

	return nullptr;
}

bool Board::isNeighbours(Block* first, Block* second)
{
	if (!first || !second)
		return false;

	int x = abs(first->boardPos.row - second->boardPos.row);
	int y = abs(first->boardPos.col - second->boardPos.col);

	return (x == 1 && y == 0) || (x == 0 && y == 1);
}

void Board::swapBlock(Block* first, Block* second)
{
	if (!first || !second)
		return;

	if (!isNeighbours(first, second))
	{
		CCLOGERROR("BLOCKS [%d, %d] and [%d, %d] are not neighbours!",
			first->boardPos.row,
			first->boardPos.col,
			second->boardPos.row,
			second->boardPos.col);
		return;
	}

	blocks[first->boardPos.row][first->boardPos.col] = second;
	blocks[second->boardPos.row][second->boardPos.col] = first;

	BoardPosition t_pos = first->boardPos;
	first->boardPos = second->boardPos;
	second->boardPos = t_pos;
}

bool Board::checkForMatch(Block* block)
{
	if (!block)
		return false;

	BoardPosition bp = block->boardPos;

	int match = 1;
	int row = bp.row;

	while (--row > -1 && blocks[row][bp.col] && blocks[row][bp.col]->getType() == block->getType()) // Check Left
		match++;

	row = bp.row;

	while (++row < MAX_ROW && blocks[row][bp.col] && blocks[row][bp.col]->getType() == block->getType()) // Check Right
		match++;

	if (match >= MAX_MATCH)
		return true;

	match = 1;
	int col = bp.col;
	while (--col > -1 && blocks[bp.row][col] && blocks[bp.row][col]->getType() == block->getType()) // Check Down
		match++;

	col = bp.col;
	while (++col < MAX_COL && blocks[bp.row][col] && blocks[bp.row][col]->getType() == block->getType()) // Check Up
		match++;

	return (match >= MAX_MATCH);
}

std::vector<Block*> Board::findMatch(Block* block, bool isRoot)
{
	if (isRoot)
		matches.clear();

	matches.push_back(block);

	BoardPosition bp = block->boardPos;

	Block* leftBlock = (bp.row > 0) ? blocks[bp.row - 1][bp.col] : nullptr;
	Block* rightBlock = (bp.row < MAX_ROW - 1) ? blocks[bp.row + 1][bp.col] : nullptr;
	Block* topBlock = (bp.col < MAX_COL - 1) ? blocks[bp.row][bp.col + 1] : nullptr;
	Block* bottomBlock = (bp.col > 0) ? blocks[bp.row][bp.col - 1] : nullptr;

	// Left
	if (leftBlock && leftBlock->getType() == block->getType())
	{
		if (std::find(matches.begin(), matches.end(), leftBlock) == matches.end())
			findMatch(leftBlock, false);
	}

	// Right
	if (rightBlock && rightBlock->getType() == block->getType())
	{
		if (std::find(matches.begin(), matches.end(), rightBlock) == matches.end())
			findMatch(rightBlock, false);
	}

	// TOP
	if (topBlock && topBlock->getType() == block->getType())
	{
		if (std::find(matches.begin(), matches.end(), topBlock) == matches.end())
			findMatch(topBlock, false);
	}

	// BOTTOM
	if (bottomBlock && bottomBlock->getType() == block->getType())
	{
		if (std::find(matches.begin(), matches.end(), bottomBlock) == matches.end())
			findMatch(bottomBlock, false);
	}

	return matches;
}

void Board::removeBlockAt(BoardPosition pos)
{
	Block* block = blocks[pos.row][pos.col];
	if (block)
	{
		blocks[pos.row][pos.col] = nullptr;
		block->setType(BlockType::NONE);
		removeChild(block, true);
	}
}

void Board::fillBlanks()
{
	busy = true;
	std::vector<Block*> addedBlocks;

	for (int row = 0; row < MAX_ROW; row++)
	{
		int blanks = 0;

		for (int col = 0; col < MAX_COL; col++)
		{
			if (blocks[row][col] == nullptr)
				blanks++;
			else if (blanks > 0)
			{
				int new_col = col - blanks;
				blocks[row][col]->runAction(EaseBounceOut::create(MoveTo::create(0.7f,
						Vec2(blocks[row][col]->getPositionX(),
						new_col * m_BlockSize.height + m_BlockSize.height * 0.5f))));

				blocks[row][new_col] = blocks[row][col];
				blocks[row][col] = nullptr;
				blocks[row][new_col]->boardPos = { row, new_col };

				addedBlocks.push_back(blocks[row][new_col]);
			}
		}

		while (blanks--)
		{
			int new_col = MAX_COL - blanks - 1;
			Block* block = Block::createBlock((BlockType)random((int)BlockType::APPLE, (int)BlockType::BANANA), { row, new_col });
			Vec2 newPosition = Vec2(row * m_BlockSize.width + m_BlockSize.width * 0.5f,
				new_col * m_BlockSize.height + m_BlockSize.height * 0.5f);
			block->setPositionX(newPosition.x);
			block->setPositionY(getContentSize().height + (MAX_COL - blanks) * m_BlockSize.height * 0.5f);
			block->boardPos = { row, new_col };
			block->runAction(EaseBounceOut::create(MoveTo::create(0.7f, newPosition)));

			addChild(block, 1);
			blocks[row][new_col] = block;
			addedBlocks.push_back(block);
		}

	}

	runAction(Sequence::create(
		DelayTime::create(0.75f),
		CallFunc::create(CC_CALLBACK_0(Board::resolveMatchForBlocks, this, addedBlocks)),
		NULL
	));
}

void Board::resolveMatchForBlocks(std::vector<Block*> blocks)
{
	bool hasMatch = false;
	std::vector<Block*> blocksToRemove;

	for (int i = 0; i < blocks.size(); i++)
	{
		Block* block = blocks.at(i);

		if (block && block->getType() != BlockType::NONE && checkForMatch(block))
		{
			hasMatch = true;
			for (auto match : findMatch(block))
			{
				if (std::find(blocksToRemove.begin(), blocksToRemove.end(), match) == blocksToRemove.end())
					blocksToRemove.push_back(match);
			}
		}

	}

	if (hasMatch)
	{
		EventCustom hasMatchEvent(EVENT_HAS_MATCH);
		EventMatchesData em;
		em.matches = (int)blocksToRemove.size();
		hasMatchEvent.setUserData((void*)&em);
		_eventDispatcher->dispatchEvent(&hasMatchEvent);


		for (auto block : blocksToRemove)
			removeBlockAt(block->boardPos);

		fillBlanks();
	}
	else
	{
		EventCustom ReadyEvent(EVENT_READY);
		_eventDispatcher->dispatchEvent(&ReadyEvent);
		busy = false;
	}
}

std::vector<BoardMove> Board::findAvailableMove()
{
	std::vector<BoardMove> availableMove;
	Block* other;

	for (int row = 0; row < MAX_ROW; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			Block* block = blocks[row][col];
			if (block == nullptr)
				continue;

			if (row < MAX_ROW - 1 && blocks[row + 1][col])
			{
				other = blocks[row + 1][col];
				swapBlock(block, other);

				if (checkForMatch(block) || checkForMatch(other))
					availableMove.push_back({ other->boardPos, block->boardPos });

				swapBlock(other, block);
			}

			if (col < MAX_COL - 1 && blocks[row][col + 1])
			{
				other = blocks[row][col + 1];

				swapBlock(block, other);

				if (checkForMatch(block) || checkForMatch(other))
					availableMove.push_back({ other->boardPos, block->boardPos });

				swapBlock(other, block);
			}

		}

	}

	return availableMove;
}

void Board::onEnter()
{
	Layer::onEnter();
}
