#include "GameSettingPopup.h"
#include "GameScene.h"
#include "MenuScene.h"

GameSettingPopup* GameSettingPopup::create()
{
	GameSettingPopup* ret = nullptr;
	try
	{
		ret = new GameSettingPopup();
		if (!ret->init())
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

bool GameSettingPopup::init()
{
	auto visibleSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);
	this->addChild(fadeBack);
	fadeBack->runAction(FadeTo::create(0.5f, 100));

	auto resumeButton = ui::Button::create("Images/BlueSquareButton.png");
	resumeButton->setTitleText("RESUME");
	resumeButton->setTitleFontName("fonts/Jellee-Roman.ttf");
	resumeButton->setTitleFontSize(36);
	resumeButton->setTitleAlignment(TextHAlignment::CENTER);
	resumeButton->setTag(1);
	resumeButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 126));
	resumeButton->addClickEventListener(CC_CALLBACK_1(GameSettingPopup::onClickButton, this));
	this->addChild(resumeButton, 10);

	auto replayButton = ui::Button::create("Images/GreenSquareButton.png");
	replayButton->setTitleText("REPLAY");
	replayButton->setTitleFontName("fonts/Jellee-Roman.ttf");
	replayButton->setTitleFontSize(36);
	replayButton->setTitleAlignment(TextHAlignment::CENTER);
	replayButton->setTag(2);
	replayButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	replayButton->addClickEventListener(CC_CALLBACK_1(GameSettingPopup::onClickButton, this));
	this->addChild(replayButton, 10);

	auto exitButton = ui::Button::create("Images/RedSquareButton.png");
	exitButton->setTitleText("EXIT");
	exitButton->setTitleFontName("fonts/Jellee-Roman.ttf");
	exitButton->setTitleFontSize(36);
	exitButton->setTitleAlignment(TextHAlignment::CENTER);
	exitButton->setTag(3);
	exitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 126));
	exitButton->addClickEventListener(CC_CALLBACK_1(GameSettingPopup::onClickButton, this));
	this->addChild(exitButton, 10);

	return true;
}

void GameSettingPopup::onEnter()
{
	Layer::onEnter();
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}

bool GameSettingPopup::onTouchBegan(Touch* touch, Event* events)
{
	return true;
}

void GameSettingPopup::onClickButton(Ref* object)
{
	const int getTag = ((Node*)object)->getTag();

	auto parent = (GameScene*)this->getParent();

	switch (getTag)
	{
	case 1:
		setTouchEnabled(false);
		parent->ResumeScene();
		this->removeAllChildrenWithCleanup(true);
		break;

	case 2:
		parent->replayGame();
		setTouchEnabled(false);
		this->removeAllChildrenWithCleanup(true);
		break;

	case 3:
		Scene * menu = MenuScene::createScene();
		Director::getInstance()->replaceScene(menu);
		break;
	}
}
