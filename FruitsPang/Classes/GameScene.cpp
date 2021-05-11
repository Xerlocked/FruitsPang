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

	Size screenSize = Director::getInstance()->getVisibleSize();

	auto background = Layer::create();
	background->setColor(Color3B::BLACK);
	addChild(background);

	CCLOG("onEnter");
}