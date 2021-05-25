#include "DataManager.h"
#include <string>
#include "AudioEngine.h"

using namespace std;
USING_NS_CC;

using namespace experimental;
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

void DataManager::loadUserData()
{
	BestScore[0] = UserDefault::getInstance()->getIntegerForKey("Normal");

	BestScore[1] = UserDefault::getInstance()->getIntegerForKey("Reverse");

	BestScore[2] = UserDefault::getInstance()->getIntegerForKey("Blink");

	b_muteMusic = UserDefault::getInstance()->getBoolForKey("setMusic"); // 최초 실행시 값은 false

	b_muteSound = UserDefault::getInstance()->getBoolForKey("setSound"); // 최초 실행시 값은 false

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

void DataManager::PlaySound(const char* filename, bool loop, float volume)
{
	if (b_muteSound)
		return;

	AudioEngine::play2d(filename, loop, volume);
}

void DataManager::PlayMusic(int id, const char* filename, bool loop, float volume)
{
	if (b_muteMusic)
		return;

	AudioEngine::stopAll();

	switch (id)
	{
	case 101:
		if (AudioEngine::getState(BGM_ID1) != AudioEngine::AudioState::PLAYING)
			BGM_ID1 = AudioEngine::play2d(filename, true);
		break;

	case 102:
		if (AudioEngine::getState(BGM_ID2) != AudioEngine::AudioState::PLAYING)
			BGM_ID2 = AudioEngine::play2d(filename);
		break;

	default:
		break;
	}
}

void DataManager::PauseMusic()
{
	if (AudioEngine::getState(BGM_ID2) == AudioEngine::AudioState::PLAYING)
		AudioEngine::pause(BGM_ID2);
}

void DataManager::ResumeMusic()
{
	if (AudioEngine::getState(BGM_ID2) == AudioEngine::AudioState::PAUSED)
		AudioEngine::resume(BGM_ID2);
}

void DataManager::ChangeSoundState(bool value)
{
	b_muteSound = value;
	UserDefault::getInstance()->setBoolForKey("setSound", b_muteSound);
	UserDefault::getInstance()->flush();
}

void DataManager::ChangeMusicState(bool value)
{
	b_muteMusic = value;
	if (b_muteMusic)
		AudioEngine::stopAll();

	UserDefault::getInstance()->setBoolForKey("setMusic", b_muteMusic);
	UserDefault::getInstance()->flush();
}

bool DataManager::init()
{
	g_PlayMode = PLAYMODE::REVERSE;
	AudioEngine::preload(SOUND_LOBBY_MUSIC);
	AudioEngine::preload(SOUND_IN_GAME_MUSIC);
	return true;
}
