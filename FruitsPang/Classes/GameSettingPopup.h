#ifndef GAME_SETTING_POPUP_H
#define GAME_SETTING_POPUP_H
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameSettingPopup : public Layer
{
public:
	GameSettingPopup() = default;
	~GameSettingPopup() = default;
	GameSettingPopup(const GameSettingPopup&) = default;

	static GameSettingPopup* create();
	bool init();
	void onEnter();
	bool onTouchBegan(Touch* touch, Event* events);
	void onClickButton(Ref* object);

private:

};

#endif // !GAME_SETTING_POPUP_H
