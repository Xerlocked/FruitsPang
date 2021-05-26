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

	void loadUserData();
	void setBestScore(int score);

	int getBestScorePlayMode();
	int getBestScoreNormal() noexcept { return BestScore[0]; }
	int getBestScoreReverse() noexcept { return BestScore[1]; }
	int getBestScoreBlink() noexcept { return BestScore[2]; }

/// <summary>
/// Sound
/// </summary>
	void PlaySound(const char* filename, bool loop = false, float volume = 1.0f);
	void PlayMusic(int id, const char* filename, bool loop = false, float volume = 1.0f);
	void PauseMusic();
	void ResumeMusic();
	void StopMusic();
	void ChangeSoundState(bool value);
	void ChangeMusicState(bool value);

	bool getSoundState() noexcept { return b_muteSound; }
	bool getMusicState() noexcept { return b_muteMusic; }

private:
public:
private:
	/// <summary>
	/// BestScore - Normal, Reverse, Blink
	/// </summary>
	int BestScore[3];
	PLAYMODE g_PlayMode;
	bool b_muteSound;
	bool b_muteMusic;
	int BGM_ID1;
	int BGM_ID2;


};

#endif // !DATA_MANAGER_H

