#include "ResultPopup.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "DataManager.h"

ResultPopup* ResultPopup::create(int score)
{
	ResultPopup* ret = nullptr;

	try
	{
		ret = new ResultPopup();
		if (!ret->init(score))
			throw std::bad_alloc();
		ret->autorelease();
		return ret;
	}
	catch (...)
	{
		CC_SAFE_DELETE(ret);
		throw;
	}
}

bool ResultPopup::init(int score)
{
	auto visibleSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);

	this->addChild(fadeBack);

	fadeBack->runAction(FadeTo::create(0.5f, 200));

	back = Sprite::createWithSpriteFrameName("Result.png");

	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(back, 10);

	ui_BestScore = Label::createWithTTF("0", "fonts/Vagron.ttf", 130);
	ui_BestScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_BestScore->setPosition(Vec2(back->getContentSize().width / 2, back->getContentSize().height / 2 + 100));
	ui_BestScore->setTextColor(Color4B(251, 50, 100,255));
	back->addChild(ui_BestScore, 11);

	ui_Score = Label::createWithTTF("0", "fonts/Vagron.ttf", 100);
	ui_Score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_Score->setPosition(Vec2(back->getContentSize().width / 2, back->getContentSize().height / 2 - 165));
	ui_Score->setTextColor(Color4B::WHITE);
	back->addChild(ui_Score, 11);

	auto ReplayButton = ui::Button::create("ReplayButton.png", "", "", ui::Widget::TextureResType::PLIST);
	ReplayButton->setTag(1);
	ReplayButton->setPosition(Vec2(back->getContentSize().width / 2 - 200, 0));
	ReplayButton->addClickEventListener(CC_CALLBACK_1(ResultPopup::onClickButton, this));
	back->addChild(ReplayButton, 11);

	auto MenuButton = ui::Button::create("MenuButton.png", "", "", ui::Widget::TextureResType::PLIST);
	MenuButton->setTag(2);
	MenuButton->setPosition(Vec2(back->getContentSize().width / 2 + 200, 0));
	MenuButton->addClickEventListener(CC_CALLBACK_1(ResultPopup::onClickButton, this));
	back->addChild(MenuButton, 11);

	auto actionBestScore = ActionFloat::create(1.5f, 0, DataManager::getInstance()->getBestScorePlayMode(), [&](int value)
		{
			util_add_comma_to_num(std::to_string(value).c_str(), buf, 1024);
			ui_BestScore->setString(buf);
		});

	auto actionScore = ActionFloat::create(1.5f, 0, score, [&](int value)
		{
			util_add_comma_to_num(std::to_string(value).c_str(), buf, 1024);
			ui_Score->setString(buf);
		});
	auto seq = Sequence::create(actionBestScore, actionScore, NULL);

	runAction(seq);

	return true;
}

void ResultPopup::onEnter()
{
	Layer::onEnter();
	setTouchEnabled(true); /// 뒤 레이어 터치 방지

	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

}

bool ResultPopup::onTouchBegan(Touch* touch, Event* events)
{
	return true;
}

void ResultPopup::onClickButton(Ref* obj)
{
	const int getTag = ((Node*)obj)->getTag();

	auto parent = (GameScene*)this->getParent();

	switch (getTag)
	{
	case 1:
		parent->replayGame();
		setTouchEnabled(false);
		this->stopAllActions();
		this->removeAllChildrenWithCleanup(true);
		break;

	case 2:
		Scene * menu = MenuScene::createScene();
		Director::getInstance()->replaceScene(menu);
		break;
	}
}
