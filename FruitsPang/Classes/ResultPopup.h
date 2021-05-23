#ifndef RESULT_POPUP_H
#define RESULT_POPUP_H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class ResultPopup : public Layer
{
public:
	ResultPopup();
	~ResultPopup();

	static ResultPopup* create(int score);
	bool init(int score);
	void onEnter();
	bool onTouchBegan(Touch* touch, Event* events);
	void onClickButton(Ref* obj);
};


#endif // !RESULT_POPUP_H
