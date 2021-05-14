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

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Board::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Board::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto boardListener = EventListenerCustom::create(EVENT_READY, CC_CALLBACK_1(GameScene::onBoardReady, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(boardListener, this);

	auto matchListener = EventListenerCustom::create(EVENT_HAS_MATCH, CC_CALLBACK_1(GameScene::onBoardMatch, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(matchListener, this);

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
		screenSize.height * 0.5f - board->getContentSize().height * 0.5f + 180);
	addChild(board, 1);

	board->generateCell();
	newGame(this);

	CCLOG("onEnter");
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* events)
{
	Vec2 touchPoint = touch->getLocation();
	CCLOG("current: [%f,%f]", touch->getLocation().x, touch->getLocation().y);
	if (isBusy || board->isBusy() || board->getBoundingBox().containsPoint(touchPoint) == false)
		return false;

	auto block = board->getBlockForPosition(touchPoint);
	if (block == nullptr || block == activeBlock)
		return true;

	if (activeBlock != nullptr)
	{
		if (board->isNeighbours(activeBlock, block))
		{
			swipeBlock(block, activeBlock);
			runAction(Sequence::create(DelayTime::create(0.3f),
				CallFunc::create(CC_CALLBACK_0(GameScene::checkForMatch, this, activeBlock, block)),
				nullptr));

			activeBlock->setActive(false);
			block->setActive(false);
			activeBlock = nullptr;
		}
		else
		{
			activeBlock->setActive(false);
			activeBlock = block;
			activeBlock->setActive(true);
		}
	}
	else
	{
		activeBlock = block;
		activeBlock->setActive(true);
	}

	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* events)
{
	if (isBusy || board->isBusy() || activeBlock == nullptr)
		return;

	Vec2 touchDist = touch->getLocation() - touch->getPreviousLocation();

	CCLOG("current: [%f,%f] \/ previous: [%f,%f]", touch->getLocation().x, touch->getLocation().y,
		touch->getPreviousLocation().x, touch->getPreviousLocation().y);

	CCLOG("dist: [%f, %f]", touchDist.x, touchDist.y);

	CCLOG("Delta: [%f, %f]", touch->getDelta().x, touch->getDelta().y);

	Block* blockToSwap = nullptr;

	//Right
	if (touchDist.x >= SWIPE_TRESHOLD && (activeBlock->boardPosition.row + 1 < MAX_ROW))
		blockToSwap = board->blocks[activeBlock->boardPosition.row + 1][activeBlock->boardPosition.col];
	//Left
	if (touchDist.x <= -SWIPE_TRESHOLD && (activeBlock->boardPosition.row > 0))
		blockToSwap = board->blocks[activeBlock->boardPosition.row - 1][activeBlock->boardPosition.col];
	//Up
	if (touchDist.y >= SWIPE_TRESHOLD && (activeBlock->boardPosition.col + 1 < MAX_COL))
		blockToSwap = board->blocks[activeBlock->boardPosition.row][activeBlock->boardPosition.col + 1];
	//Down
	if (touchDist.y <= -SWIPE_TRESHOLD && (activeBlock->boardPosition.col > 0))
		blockToSwap = board->blocks[activeBlock->boardPosition.row][activeBlock->boardPosition.col - 1];

	if (blockToSwap != nullptr)
	{
		swipeBlock(blockToSwap, activeBlock);
		runAction(Sequence::create(DelayTime::create(0.3f),
			CallFunc::create(CC_CALLBACK_0(GameScene::checkForMatch, this, activeBlock, blockToSwap)),
			nullptr));

		activeBlock->setActive(false);
		activeBlock = nullptr;
	}

}

void GameScene::swipeBlock(Block* first, Block* second)
{
	lockTouch(0.3f);
	board->swapBlock(first, second);
	first->runAction(MoveTo::create(0.3f, second->getPosition()));
	second->runAction(MoveTo::create(0.3f, first->getPosition()));
}

void GameScene::newGame(cocos2d::Ref* ref)
{
	board->removeAllBlocks();
	board->generateRandomBlock();
	availableMove = board->findAvailableMove();

	activeBlock = nullptr;

	if (availableMove.size() == 0)
		newGame(this);
}

void GameScene::checkForMatch(Block* first, Block* second)
{
	bool firstMatch = board->checkForMatch(first);
	bool secondMatch = board->checkForMatch(second);

	if (!firstMatch && !secondMatch) // 둘다 미스매치 - 원상복구
	{
		swipeBlock(first, second);
		return;
	}

	if (firstMatch)
		resolveMatchForBlock(first);

	if (secondMatch)
		resolveMatchForBlock(second);

	if (firstMatch || secondMatch)
	{
		lockTouch(0.7f);
		board->fillBlanks();

		activeBlock = nullptr;
	}

}

void GameScene::lockTouch(float time)
{
	unschedule(CC_SCHEDULE_SELECTOR(GameScene::unlockTouch));
	scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::unlockTouch), 0.5f);
	isBusy = true;
}

void GameScene::unlockTouch(float delTime)
{
	isBusy = false;
}

void GameScene::resolveMatchForBlock(Block* block)
{
	if (block == nullptr)
		return;

	std::vector<Block*> matches;

	int num_matches = board->findMatch(block, matches);
	// 점수 추가

	for (auto match : matches)
	{
		board->removeBlockAt(match->boardPosition);
	}
}

void GameScene::onBoardReady(cocos2d::EventCustom* events)
{
	availableMove = board->findAvailableMove();
	if (availableMove.size() == 0)
		newGame(this);
}

void GameScene::onBoardMatch(cocos2d::EventCustom* events)
{
	EventMatchesData* em = (EventMatchesData*)events->getUserData();
	// 점수 추가
}
