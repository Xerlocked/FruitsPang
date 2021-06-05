#include "Board.h"
#include "DataManager.h"

USING_NS_CC;

Board* Board::createBoard(int rows, int cols)
{
	Board* board = nullptr;

	try
	{
		board = new Board();
		if (!board->init())
			throw std::bad_alloc();
		board->autorelease();
		board->setContentSize(Size(rows * m_CellSize.width, cols * m_CellSize.height));
		board->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

		return board;
	}
	catch (...)
	{
		CC_SAFE_DELETE(board);
		throw;

	}
}

void Board::removeAllBlocks()
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

			block->setPosition(row * m_CellSize.width + m_CellSize.width * 0.5f,
				col * m_CellSize.height + m_CellSize.height * 0.5f);

			addChild(block, 3);
			blocks[row][col] = block;

		}

	}
}

void Board::generateCell()
{
	for (int col = 0; col < MAX_COL; col++)
	{
		for (int row = 0; row < MAX_ROW; row++)
		{
			GridCell* cell = GridCell::createCell(CellType::BASIC, { row, col });
			cell->setPosition(row * m_CellSize.width + m_CellSize.width * 0.5f,
				col * m_CellSize.height + m_CellSize.height * 0.5f);

			addChild(cell,2);
		}
	}

}

Block* Board::getBlockForPosition(cocos2d::Vec2 pos)
{
	unsigned int row = (unsigned int)ceil((pos.x - getPosition().x) / m_CellSize.width) - 1;
	unsigned int col = (unsigned int)ceil((pos.y - getPosition().y) / m_CellSize.height) - 1;

	CCASSERT((col < MAX_COL&& row < MAX_ROW), "INCORRECT ROW/COL, INDEX OUT OF RANGE");

	if (blocks[row][col])
		return blocks[row][col];

	return nullptr;
}

bool Board::isNeighbours(Block* first, Block* second)
{
	if (!first || !second)
		return false;

	int x = abs(first->boardPosition.row - second->boardPosition.row);
	int y = abs(first->boardPosition.col - second->boardPosition.col);

	return (x == 1 && y == 0) || (x == 0 && y == 1);
}

void Board::swapBlock(Block* first, Block* second)
{
	if (!first || !second)
		return;

	if (!isNeighbours(first, second))
	{
		CCLOGERROR("BLOCKS [%d, %d] and [%d, %d] are not neighbours!",
			first->boardPosition.row,
			first->boardPosition.col,
			second->boardPosition.row,
			second->boardPosition.col);
		return;
	}

	blocks[first->boardPosition.row][first->boardPosition.col] = second;
	blocks[second->boardPosition.row][second->boardPosition.col] = first;

	BoardPosition t_pos = first->boardPosition;
	first->boardPosition = second->boardPosition;
	second->boardPosition = t_pos;
}

