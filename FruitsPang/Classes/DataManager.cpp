#include "DataManager.h"
#include <string>

using namespace std;

USING_NS_CC;

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

void DataManager::loadScore()
{
	BestScore[0] = UserDefault::getInstance()->getIntegerForKey("Normal");

	BestScore[1] = UserDefault::getInstance()->getIntegerForKey("Reverse");

	BestScore[2] = UserDefault::getInstance()->getIntegerForKey("Blink");

	CCLOG("[%d, %d, %d]", BestScore[0], BestScore[1], BestScore[2]);
}

void DataManager::setBestScore(int score)
{
	switch (g_PlayMode)
	{
	case PLAYMODE::NORAML:

		BestScore[0] = score;
		UserDefault::getInstance()->setIntegerForKey("Normal", score);
		break;

	case PLAYMODE::REVERSE:

		BestScore[1] = score;
		UserDefault::getInstance()->setIntegerForKey("Reverse", score);
		break;

	case PLAYMODE::BLINK:

		BestScore[2] = score;
		UserDefault::getInstance()->setIntegerForKey("Blink", score);
		break;
	}

	UserDefault::getInstance()->flush();
}

int DataManager::getBestScorePlayMode()
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

bool DataManager::init()
{
	BestScore[0] = 0;
	BestScore[1] = 0;
	BestScore[2] = 0;

	g_PlayMode = PLAYMODE::REVERSE;

	return true;
}
