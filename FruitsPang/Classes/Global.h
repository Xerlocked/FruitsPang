#ifndef GLOBAL_H
#define GLOBAL_H

#include "cocos2d.h"
#include <string>

const auto EVENT_READY		= "event.custom.is_ready";
const auto EVENT_HAS_MATCH	= "event.custom.has_match";
const auto EVENT_FADE_OUT	= "event.custom.fade.out";
const auto EVENT_FADE_IN	= "event.custom.fade.in";

const auto SOUND_IN_GAME_MUSIC	= "Sounds/bgm01.mp3";
const auto SOUND_LOBBY_MUSIC	= "Sounds/menubgm01.mp3";
const auto SOUND_SELECT_EFFECT	= "Sounds/tap01.mp3";
const auto SOUND_TIME_OVER		= "Sounds/sound1.mp3";
const auto SOUND_REMOVE_BLOCK	= "Sounds/match01.mp3";
const auto SOUND_SHOW_RECORD	= "Sounds/sound2.mp3";
const auto SOUND_REMOVE_BLOCK_2 = "Sounds/match02.mp3";
const auto SOUND_LINE_CREATE	= "Sounds/linecreate01.mp3";
const auto SOUND_SWAP			= "Sounds/swap01.mp3";
const auto SOUND_SWAP_ERROR		= "Sounds/swaperror01.mp3";
const auto SOUND_NO_MATCH		= "Sounds/shuffle01.mp3";

//const auto COLOR_BROWN = cocos2d::Color3B(173,138,122);

const int MAX_MATCH = 3;
const int MAX_ROW = 7;
const int MAX_COL = 7;

const int SWIPE_TRESHOLD = 10; // Minum pixels for swipe move

const cocos2d::Size m_BlockSize = cocos2d::Size(128, 150);

const cocos2d::Size m_CellSize = cocos2d::Size(148, 148);

enum class PLAYMODE : int
{
	NORAML = 0,
	REVERSE,
	BLINK
};

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

static char buf[1024] = { 0, };
static int util_add_comma_to_num(const char* str, char* buf, int buflen)
{
	int len;
	int shift;

	/* count given string */
	len = strlen(str);
	shift = -len;

	assert(buflen >= (len + len / 3 + 1));

	while (*str)
	{
		*buf++ = *str++;
		if (++shift && (shift % 3) == 0)
			*buf++ = ',';
	}

	*buf = '\0';

	return 0;
}

struct Sound
{
public:
	const char* BACKGROUND = "aaa";

};

#endif // !GLOBAL_H

