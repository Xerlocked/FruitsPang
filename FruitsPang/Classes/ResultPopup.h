#ifndef RESULT_POPUP_H
#define RESULT_POPUP_H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ResultPopup : public Layer
{
public:
	ResultPopup() = default;
	~ResultPopup() = default;
	ResultPopup(const ResultPopup&) = default;

	static ResultPopup* create(int score);
	bool init(int score);
	void onEnter();
	bool onTouchBegan(Touch* touch, Event* events);
	void onClickButton(Ref* obj);

private:
	cocos2d::Label* ui_BestScore = nullptr;
	cocos2d::Label* ui_Score = nullptr;
	cocos2d::Sprite* back = nullptr;
};


#endif // !RESULT_POPUP_H
