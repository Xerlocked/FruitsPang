#include "Manual.h"
#include "GameScene.h"
#include "DataManager.h"

Manual* Manual::create()
{
	Manual* ret = nullptr;
	try
	{
		ret = new Manual();
		if (!ret->init())
			throw std::bad_alloc();
		ret->autorelease();
		return ret;
	}
	catch (...)
	{
		CC_SAFE_DELETE(ret);
		throw;
	}
}

bool Manual::init()
{
	visibleSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);
	this->addChild(fadeBack);
	fadeBack->runAction(FadeTo::create(0.5f, 100));

	explainLabel = Label::createWithTTF("중앙 타일을 기준으로 점대칭이 됩니다.", "fonts/Maplestory-Light.ttf", 56);
	explainLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	explainLabel->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
	explainLabel->setTextColor(Color4B::WHITE);
	this->addChild(explainLabel, 99);

	explainTile = Sprite::create("Images/actionTile.png");
	explainTile->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f - 105));
	this->addChild(explainTile, 99);

	okButton = ui::Button::create("Images/GreenSquareButton.png");
	okButton->setTag(0);
	okButton->setTitleText("네. 알겠습니다");
	okButton->setTitleFontName("fonts/Maplestory-Light.ttf");
	okButton->setTitleFontSize(36);
	okButton->setPosition(Vec2(visibleSize.width * 0.5f, 130));
	okButton->addClickEventListener(CC_CALLBACK_1(Manual::onClickButton, this));
	okButton->setVisible(false);
	this->addChild(okButton, 99);


	auto leftArrow = ui::Button::create("Images/leftArrow.png");
	leftArrow->setTag(1);
	leftArrow->setPosition(Vec2(64, visibleSize.height * 0.5f));
	leftArrow->addClickEventListener(CC_CALLBACK_1(Manual::onClickButton, this));
	this->addChild(leftArrow, 99);

	auto rightArrow = ui::Button::create("Images/rightArrow.png");
	rightArrow->setTag(2);
	rightArrow->setPosition(Vec2(visibleSize.width - 64, visibleSize.height * 0.5f));
	rightArrow->addClickEventListener(CC_CALLBACK_1(Manual::onClickButton, this));
	this->addChild(rightArrow, 99);

	exNum = 0;

	return true;
}

void Manual::onEnter()
{
	Layer::onEnter();
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}

bool Manual::onTouchBegan(Touch* touch, Event* events)
{
	return true;
}

void Manual::onClickButton(Ref* object)
{
	const int getTag = ((Node*)object)->getTag();

	DataManager::getInstance()->PlaySoundW(SOUND_SELECT_EFFECT);

	switch (getTag)
	{
	case 0:
	{
		auto parent = (GameScene*)this->getParent();
		setTouchEnabled(false);
		parent->ResumeScene();
		this->removeAllChildrenWithCleanup(true);
	}
	break;

	case 1:
	{
		if (exNum <= 0)
			return;
		exNum--;
		changeExplain();
	}
	break;

	case 2:
	{
		if (exNum >= 2)
			return;

		exNum++;
		changeExplain();
	}
	break;

	default:
		break;
	}
}

void Manual::changeExplain()
{
	switch (exNum)
	{
	case 0:
	{
		explainLabel->setString("중앙 타일을 기준으로 점대칭이 됩니다");
		explainTile->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f - 105));
		okButton->setVisible(false);
	}
	break;

	case 1:
	{
		explainLabel->setString("만약, 해당 위치의 과일을 움직이고 싶다면");
		explainTile->setPosition(Vec2(visibleSize.width * 0.2f + 30, visibleSize.height * 0.6f));
		okButton->setVisible(false);
	}
	break;

	case 2:
	{
		explainLabel->setString("지금 표시된 과일을 움직이시면 됩니다");
		explainTile->setPosition(Vec2(visibleSize.width * 0.8f - 30, visibleSize.height * 0.3f - 17));
		okButton->setVisible(true);
	}
	break;

	default:
		break;
	}
}
