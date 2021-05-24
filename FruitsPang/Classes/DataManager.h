#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "cocos2d.h"
#include "Global.h"
#include <sstream>
#include <vector>

class DataManager
{
public:
	DataManager() = default;
	~DataManager() = default;
	DataManager(const DataManager&) = default;

	static DataManager* getInstance();
	bool init();

	PLAYMODE getPlayMode() noexcept { return g_PlayMode; }
	void setPlayMode(PLAYMODE mode);

	void loadScore();
	void setBestScore(int score);

	int getBestScorePlayMode();
	int getBestScoreNormal() noexcept { return BestScore[0]; }
	int getBestScoreReverse() noexcept { return BestScore[1]; }
	int getBestScoreBlink() noexcept { return BestScore[2]; }

/// <summary>
/// Sound Path
/// </summary>
	const char* SOUND_IN_GAME_MUSIC = "Sounds/Background1.mp3";
	const char* SOUND_LOBBY_MUSIC = "Sounds/Background2.mp3";
	const char* SOUND_SELECT_EFFECT = "Sounds/sound5.mp3";
	const char* SOUND_TIME_OVER = "Sounds/sound1.mp3";
	const char* SOUND_REMOVE_BLOCK = "Sounds/sound9.mp3";
	const char* SOUND_NEW_RECORD = "Sounds/sound2.mp3";

private:
public:

private:
	/// <summary>
	/// BestScore - Normal, Reverse, Blink
	/// </summary>
	int BestScore[3];
	PLAYMODE g_PlayMode;
};

#endif // !DATA_MANAGER_H

