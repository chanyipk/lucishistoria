#include "NoticeLayer.h"
#include "dataSingleton.h"


bool NoticeLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto info = Sprite::create("standard.png");
	info->setAnchorPoint(Point(0.5, 0.5));
	info->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	info->setTag(NOTICE);
	this->addChild(info);


	auto close = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(NoticeLayer::onCloseTouchBegan, this));


	auto but_1 = Menu::create(close, NULL);
	but_1->alignItemsVertically();
	but_1->setAnchorPoint(Point(0, 0));
	but_1->setPosition(Point(1430,1000));
	but_1->setTag(CLOSE);
	this->addChild(but_1);


	return true;
}


void NoticeLayer::onCloseTouchBegan(cocos2d::Ref *sender) {
	
	Sprite *notice;
	Menu *close;

	notice = (Sprite*)this->getChildByTag(NOTICE);
	close = (Menu*)this->getChildByTag(CLOSE);
	this->removeChild(notice);
	this->removeChild(close);
	dataSingleton::getInstance()->enable = true;

}