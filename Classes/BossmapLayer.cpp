#include "DungeonmapScene.h"
#include "BossmapLayer.h"
#include "GameScene2.h"
#include "dataSingleton.h"

bool BossmapLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto info = Sprite::create("boss_info.png");
	info->setAnchorPoint(Point(0.5, 0.5));
	info->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	info->setTag(INFO);
	this->addChild(info);


	auto enter = MenuItemImage::create("enter.png", "enter_push.png", CC_CALLBACK_1(BossmapLayer::onTouchBegan, this));
	auto close = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_1(BossmapLayer::onCloseTouchBegan, this));

	auto but_1 = Menu::create(enter, NULL);
	but_1->alignItemsHorizontally();
	but_1->setAnchorPoint(Point(0, 0));
	but_1->setPosition(Point(785, 150));
	but_1->setScale(0.8);
	but_1->setTag(ENTER);
	this->addChild(but_1);

	auto but_2 = Menu::create(close, NULL);
	but_2->alignItemsHorizontally();
	but_2->setAnchorPoint(Point(0, 0));
	but_2->setPosition(1125, 150);
	but_2->setScale(0.8);
	but_2->setTag(CLOSE);
	this->addChild(but_2);



	return true;
}

void BossmapLayer::onTouchBegan(cocos2d::Ref *sender) {

	Director::getInstance()->replaceScene(GameScene2::createScene());
}

void BossmapLayer::onCloseTouchBegan(cocos2d::Ref *sender) {

	Sprite *info;
	Menu *close, *enter;

	info = (Sprite*)this->getChildByTag(INFO);
	close = (Menu*)this->getChildByTag(CLOSE);
	enter = (Menu*)this->getChildByTag(ENTER);
	this->removeChild(info);
	this->removeChild(close);
	this->removeChild(enter);
}

