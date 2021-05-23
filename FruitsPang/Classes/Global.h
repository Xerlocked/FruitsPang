#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "cocos2d.h"

const auto EVENT_READY		= "event.custom.is_ready";
const auto EVENT_HAS_MATCH	= "event.custom.has_match";
const auto EVENT_FADE_OUT	= "event.custom.fade.out";
const auto EVENT_FADE_IN	= "event.custom.fade.in";

//const auto COLOR_BROWN = cocos2d::Color3B(173,138,122);

const int MAX_MATCH = 3;

const int MAX_ROW = 7;
const int MAX_COL = 7;

const int SWIPE_TRESHOLD = 5; // Minum pixels for swipe move

const cocos2d::Size m_BlockSize = cocos2d::Size(128, 150);

const cocos2d::Size m_CellSize = cocos2d::Size(148, 148);

enum PLAYMODE
{
	NORAML = 0,
	REVERSE,
	BLINK
};

static short GLOBAL_PLAYMODE = PLAYMODE::NORAML;

enum class BlockType : int
{
	APPLE = 0,
	PEAR,
	ORANGE,
	GRAPE,
	BERRY,
	BANANA
};

enum class CellType : int
{
	BASIC = 0
};

const char* const BlockTypeName[]
{
	"fruits1.png",
	"fruits2.png",
	"fruits3.png",
	"fruits4.png",
	"fruits5.png",
	"fruits6.png"
};

const char* const CellTypeName[]
{
	"Basic.png"
};

struct BoardPosition {
	int row;
	int col;
};

struct BoardMove {
	BoardPosition first;
	BoardPosition second;
};

struct EventMatchesData {
	int matches;
};

#endif // !CONSTANTS_H

