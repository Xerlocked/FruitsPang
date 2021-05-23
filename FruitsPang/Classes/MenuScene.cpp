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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Images/Background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(background, 0);

	float rX = visibleSize.width / background->getContentSize().width;
	float rY = visibleSize.height / background->getContentSize().height;

	background->setScaleX(rX);
	background->setScaleY(rY);

	auto Normal = Label::createWithTTF("Normal", "fonts/Jellee-Roman.ttf", 24);
	auto Reverse = Label::createWithTTF("Reverse", "fonts/Jellee-Roman.ttf", 24);
	auto Blink = Label::createWithTTF("Blink", "fonts/Jellee-Roman.ttf", 24);
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

	auto Normal = MenuItemLabel::create(Normal, CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto Reverse = MenuItemLabel::create(Reverse, CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto Blink = MenuItemLabel::create(Blink, CC_CALLBACK_1(MenuScene::menuCallback, this));

	auto menu = Menu::create(Normal, Reverse, Blink, nullptr);
	menu->alignItemsvertically();
	this->addChild(menu);
	menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	return true;
}

void MenuScene::menuCallback(Ref* pSender)
{
	Scene* game = GameScene::createScene();
	Director::getInstance()->replaceScene(game);
}
