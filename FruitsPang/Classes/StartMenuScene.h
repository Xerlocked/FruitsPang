#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocos2d.h"

class StartMenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCallback(Ref* pSender);
	
	void tick(float dt);
	virtual void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent);
	CCSprite* Continue;

	CREATE_FUNC(StartMenuScene);
};

#endif