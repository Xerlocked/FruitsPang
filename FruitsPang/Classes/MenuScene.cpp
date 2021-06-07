#include "MenuScene.h"
#include "GameScene.h"
#include "DataManager.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	MenuScene* menuScene = nullptr;
	try
	{
		menuScene = new MenuScene();
		if (!menuScene->init())
			throw std::bad_alloc();
		menuScene->autorelease();
		scene->addChild(menuScene);

		return scene;
	}
	catch (...)
	{
		CC_SAFE_DELETE(menuScene);
		throw;
	}
}

bool MenuScene::init()
{
	if (!Layer::init())
		return false;

	CCLOG("MENU INIT");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Images/MenuBackground.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(background, 0);

	float rX = visibleSize.width / background->getContentSize().width;
	float rY = visibleSize.height / background->getContentSize().height;

	background->setScaleX(rX);
	background->setScaleY(rY);

	Sprite* girl = Sprite::create("Images/Girls.png");
	girl->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	girl->setPosition(Vec2(visibleSize.width / 2 - 280, visibleSize.height + 420));
	addChild(girl, 1);

	Sprite* title = Sprite::create("Images/MenuTitle.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 400));
	addChild(title, 1);

	auto playButton = ui::Button::create("Images/BlueSquareButton.png");
	playButton->setTitleText("Play");
	playButton->setTitleFontName("fonts/Jellee-Roman.ttf");
	playButton->setTitleFontSize(42);
	playButton->setTag(0);
	playButton->setTitleAlignment(TextHAlignment::CENTER);
	playButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3 - 200));
	playButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onClickButton, this));
	this->addChild(playButton, 10);

	auto exitButton = ui::Button::create("Images/RedSquareButton.png");
	exitButton->setTitleText("Exit");
	exitButton->setTitleFontName("fonts/Jellee-Roman.ttf");
	exitButton->setTitleFontSize(42);
	exitButton->setTag(1);
	exitButton->setTitleAlignment(TextHAlignment::CENTER);
	exitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3 - 326));
	exitButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onClickButton, this));
	this->addChild(exitButton, 10);

	auto leftArrow = ui::Button::create("Images/leftArrow.png");
	leftArrow->setTag(2);
	leftArrow->setPosition(Vec2(visibleSize.width / 2 - 155, visibleSize.height / 3 - 80));
	leftArrow->addClickEventListener(CC_CALLBACK_1(MenuScene::onClickButton, this));
	this->addChild(leftArrow, 10);

	auto rightArrow = ui::Button::create("Images/rightArrow.png");
	rightArrow->setTag(3);
	rightArrow->setPosition(Vec2(visibleSize.width / 2 + 155, visibleSize.height / 3 - 80));
	rightArrow->addClickEventListener(CC_CALLBACK_1(MenuScene::onClickButton, this));
	this->addChild(rightArrow, 10);

	playNumber = 0;
	DataManager::getInstance()->setPlayMode(PLAYMODE::NORAML);

	labelMode = Label::createWithTTF("NORMAL", "fonts/Jellee-Roman.ttf", 46);
	labelMode->setTextColor(Color4B::WHITE);
	labelMode->enableOutline(Color4B::BLACK, 2);
	labelMode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3 - 80));
	this->addChild(labelMode, 10);
	//MenuItemLabel* noraml_menu_item = MenuItemLabel::create(Normal, [&](Ref* sender) {
	//	CCLOG("Click");

	//	Scene* game = GameScene::createScene();
	//	DataManager::getInstance()->setPlayMode(PLAYMODE::NORAML);
	//	Director::getInstance()->replaceScene(game);
	//	});
	//noraml_menu_item->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	//Menu* menu = Menu::createWithItem(noraml_menu_item);
	//menu->setPosition(Vec2::ZERO);

	//addChild(menu, 1);

	return true;
}

void MenuScene::onEnter()
{
	Layer::onEnter();
	DataManager::getInstance()->PlayMusic(101,SOUND_LOBBY_MUSIC, true);
}

bool MenuScene::onTouchBegan(Touch* touch, Event* events)
{
	return true;
}

void MenuScene::onClickButton(Ref* object)
{
	const int getTag = ((Node*)object)->getTag();

	DataManager::getInstance()->PlaySoundW(SOUND_SELECT_EFFECT);

	switch (getTag)
	{
	case 0:
	{
		Scene* game = GameScene::createScene();
		Director::getInstance()->replaceScene(game);
	}
	break;

	case 1:
	{
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	}
	break;

	case 2:
	{
		if (playNumber <= NUM_PLAYMODE_NORMAL)
			playNumber = NUM_PLAYMODE_REVERSE;
		else
			playNumber--;

		SetPlayMode();
	}
	break;

	case 3:
	{
		if (playNumber >= NUM_PLAYMODE_REVERSE)
			playNumber = NUM_PLAYMODE_NORMAL;
		else
			playNumber++;

		SetPlayMode();
	}
	break;
	}

}

void MenuScene::SetPlayMode()
{

	if (playNumber == NUM_PLAYMODE_NORMAL)
	{
		labelMode->setString("NORMAL");
		DataManager::getInstance()->setPlayMode(PLAYMODE::NORAML);
	}
	else if (playNumber == NUM_PLAYMODE_BLINK)
	{
		labelMode->setString("BLINK");
		DataManager::getInstance()->setPlayMode(PLAYMODE::BLINK);
	}
	else
	{
		labelMode->setString("REVERSE");
		DataManager::getInstance()->setPlayMode(PLAYMODE::REVERSE);
	}
}
