#include "ElyonScene.h"
#include "UserLayer.h"
#include "MapScene.h"
#include "TopLayer.h"
#include "SimpleAudioEngine.h"
#include "dataSingleton.h"

Scene* ElyonScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ElyonScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ElyonScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	initBG();//µÞ¹è°æ
	dataSingleton::getInstance()->elyonScene = true;
	dataSingleton::getInstance()->playerDead = false;
	auto TopLayer = TopLayer::create();//Ä³¸¯ÅÍ, mpc, ¶¥, »óÁ¡
	this->addChild(TopLayer);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Wintry Town.mp3", true);

	auto map = MenuItemImage::create("mapbut.png", "mapbut_push.png",
		CC_CALLBACK_1(ElyonScene::changeScene, this));
	
	auto map1 = Menu::create(map, NULL);
	map1->setAnchorPoint(Point::ZERO);
	map1->setPosition(Point(55, 1030));
	map1->setScale(0.7);
	this->addChild(map1);

	
	return true;
}

void ElyonScene::initBG()
{

	auto bgimg = Sprite::create("elyon.png", Rect(0, 0, 1920, 1080));
	bgimg->setAnchorPoint(Point::ZERO);
	bgimg->setPosition(Point::ZERO);
	this->addChild(bgimg);
}

void ElyonScene::changeScene(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(MapScene::createScene());
}