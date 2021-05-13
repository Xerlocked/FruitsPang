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
	Block* activeBlock;
	Board* board;
	bool isBusy;
	std::vector<BoardMove> availableMove;
	
	void swapBox(Block* first, Block* second);
	void newGame(cocos2d::Ref* ref);
	void checkForMatch(Block* first, Block* second);
	void lockTouch(float time);
	void unlockTouch(float delTime);
	void resolveMatchForBlock(Block* block);

	void onBoardReady(cocos2d::EventCustom* events);

};

#endif // !_GAME_SCENE_H
