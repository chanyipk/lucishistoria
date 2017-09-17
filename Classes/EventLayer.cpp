#include "EventLayer.h"
#include "dataSingleton.h"


bool EventLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	auto info = Sprite::create("standard.png");
	info->setAnchorPoint(Point(0.5, 0.5));
	info->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	info->setTag(EVENT);
	this->addChild(info);

	auto close = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(EventLayer::onCloseTouchBegan, this));
	auto but_1 = Menu::create(close, NULL);
	but_1->alignItemsVertically();
	but_1->setAnchorPoint(Point(0, 0));
	but_1->setPosition(Point(1430, 1000));
	but_1->setTag(CLOSE);
	this->addChild(but_1);


	return true;
}


void EventLayer::onCloseTouchBegan(cocos2d::Ref *sender) {


	Sprite *ev;
	Menu *close;

	ev = (Sprite*)this->getChildByTag(EVENT);
	close = (Menu*)this->getChildByTag(CLOSE);
	this->removeChild(ev);
	this->removeChild(close);
	dataSingleton::getInstance()->enable = true;
}