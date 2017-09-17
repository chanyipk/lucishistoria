#include "GameScene.h"
#include "DtopLayer.h"
#include "dataSingleton.h"
#include "userLayer.h"
#include "ElyonScene.h"
#include "Jdata.h"
#include "SimpleAudioEngine.h"

Jdata* pG;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool GameScene::init() {
	if (!Layer::init()) {
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("My Friend.mp3", true);
	dataSingleton::getInstance()->elyonScene = false;
	initBG();

	auto DtopLayer = DtopLayer::create();
	this->addChild(DtopLayer);

/*	auto MonsterLayer= MonsterLayer::create();
	this->addChild(MonsterLayer);
*/
	



	return true;

	

}
void GameScene::initBG() {
	auto bgimg = Sprite::create("b1.png", Rect(0, 0, 1920, 1080));
	bgimg->setAnchorPoint(Point::ZERO);
	bgimg->setPosition(Point::ZERO);
	this->addChild(bgimg);
}