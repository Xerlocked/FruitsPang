#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "cocos2d.h"


class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();

};

#endif // !_GAME_SCENE_H
