#include "MapScene.h"
#include "PrologScene1.h"
#include "PrologScene2.h"
#include "Jdata.h"

Jdata* pP;

Scene* PrologScene1::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PrologScene1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PrologScene1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	std::string prol_uname = pP->jjgetuserName(0);
	pP->jjsetBool(true, "pro", prol_uname);
	auto pro0 = Sprite::create("pro0.png");
	pro0->setAnchorPoint(Point(0.5, 0.5));
	pro0->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	this->addChild(pro0);

	auto dt = DelayTime::create(8.0);
	auto prolog = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(PrologScene1::changeScene, this)), NULL);
	this->runAction(prolog);

	auto skip_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(PrologScene1::skipScene, this));
	auto skip = Menu::create(skip_but, NULL);
	skip->alignItemsVertically();
	skip->setAnchorPoint(Point(0.5, 0.5));
	skip->setPosition(Point(1200, -300));
	skip->setScale(0.35);
	pro0->addChild(skip);

	return true;
}


void PrologScene1::changeScene(Ref* Sender)
{
	auto scene = TransitionFade::create(3.0, PrologScene2::createScene());
	Director::getInstance()->replaceScene(scene);
}
void PrologScene1::skipScene(Ref* Sender)
{
	this->stopAllActions();
	Director::getInstance()->replaceScene(MapScene::createScene());
}