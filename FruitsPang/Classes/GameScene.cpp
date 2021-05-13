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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/data.plist");
	Director::getInstance()->getTextureCache()->addImage("Images/GameSceneBackground.png");

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

	board = Board::createBoard(MAX_ROW, MAX_COL);

	board->setPosition(screenSize.width * 0.5f - board->getContentSize().width * 0.5f,
		screenSize.height * 0.5f - board->getContentSize().height * 0.5f - 30);
	addChild(board, 1);

	board->generateCell();
	board->generateRandomBlock();

	CCLOG("onEnter");
}

void GameScene::swapBox(Block* first, Block* second)
{
}

void GameScene::newGame(cocos2d::Ref* ref)
{
}

void GameScene::checkForMatch(Block* first, Block* second)
{
}

void GameScene::lockTouch(float time)
{
}

void GameScene::unlockTouch(float delTime)
{
}

void GameScene::resolveMatchForBlock(Block* block)
{
}

void GameScene::onBoardReady(cocos2d::EventCustom* events)
{
}
