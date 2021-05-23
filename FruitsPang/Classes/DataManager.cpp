#include "DataManager.h"
#include <string>

using namespace std;

static DataManager* s_DM = nullptr;

DataManager* DataManager::getInstance()
{
	if (!s_DM)
	{
		s_DM = new (std::nothrow) DataManager;
		_ASSERT(s_DM, "FAIL DATAMANAGER");
		s_DM->init();
	}

	return s_DM;
}

void DataManager::setPlayMode(PLAYMODE mode)
{
	if (g_PlayMode == mode)
		return;
	g_PlayMode = mode;
}

void DataManager::loadScore(std::string text)
{
	vector<string> r = split(text, ',');

	for (int i = 0; i < 3; i++)
	{
		BestScore[i] = stoi(r.at(i));
	}

	CCLOG("[%d, %d, %d]", BestScore[0], BestScore[1], BestScore[2])
}

unsigned int DataManager::getBestScorePlayMode()
{
	switch (g_PlayMode)
	{
	case PLAYMODE::NORAML:
		return BestScore[0];
		
	case PLAYMODE::REVERSE:
		return BestScore[1];

	case PLAYMODE::BLINK:
		return BestScore[2];
	}
}

vector<std::string> DataManager::split(const std::string& s, char delim)
{

	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

bool DataManager::init()
{
	BestScore[0] = 0;
	BestScore[1] = 0;
	BestScore[2] = 0;

	g_PlayMode = PLAYMODE::NORAML;

	return true;
}
