#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	
	cocos2d::Label* labelMode;

	virtual bool init();
	virtual void onEnter();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* events);
	void onClickButton(Ref* object);
	
	void SetPlayMode();

private:
	int		playNumber = 0;

	const int NUM_PLAYMODE_NORMAL	= 0;
	const int NUM_PLAYMODE_BLINK	= 1;
	const int NUM_PLAYMODE_REVERSE	= 2;
};

#endif