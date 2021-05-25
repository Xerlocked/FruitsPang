#include "MenuScene.h"
#include "GameScene.h"
#include "DataManager.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Images/Background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(background, 0);

	float rX = visibleSize.width / background->getContentSize().width;
	float rY = visibleSize.height / background->getContentSize().height;

	background->setScaleX(rX);
	background->setScaleY(rY);

	Label* Normal = Label::createWithTTF("Normal", "fonts/Jellee-Roman.ttf", 24);
	Normal->setTextColor(Color4B::WHITE);

	MenuItemLabel* noraml_menu_item = MenuItemLabel::create(Normal, [&](Ref* sender) {
		CCLOG("Click");

		Scene* game = GameScene::createScene();
		DataManager::getInstance()->setPlayMode(PLAYMODE::NORAML);
		Director::getInstance()->replaceScene(game);
		});
	noraml_menu_item->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	Menu* menu = Menu::createWithItem(noraml_menu_item);
	menu->setPosition(Vec2::ZERO);

	addChild(menu, 1);

	
}

void MenuScene::onEnter()
{
	Scene::onEnter();
	DataManager::getInstance()->PlayMusic(101,SOUND_LOBBY_MUSIC, true);
}
