
#include "MapScene.h"
#include "PrologScene2.h"



Scene* PrologScene2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PrologScene2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PrologScene2::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto pro1 = Sprite::create("pro1.png");
	pro1->setAnchorPoint(Point(0.5, 0.5));
	pro1->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	this->addChild(pro1);

	auto dt = DelayTime::create(8.0);
	auto prolog = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(PrologScene2::changeScene, this)), NULL);
	this->runAction(prolog);

	auto pro1_1 = Sprite::create("pro1_1.png");
	pro1_1->setOpacity(0.0);
	pro1_1->setAnchorPoint(Point(0.5, 0.5));
	pro1_1->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	this->addChild(pro1_1);
	auto fade_1 = FadeIn::create(4.0f);
	auto move_1 = MoveBy::create(5, Point(100, 0));
	auto spaw_1 = Spawn::create(fade_1, move_1, NULL);
	pro1_1->runAction(spaw_1);

	auto pro1_2 = Sprite::create("pro1_2.png");
	pro1_2->setOpacity(0.0);
	pro1_2->setAnchorPoint(Point(0.5, 0.5));
	pro1_2->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	this->addChild(pro1_2);
	auto fade_2 = FadeIn::create(4.0f);
	auto dt_2 = DelayTime::create(3.0);
	auto move_2 = MoveBy::create(5, Point(-100, 0));
	auto spaw_2 = Spawn::create(fade_2, move_2, NULL);
	auto seq_2 = Sequence::create(dt_2, spaw_2, NULL);
	pro1_2->runAction(seq_2);

	auto skip_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(PrologScene2::skipScene, this));
	auto skip = Menu::create(skip_but, NULL);
	skip->alignItemsVertically();
	skip->setAnchorPoint(Point(0.5, 0.5));
	skip->setPosition(Point(1200, -300));
	skip->setScale(0.35);
	pro1->addChild(skip);



	return true;
}

void PrologScene2::changeScene(Ref* pSender)
{
	auto scene = TransitionFade::create(3.0, MapScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void PrologScene2::skipScene(Ref* Sender)
{
	this->stopAllActions();
	Director::getInstance()->replaceScene(MapScene::createScene());
}