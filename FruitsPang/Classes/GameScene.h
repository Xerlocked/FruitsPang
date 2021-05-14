#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "cocos2d.h"
#include "Board.h"


class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();

private:
	GameScene() = default;
	~GameScene() = default;
	GameScene(GameScene&) = default;

	Block* activeBlock = nullptr;
	Board* board = nullptr;
	bool isBusy = false;
	std::vector<BoardMove> availableMove;
	
	void swipeBlock(Block* first, Block* second);
	void newGame(cocos2d::Ref* ref);
	void checkForMatch(Block* first, Block* second);
	void lockTouch(float time);
	void unlockTouch(float delTime);
	void resolveMatchForBlock(Block* block);


	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* events);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* events);
	void onBoardReady(cocos2d::EventCustom* events);
	void onBoardMatch(cocos2d::EventCustom* events);
};

#endif // !_GAME_SCENE_H
