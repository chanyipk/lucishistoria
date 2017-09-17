#include "MainLayer.h"
#include "MapScene.h"
#include "dataSingleton.h"

bool MainLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	initBG();
	dataSingleton::getInstance()->touch = false;

	auto info = Sprite::create("startwin.png");
	info->setAnchorPoint(Point(0.5, 0.5));
	info->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height/2+60));
	info->setTag(WIN);
	info->setScale(0.9);
	this->addChild(info);



	auto start = MenuItemImage::create("start.png", "start_push.png", CC_CALLBACK_1(MainLayer::onStartTouchBegan, this));
	auto close = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_1(MainLayer::onCloseTouchBegan, this));

	auto startbut = Menu::create(start,NULL);
	startbut->alignItemsHorizontally();
	startbut->setAnchorPoint(Point(0.5, 0.5));
	startbut->setPosition(Point(590,10));
	startbut->setTag(START);
	startbut->setScale(0.8);
	this->addChild(startbut);

	auto closebut = Menu::create(close, NULL);
	closebut->alignItemsHorizontally();
	closebut->setAnchorPoint(Point(0.5, 0.5));
	closebut->setPosition(Point(950,10));
	closebut->setTag(CLOSE);
	closebut->setScale(0.8);
	this->addChild(closebut);


	return true;
}

void MainLayer::onStartTouchBegan(cocos2d::Ref *sender) {

	Director::getInstance()->replaceScene(MapScene::createScene());
}

void MainLayer::onCloseTouchBegan(cocos2d::Ref *sender) {


	Sprite *win, *backg;
	Menu *startbut,*closebut;
	
	win = (Sprite*)this->getChildByTag(WIN);
	backg = (Sprite*)this->getChildByTag(BACKG);
	startbut = (Menu*)this->getChildByTag(START);
	closebut = (Menu*)this->getChildByTag(CLOSE);

	dataSingleton::getInstance()->touch = true;
	this->removeChild(win);
	this->removeChild(backg);
	this->removeChild(startbut);
	this->removeChild(closebut);

}

void MainLayer::initBG() {

	// 레이어 배경이 켜졌을 때 이 레이어 뒤에 있는 버튼들은 아무것도 안눌려야 함
	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	background->setTag(BACKG);
	this->addChild(background);
}