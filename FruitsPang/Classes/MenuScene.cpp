#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
		return false;


	Size screenSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	Sprite* background = Sprite::create("Images/UI/Background.png");
	background->setPosition(origin.x + screenSize.width / 2, origin.y + screenSize.height / 2);
	addChild(background, 0);

	/*Sprite* Menu_title = Sprite::create("Images/UI/GameTitle.png");
	Menu_title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	Menu_title->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height + 120));
	addChild(Menu_title, 1);*/


	float rX = screenSize.width / background->getContentSize().width;
	float rY = screenSize.height / background->getContentSize().height;

	background->setScaleX(rX);
	background->setScaleY(rY);

	auto Normal = Label::createWithTTF("Normal", "fonts/Jellee-Roman.ttf", 24);
	auto normal_item = MenuItemLabel::create(Normal);
	
	auto Reverse = Label::createWithTTF("Reverse", "fonts/Jellee-Roman.ttf", 24);
	auto reverse_item = MenuItemLabel::create(Reverse);

	auto Blink = Label::createWithTTF("Blink", "fonts/Jellee-Roman.ttf", 24);
	auto blink_item = MenuItemLabel::create(Blink);

	Normal->setTextColor(Color4B::WHITE);
	Reverse->setTextColor(Color4B::WHITE);
	Blink->setTextColor(Color4B::WHITE);

	/*MenuItemLabel* noraml_menu_item = MenuItemLabel::create(Normal, [&](Ref* sender) {
		CCLOG("Normal Clicked");

		Scene* game = GameScene::createScene();
		Director::getInstance()->replaceScene(game);
		});
	noraml_menu_item->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	Menu* menu = Menu::createWithItem(noraml_menu_item);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);*/

	auto menu = Menu::create(normal_item, reverse_item, blink_item, nullptr);
	menu->alignItemsVertically();
	this->addChild(menu);
	menu->setPosition(origin.x + screenSize.width / 2, origin.y + screenSize.height / 2);

	return true;
}

void MenuScene::menuCallback(Ref* pSender)
{
	Scene* game = GameScene::createScene();
	Director::getInstance()->replaceScene(game);
}
