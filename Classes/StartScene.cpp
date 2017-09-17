#include "StartScene.h"
#include "MainScene.h"
#include "Jdata.h"
#include "SimpleAudioEngine.h"

Jdata * start_pL;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first

	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Fresh Dew.mp3", true);

	auto spr = MenuItemImage::create("first.png", "first.png", CC_CALLBACK_1(StartScene::changeScene, this));
	auto startspr = Menu::create(spr, NULL);
	startspr->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	startspr->setOpacity(0);
	auto action_0 = FadeIn::create(1);
	startspr->runAction(action_0);
	this->addChild(startspr);

	auto logo = Sprite::create("logo.png");
	logo->setAnchorPoint(Point(0, 1));
	logo->setPosition(Point(0, 1080));
	this->addChild(logo);

	auto touch = Sprite::create("touchscreen.png");
	touch->setAnchorPoint(Point(0.5, 0.5));
	touch->setPosition(Point(960, 150));
	this->addChild(touch);

	auto action_1 = FadeOut::create(1.0);
	auto action_2 = FadeIn::create(1.0);
	auto action_3 = Sequence::create(action_1, action_2, NULL);
	auto action_4 = RepeatForever::create(action_3);
	touch->runAction(action_4);

	return true;
}


void StartScene::changeScene(Ref *sender)
{
		auto scene2 = TransitionFade::create(3.0, MainScene::createScene());
		Director::getInstance()->replaceScene(scene2);
}