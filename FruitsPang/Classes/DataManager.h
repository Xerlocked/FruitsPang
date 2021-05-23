#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

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

	void loadScore(std::string text);
	void setBestScore(int idx, unsigned int score) { BestScore[idx] = score; }

	int getBestScorePlayMode();
	int getBestScoreNormal() noexcept { return BestScore[0]; }
	int getBestScoreReverse() noexcept { return BestScore[1]; }
	int getBestScoreBlink() noexcept { return BestScore[2]; }

private:
	std::vector<std::string> split(const std::string& s, char delim);
public:

private:
	/// <summary>
	/// BestScore - Normal, Reverse, Blink
	/// </summary>
	int BestScore[3];
	PLAYMODE g_PlayMode;
};

#endif // !DATA_MANAGER_H

