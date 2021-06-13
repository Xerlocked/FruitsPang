#ifndef MANUAL_H
#define MANUAL_H
#include "cocos2d.h"
#include "cocos-ext.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;
USING_NS_CC_EXT;

class Manual : public Layer
{
public:
	Manual() = default;
	~Manual() = default;
	Manual(const Manual&) = default;

	static Manual* create();
	bool init();
	void onEnter();
	bool onTouchBegan(Touch* touch, Event* events);
	void onClickButton(Ref* object);
	void changeExplain();

private:
	cocos2d::Label* explainLabel;
	cocos2d::Sprite* explainTile;
	cocos2d::ui::Button* okButton;
	cocos2d::Size visibleSize;

	int exNum = 0;
};

#endif // !MANUAL_H
