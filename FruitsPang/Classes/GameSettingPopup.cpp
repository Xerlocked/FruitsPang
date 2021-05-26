#include "GameSettingPopup.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "DataManager.h"

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


	auto SoundOnSprite = Sprite::createWithSpriteFrameName("SoundOn.png");
	auto SoundOffSprite = Sprite::createWithSpriteFrameName("SoundOff.png");
	auto MusicOnSprite = Sprite::createWithSpriteFrameName("MusicOn.png");
	auto MusicOffSprite = Sprite::createWithSpriteFrameName("MusicOff.png");

	SoundOn = MenuItemSprite::create(SoundOnSprite, SoundOnSprite, [&](Ref* sender) {
		DataManager::getInstance()->ChangeSoundState(false);
		});
	SoundOff = MenuItemSprite::create(SoundOffSprite, SoundOffSprite, [&](Ref* sender) {
		DataManager::getInstance()->ChangeSoundState(true);
		});
	MusicOn = MenuItemSprite::create(MusicOnSprite, MusicOnSprite, [&](Ref* sender) {
		DataManager::getInstance()->ChangeMusicState(false);
		DataManager::getInstance()->PlayMusic(102, SOUND_IN_GAME_MUSIC);
		});
	MusicOff = MenuItemSprite::create(MusicOffSprite, MusicOffSprite, [&](Ref* sender) {
		DataManager::getInstance()->ChangeMusicState(true);
		DataManager::getInstance()->StopMusic();
		});

	auto SoundToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameSettingPopup::onClickToggle, this), SoundOn, SoundOff, NULL);

	auto MusicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameSettingPopup::onClickToggle, this), MusicOn, MusicOff, NULL);

	if (DataManager::getInstance()->getSoundState())
		SoundToggle->setSelectedIndex(1);

	if (DataManager::getInstance()->getMusicState())
		MusicToggle->setSelectedIndex(1);


	Menu* pMenu = Menu::create(SoundToggle, MusicToggle, NULL);
	pMenu->alignItemsHorizontally();
	pMenu->alignItemsHorizontallyWithPadding(36);
	pMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 228));
	this->addChild(pMenu, 10);
	return true;
}

void GameSettingPopup::onEnter()
{
	Layer::onEnter();
	auto visibleSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
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

	DataManager::getInstance()->PlaySoundW(SOUND_SELECT_EFFECT);

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

void GameSettingPopup::onClickToggle(Ref* sender)
{
	MenuItemToggle* toggleItem = (MenuItemToggle*)sender;

	if (toggleItem->getSelectedItem() == SoundOn)
	{
		DataManager::getInstance()->ChangeSoundState(false);
	}
	else if (toggleItem->getSelectedItem() == SoundOff) 
	{
		DataManager::getInstance()->ChangeSoundState(true);
	}
	else if (toggleItem->getSelectedItem() == MusicOn) {
		DataManager::getInstance()->ChangeMusicState(false);
		DataManager::getInstance()->PlayMusic(102, SOUND_IN_GAME_MUSIC);
	}
	else if (toggleItem->getSelectedItem() == MusicOff) {
		DataManager::getInstance()->ChangeMusicState(true);
		DataManager::getInstance()->StopMusic();
	}
}
