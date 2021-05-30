#include "StartMenuScene.h"
#include "GameScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* StartMenuScene::createScene()
{
	return StartMenuScene::create();
}

bool StartMenuScene::init()
{
	if (!Scene::init())
		return false;


	Size screenSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	Sprite* background = Sprite::create("Images/UI/Background.png");
	background->setPosition(origin.x + screenSize.width / 2, origin.y + screenSize.height / 2);
	addChild(background, 0);

	Sprite* Menu_title = Sprite::create("Images/UI/GameTitle.png");
	Menu_title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	Menu_title->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height + 120));
	addChild(Menu_title, 1);


	float rX = screenSize.width / background->getContentSize().width;
	float rY = screenSize.height / background->getContentSize().height;

	background->setScaleX(rX);
	background->setScaleY(rY);

	this->schedule(schedule_selector(StartMenuScene::tick));


	return true;
}

void StartMenuScene::tick(float dt)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Continue = CCSprite::create("Images/continue.png");
	Continue->setPosition(Vec2(240, 160));
	Continue->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->addChild(Continue);

	CCFiniteTimeAction* ContinueAct = CCSequence::create(CCFadeOut::create(1.0f), CCFadeIn::create(1.0f), nullptr);
	CCAction* rep = CCRepeatForever::create((CCActionInterval*)ContinueAct);
	Continue->runAction(rep);
}

void StartMenuScene::ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent)
{
	CCScene* pScene = MenuScene:: create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressRadialCW::create(0.5f, pScene));//반시계방향으로 방사형 전환
}