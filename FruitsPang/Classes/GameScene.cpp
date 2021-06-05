#include "GameScene.h"
#include "ResultPopup.h"
#include "GameSettingPopup.h"
#include "DataManager.h"
#include "AudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace experimental;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	GameScene* gameScene = nullptr;
	try
	{
		gameScene = new GameScene();
		if (!gameScene->init())
			throw std::bad_alloc();
		gameScene->autorelease();
		scene->addChild(gameScene);

		return scene;
	}
	catch (...)
	{
		CC_SAFE_DELETE(gameScene);
		throw;
	}
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	CCLOG("init");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Assets/texture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Assets/UI.plist");
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

	/// Background - Size : 1440x2280
	auto background = Sprite::create("Images/GameSceneBackground.png");
	background->setPosition(origin.x + screenSize.width / 2, origin.y + screenSize.height / 2);
	
	float rX = screenSize.width / background->getContentSize().width;
	float rY = screenSize.height / background->getContentSize().height;

	background->setScaleX(rX);
	background->setScaleY(rY);
	addChild(background, 0);

	/// Title - Fruits Pang 
	auto ui_title = Sprite::createWithSpriteFrameName("GameTitle.png");
	ui_title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_title->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height - 170));
	addChild(ui_title, 1);

	/// Score - Maplestory-light.ttf
	ui_score = Label::createWithTTF("0", "fonts/Vagron.ttf", 65);
	ui_score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_score->setPosition(Vec2(screenSize.width * 0.5f, 1570));
	ui_score->enableOutline(Color4B::BLACK, 2);
	ui_score->enableShadow();
	ui_score->setTextColor(Color4B::WHITE);
	addChild(ui_score, 1);

	/// whiteRabbit - sprite
	auto ui_wRabbit = Sprite::createWithSpriteFrameName("whiteRabbit.png");
	ui_wRabbit->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_wRabbit->setPosition(Vec2(110, 1680));
	addChild(ui_wRabbit, 1);


	/// pinkRabbit - sprite
	auto ui_pRabbit = Sprite::createWithSpriteFrameName("pinkRabbit.png");
	ui_pRabbit->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_pRabbit->setPosition(Vec2(970, 1680));
	addChild(ui_pRabbit, 1);

	/// Progressbar - Background
	auto ui_timer_bg = Sprite::createWithSpriteFrameName("Progressbar_bg.png");
	ui_timer_bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_timer_bg->setPosition(Vec2(screenSize.width * 0.5f, 40));

	ui_timer_label = Label::createWithTTF("60", "fonts/Jellee-Roman.ttf", 56);
	ui_timer_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_timer_label->setPosition(Vec2(ui_timer_bg->getContentSize().width * 0.5f, ui_timer_bg->getContentSize().height * 0.5f));
	ui_timer_label->setTextColor(Color4B::WHITE);
	ui_timer_label->setLocalZOrder(99);
	ui_timer_bg->addChild(ui_timer_label);

	addChild(ui_timer_bg, 1);

	/// Progressbar - Timer
	auto ui_timer_bar = Sprite::createWithSpriteFrameName("Progressbar.png");
	ui_timer = ProgressTimer::create(ui_timer_bar);
	//ui_timer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ui_timer->setPosition(Vec2(ui_timer_bg->getContentSize().width * 0.5f, ui_timer_bg->getContentSize().height * 0.5f));
	ui_timer->setType(ProgressTimerType::BAR);
	ui_timer->setBarChangeRate(Vec2(1, 0));
	ui_timer->setMidpoint(Vec2(0, 0.5f));
	ui_timer->setPercentage(100.0f);
	ui_timer_bg->addChild(ui_timer);

	auto settingButton = ui::Button::create("SettingButton.png","","",ui::Widget::TextureResType::PLIST);
	settingButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	settingButton->setPosition(Vec2(screenSize.width - 30, screenSize.height - 30));
	settingButton->addClickEventListener(CC_CALLBACK_0(GameScene::OpenSettingPopup, this));
	addChild(settingButton,1);

	/// Board - 9x9
	board = Board::createBoard(MAX_ROW, MAX_COL);
	board->setPosition(screenSize.width * 0.5f - board->getContentSize().width * 0.5f,
		screenSize.height * 0.5f - board->getContentSize().height * 0.6f);
	addChild(board, 1);

	board->generateCell();
	newGame(this);

	setTimer();

	CCLOG("onEnter");
	CCLOG("%d", (int)DataManager::getInstance()->getPlayMode());
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* events)
{
	Vec2 touchPoint = touch->getLocation();

	CCLOG("%d", DataManager::getInstance()->getPlayMode());
	
	if (DataManager::getInstance()->getPlayMode() == PLAYMODE::REVERSE)
	{
		touchPoint.x = 1100 - touchPoint.x;
		touchPoint.y = 1700 - touchPoint.y;
	}

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
	DataManager::getInstance()->PlaySoundW(SOUND_SWAP);
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

void GameScene::replayGame()
{
	newGame(this);
	currentScore = 0;
	ui_score->setString(std::to_string(0));
	isBusy = false;

	setTimer();
}

void GameScene::checkForMatch(Block* first, Block* second)
{
	bool firstMatch = board->checkForMatch(first);
	bool secondMatch = board->checkForMatch(second);

	if (!firstMatch && !secondMatch) // 둘다 미스매치 - 원상복구
	{
		swipeBlock(first, second);
		DataManager::getInstance()->PlaySoundW(SOUND_SWAP_ERROR);
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

	addScore(num_matches * 100);

	for (auto match : matches)
	{
		board->removeBlockAt(match->boardPosition);
		DataManager::getInstance()->PlaySoundW(SOUND_REMOVE_BLOCK);
	}
}

void GameScene::addScore(int score)
{
	auto risingScore = ActionFloat::create(1.5f, currentScore, currentScore + score, [&](int value)
		{
			util_add_comma_to_num(std::to_string(value).c_str(), buf, 1024);
			ui_score->setString(buf);
		});
	runAction(risingScore);
	currentScore += score;
}

void GameScene::onBlink(float t)
{
	if (isFade)
	{
		EventCustom ec(EVENT_FADE_IN);
		_eventDispatcher->dispatchEvent(&ec);
		isFade = false;
	}
	else
	{

		EventCustom ec(EVENT_FADE_OUT);
		_eventDispatcher->dispatchEvent(&ec);
		isFade = true;
	}
}

void GameScene::setTimer() /// 타이머 설정
{
	_RemainTime = 60.0f;

	/// 레디, 고 액션 추가

	DataManager::getInstance()->PlayMusic(102,SOUND_IN_GAME_MUSIC, true);

	ui_timer->runAction(ProgressFromTo::create(_RemainTime, 100, 0));

	schedule(schedule_selector(GameScene::updateTimer));

	if (DataManager::getInstance()->getPlayMode() == PLAYMODE::BLINK)
		schedule(schedule_selector(GameScene::onBlink), 5.0f);

}

void GameScene::updateTimer(float t)
{
	_RemainTime -= t;

	if (_RemainTime < 0 && !board->isBusy())
	{
		isBusy = true;
		DataManager::getInstance()->StopMusic();
		DataManager::getInstance()->PlaySoundW(SOUND_TIME_OVER);
		_RemainTime = 0;
		unschedule(schedule_selector(GameScene::updateTimer));
		ui_timer_label->setString("0");

		if (DataManager::getInstance()->getPlayMode() == PLAYMODE::BLINK)
			unschedule(schedule_selector(GameScene::onBlink));

		auto Seq = Sequence::create(DelayTime::create(2.2), CallFunc::create([&]() {
			if (currentScore > DataManager::getInstance()->getBestScorePlayMode())
				DataManager::getInstance()->setBestScore(currentScore);

			ResultPopup* resultPopup = ResultPopup::create(currentScore);
			this->addChild(resultPopup, 10);

			DataManager::getInstance()->PlaySoundW(SOUND_SHOW_RECORD);
			}), NULL);

		this->runAction(Seq);
	}
	else if(_RemainTime >= 0)
	{
		char str[10];
		snprintf(str, sizeof(str), "%2.0f", _RemainTime);
		ui_timer_label->setString(str);
	}
}

void GameScene::PauseScene()
{
	ui_timer->stopAllActions();
	unschedule(schedule_selector(GameScene::updateTimer));
	DataManager::getInstance()->PauseMusic();
}

void GameScene::ResumeScene()
{
	this->resume();
	DataManager::getInstance()->ResumeMusic();
	ui_timer->runAction(ProgressFromTo::create(_RemainTime, ui_timer->getPercentage(), 0));
	schedule(schedule_selector(GameScene::updateTimer));
}

void GameScene::OpenSettingPopup()
{
	PauseScene();
	GameSettingPopup* pop = GameSettingPopup::create();
	DataManager::getInstance()->PlaySoundW(SOUND_SELECT_EFFECT);
	this->addChild(pop, 10);
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
	addScore(em->matches);
	DataManager::getInstance()->PlaySoundW(SOUND_REMOVE_BLOCK_2);
}
