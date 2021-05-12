#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "cocos2d.h"

const int MAX_MATCH = 3;

/// <summary>
/// Grid Size
/// </summary>
const int MAX_ROW = 7;
const int MAX_COL = 7;

const int SWIPE_TRESHOLD = 5; // Minum pixels for swipe move

const cocos2d::Size m_BlockSize = cocos2d::Size(80, 80);

const cocos2d::Size m_CellSize = cocos2d::Size(150, 150);

enum class BlockType : int
{
	NONE = -1,
	APPLE = 0,
	PEAR,
	ORANGE,
	GRAPE,
	BERRY,
	BANANA
};

enum class GridType : int
{
	NONE = -1,
	BASIC = 0
};

const std::map<BlockType, std::string> BlockTypeName
{
	{BlockType::APPLE, "fruits1.png"},
	{BlockType::PEAR, "fruits2.png"},
	{BlockType::ORANGE, "fruits3.png"},
	{BlockType::GRAPE, "fruits4.png"},
	{BlockType::BERRY, "fruits5.png"},
	{BlockType::BANANA, "fruits6.png"}
};

const std::map<GridType, std::string> GridTypeName
{
	{GridType::BASIC, "BasicTile.png"}
};

typedef struct {
	int row;
	int col;
} BoardPosition;

typedef struct {
	BoardPosition first;
	BoardPosition second;
} BoardMove;

typedef struct {
	int matches;
} EventMatchesData;

#endif // !CONSTANTS_H

