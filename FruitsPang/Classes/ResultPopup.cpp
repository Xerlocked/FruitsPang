#include "ResultPopup.h"
#include "MenuScene.h"
#include "GameScene.h"

ResultPopup::ResultPopup()
{
}

ResultPopup::~ResultPopup()
{
}

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

	auto back = Sprite::createWithSpriteFrameName("Result.png");

	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(back, 10);

	auto ui_BestScore = Label::createWithTTF("987,654,321", "fonts/Vagron.ttf", 130);
	ui_BestScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_BestScore->setPosition(Vec2(back->getContentSize().width / 2, back->getContentSize().height / 2 + 100));
	ui_BestScore->setTextColor(Color4B(251, 50, 100,255));
	back->addChild(ui_BestScore, 11);

	auto ui_Score = Label::createWithTTF(std::to_string(score), "fonts/Vagron.ttf", 100);
	ui_Score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_Score->setPosition(Vec2(back->getContentSize().width / 2, back->getContentSize().height / 2 - 165));
	ui_Score->setTextColor(Color4B::WHITE);
	back->addChild(ui_Score, 11);

	auto btn_Replay = Sprite::createWithSpriteFrameName("ReplayButton.png");

	auto itemReplay = MenuItemSprite::create(btn_Replay, NULL, CC_CALLBACK_1(ResultPopup::onClickButton, this));
	itemReplay->setTag(1);
	itemReplay->setPosition(Vec2(back->getContentSize().width / 2 - 200, 0));

	auto btn_Menu = Sprite::createWithSpriteFrameName("MenuButton.png");

	auto itemMenu = MenuItemSprite::create(btn_Menu, NULL, CC_CALLBACK_1(ResultPopup::onClickButton, this));
	itemMenu->setTag(2);
	itemMenu->setPosition(Vec2(back->getContentSize().width / 2 + 200, 0));

	auto menu = Menu::create(itemReplay, itemMenu, NULL);
	menu->setPosition(Vec2::ZERO);
	back->addChild(menu);

	/// 점수 애니메이션
	//auto actionBestScore = ActionFloat::create(1.5f, 0, currentScore + score, [&](int value)
	//	{
	//		ui_BestScore->setString(std::to_string(value));
	//	});

	//auto actionScore = ActionFloat::create(1.5f, 0, currentScore + score, [&](int value)
	//	{
	//		ui_Score->setString(std::to_string(value));
	//	});

	//auto seq = Sequence::create(actionBestScore, actionScore, NULL);
	//runAction(seq);

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
		this->removeAllChildrenWithCleanup(true);
		break;

	case 2:
		Scene * menu = MenuScene::createScene();
		Director::getInstance()->replaceScene(menu);
		break;
	}
}
