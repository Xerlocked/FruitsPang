#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto gameScene = new GameScene();

	gameScene->autorelease();

	if (gameScene->init())
		scene->addChild(gameScene);
	else
		return nullptr;

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	CCLOG("init");

	return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();

	/// <summary>
	/// GameScene
	/// </summary>
	Size screenSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto background = Sprite::create("Images/GameSceneBackground.png");
	background->setPosition(origin.x + screenSize.width / 2, origin.y + screenSize.height / 2);
	
	float rX = screenSize.width / background->getContentSize().width;
	float rY = screenSize.height / background->getContentSize().height;

	background->setScaleX(rX);
	background->setScaleY(rY);
	addChild(background, 0);

	

	CCLOG("onEnter");
}