bool Board::checkForMatch(Block* block)
{
	if (!block)
		return false;

	BoardPosition bp = block->boardPosition;

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

int Board::findMatch(Block* block, std::vector<Block*> &matches, bool isRoot)
{
	if (isRoot)
		matches.clear();

	int leftCount	= 0;
	int rightCount	= 0;
	int upCount		= 0;
	int downCount	= 0;

	matches.push_back(block);

	BoardPosition bp = block->boardPosition;

	// 1. 오른쪽 방향
	for (int i = bp.row + 1; i < MAX_ROW; i++)
	{
		if (blocks[i][bp.col] == nullptr || blocks[i][bp.col]->getType() != block->getType())
			break;

		matches.push_back(blocks[i][bp.col]);
		rightCount++;
	}

	// 2. 왼쪽 방향
	for (int i = bp.row - 1; i >= 0; i--)
	{
		if (blocks[i][bp.col] == nullptr || blocks[i][bp.col]->getType() != block->getType())
			break;

		matches.push_back(blocks[i][bp.col]);
		leftCount++;
	}

	if ((leftCount == 1 && rightCount == 0) || (leftCount == 0 && rightCount == 1)) // 미완성 L자 판별 
		matches.pop_back();

	// 3. 위쪽 방향
	for (int i = bp.col + 1; i < MAX_COL; i++)
	{
		if (blocks[bp.row][i] == nullptr || blocks[bp.row][i]->getType() != block->getType())
			break;

		matches.push_back(blocks[bp.row][i]);
		upCount++;
	}

	// 4. 아래쪽 방향
	for (int i = bp.col - 1; i >= 0; i--)
	{
		if (blocks[bp.row][i] == nullptr || blocks[bp.row][i]->getType() != block->getType())
			break;

		matches.push_back(blocks[bp.row][i]);
		downCount++;
	}

	if ((upCount == 0 && downCount == 1) || (upCount == 1 && downCount == 0)) // 미완성 L자 판별 
		matches.pop_back();

	return matches.size();
}

void Board::removeBlockAt(BoardPosition pos)
{
	Block* block = blocks[pos.row][pos.col];
	if (block)
	{
		blocks[pos.row][pos.col] = nullptr;
		block->explode();
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
						new_col * m_CellSize.height + m_CellSize.height * 0.5f))));

				blocks[row][new_col] = blocks[row][col];
				blocks[row][col] = nullptr;
				blocks[row][new_col]->boardPosition = { row, new_col };

				addedBlocks.push_back(blocks[row][new_col]);
			}
		}

		while (blanks--)
		{
			int new_col = MAX_COL - blanks - 1;
			Block* block = Block::createBlock((BlockType)random((int)BlockType::APPLE, (int)BlockType::BANANA), { row, new_col });
			Vec2 newPosition = Vec2(row * m_CellSize.width + m_CellSize.width * 0.5f,
				new_col * m_CellSize.height + m_CellSize.height * 0.5f);
			block->setPositionX(newPosition.x);
			block->setPositionY(getContentSize().height + (MAX_COL - blanks) * m_CellSize.height * 0.5f);
			block->boardPosition = { row, new_col };
			block->runAction(EaseBounceOut::create(MoveTo::create(0.7f, newPosition)));

			addChild(block, 2);
			blocks[row][new_col] = block;
			addedBlocks.push_back(block);
		}

	}

	runAction(Sequence::create(
		DelayTime::create(0.75f),
		CallFunc::create(CC_CALLBACK_0(Board::resolveMatchForBlocks, this, addedBlocks)),
		NULL
	));

	DataManager::getInstance()->PlaySoundW(SOUND_LINE_CREATE);
}

void Board::resolveMatchForBlocks(std::vector<Block*> blocks)
{
	int numMatches = 0;
	std::vector<Block*> blocksToRemove;

	for (auto block : blocks)
	{
		if (checkForMatch(block))
		{
			std::vector<Block*> matches;
			numMatches += findMatch(block, matches);

			for (auto match : matches)
			{
				if (std::find(blocksToRemove.begin(), blocksToRemove.end(), match) == blocksToRemove.end())
					blocksToRemove.push_back(match);
			}

		}
	}

	if (numMatches > 0)
	{
		EventCustom haveMatchEvent(EVENT_HAS_MATCH);
		EventMatchesData em;
		em.matches = numMatches * 200;
		haveMatchEvent.setUserData((void*)&em);
		_eventDispatcher->dispatchEvent(&haveMatchEvent);

		for (auto block : blocksToRemove)
		{
			removeBlockAt(block->boardPosition);
		}

		fillBlanks();
	}
	else
	{
		EventCustom ReadyMatchEvent(EVENT_READY);
		_eventDispatcher->dispatchEvent(&ReadyMatchEvent);

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
					availableMove.push_back({ other->boardPosition, block->boardPosition });

				swapBlock(other, block);
			}

			if (col < MAX_COL - 1 && blocks[row][col + 1])
			{
				other = blocks[row][col + 1];

				swapBlock(block, other);

				if (checkForMatch(block) || checkForMatch(other))
					availableMove.push_back({ other->boardPosition, block->boardPosition });

				swapBlock(other, block);
			}

		}

	}

	return availableMove;
}

void Board::Blink()
{
	
}

void Board::onEnter()
{
	Layer::onEnter();
}
