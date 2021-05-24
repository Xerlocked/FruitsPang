#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Board.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	void replayGame();

private:
	GameScene() = default;
	~GameScene() = default;
	GameScene(GameScene&) = default;

	cocos2d::ProgressTimer* ui_timer;
	cocos2d::Label* ui_timer_label;
	cocos2d::Label* ui_score;
	Block* activeBlock = nullptr;
	Board* board = nullptr;
	bool isBusy = false;
	bool isPlay = false;
	std::vector<BoardMove> availableMove;
	
	int		currentScore = 0;
	float _RemainTime;
	bool	isFade = false;

	void swipeBlock(Block* first, Block* second);
	void newGame(cocos2d::Ref* ref);
	void checkForMatch(Block* first, Block* second);
	void lockTouch(float time);
	void unlockTouch(float delTime);
	void resolveMatchForBlock(Block* block);
	void addScore(int score);

	void onBlink(float t);
	void setTimer();
	void updateTimer(float t);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* events);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* events);
	void onBoardReady(cocos2d::EventCustom* events);
	void onBoardMatch(cocos2d::EventCustom* events);
};

#endif // !_GAME_SCENE_H
