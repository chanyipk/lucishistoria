#include "PopLayer.h"
#include "MapScene.h"
#include "ElyonScene.h"

bool PopLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto info = Sprite::create("map_info.png");
	info->setAnchorPoint(Point(0.5, 0.5));
	info->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	info->setTag(INFO);
	this->addChild(info);

	auto enter = MenuItemImage::create("enter.png", "enter_push.png", CC_CALLBACK_1(PopLayer::onTouchBegan, this));
	auto close = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_1(PopLayer::onCloseTouchBegan, this));


	auto but_1 = Menu::create(enter, NULL);
	but_1->alignItemsHorizontally();
	but_1->setAnchorPoint(Point(0.5, 0.5));
	but_1->setPosition(590, 50);
	but_1->setScale(0.8);
	but_1->setTag(ENTER);
	this->addChild(but_1);

	auto but_2 = Menu::create(close, NULL);
	but_2->alignItemsHorizontally();
	but_2->setAnchorPoint(Point(0.5, 0.5));
	but_2->setPosition(950, 50);
	but_2->setScale(0.8);
	but_2->setTag(CLOSE);
	this->addChild(but_2);


	return true;
}

void PopLayer::onTouchBegan(cocos2d::Ref *sender) {

	Director::getInstance()->replaceScene(ElyonScene::createScene());
}

void PopLayer::onCloseTouchBegan(cocos2d::Ref *sender) {

	Sprite *info;
	Menu *close, *enter;

	info = (Sprite*)this->getChildByTag(INFO);
	close = (Menu*)this->getChildByTag(CLOSE);
	enter = (Menu*)this->getChildByTag(ENTER);
	this->removeChild(info);
	this->removeChild(close);
	this->removeChild(enter);
}