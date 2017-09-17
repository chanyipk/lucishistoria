#include "UpgradeLayer.h"
#include "BuyLayer.h"
#include "ElyonScene.h"

bool UpgradeLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background);

	auto store1 = Sprite::create("store1.png");
	store1->setAnchorPoint(Point(0, 0.5));
	store1->setPosition(Point(Director::getInstance()->
		getWinSize().width / 4, Director::getInstance()->
		getWinSize().height / 9 * 5 - 30));
	this->addChild(store1);

	auto exit = Sprite::create("exit.png");
	exit->setAnchorPoint(Point(0, 0));
	exit->setPosition(Point(1800, 930));
	exit->setScale(0.7);
	this->addChild(exit);

	auto buy = Sprite::create("buy.png");
	buy->setAnchorPoint(Point(0.5, 0.5));
	buy->setPosition(Point(Director::getInstance()->getWinSize().width / 2, 80));
	this->addChild(buy);
	//파트별 아이템
	//1. 무기
	auto item1 = MenuItemImage::create("item.png", "item.png", CC_CALLBACK_1(UpgradeLayer::buyLayer, this));
	auto itemb1 = Menu::create(item1, NULL);
	itemb1->setAnchorPoint(Point(0, 0));
	itemb1->setPosition(Point(1000, 830));
	itemb1->setTag(ITEM1);
	this->addChild(itemb1);
	//2.방아구
	auto item2 = MenuItemImage::create("item.png", "item.png", CC_CALLBACK_1(UpgradeLayer::buyLayer, this));
	auto itemb2 = Menu::create(item2, NULL);
	itemb2->setAnchorPoint(Point(0, 0));
	itemb2->setPosition(Point(1000, 730));
	itemb2->setTag(ITEM2);
	itemb2->setVisible(false);
	this->addChild(itemb2);
	//3.악세서리
	auto item3 = MenuItemImage::create("item.png", "item.png", CC_CALLBACK_1(UpgradeLayer::buyLayer, this));
	auto itemb3 = Menu::create(item3, NULL);
	itemb3->setAnchorPoint(Point(0, 0));
	itemb3->setPosition(Point(1000, 630));
	itemb3->setTag(ITEM3);
	itemb3->setVisible(false);
	this->addChild(itemb3);
	//4.물약
	auto item4 = MenuItemImage::create("item.png", "item.png", CC_CALLBACK_1(UpgradeLayer::buyLayer, this));
	auto itemb4 = Menu::create(item4, NULL);
	itemb4->setAnchorPoint(Point(0, 0));
	itemb4->setPosition(Point(1000, 530));
	itemb4->setTag(ITEM4);
	itemb4->setVisible(false);
	this->addChild(itemb4);

	//좌측 아이템 선택버튼
	auto weapon = MenuItemImage::create("weapon.png", "weapon.png", CC_CALLBACK_1(UpgradeLayer::itemSelect, this));
	auto weaponb = Menu::create(weapon, NULL);
	weaponb->setAnchorPoint(Point(0, 0));
	weaponb->setPosition(Point(250, 830));
	weapon->setTag(WEAPON);
	this->addChild(weaponb);

	auto shild = MenuItemImage::create("shild.png", "shild.png", CC_CALLBACK_1(UpgradeLayer::itemSelect, this));
	shild->setTag(SHILD);
	auto shildb = Menu::create(shild, NULL);
	shildb->setAnchorPoint(Point(0, 0));
	shildb->setPosition(Point(250, 670));
	this->addChild(shildb);

	auto acc = MenuItemImage::create("acc.png", "acc.png", CC_CALLBACK_1(UpgradeLayer::itemSelect, this));
	acc->setTag(ACC);
	auto accb = Menu::create(acc, NULL);
	accb->setAnchorPoint(Point(0, 0));
	accb->setPosition(Point(250, 510));
	this->addChild(accb);

	auto potion = MenuItemImage::create("potion.png", "potion.png", CC_CALLBACK_1(UpgradeLayer::itemSelect, this));
	potion->setTag(POTION);
	auto potionb = Menu::create(potion, NULL);
	potionb->setAnchorPoint(Point(0, 0));
	potionb->setPosition(Point(250, 350));
	this->addChild(potionb);

	EventDispatcher * dispatcher2 = Director::getInstance()->getEventDispatcher();

	//구역 외의 배경 이미지를 선택할 경우 발생되는 이벤트의 리스너를 생성합니다.
	//리스너 함수의 이름은 onPositionTouchBegan입니다.
	auto closeListener = EventListenerTouchOneByOne::create();
	closeListener->setSwallowTouches(true);
	closeListener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onCloseTouchBegan, this);
	dispatcher2->addEventListenerWithSceneGraphPriority(closeListener, exit);

	auto buyListener = EventListenerTouchOneByOne::create();
	buyListener->setSwallowTouches(true);
	buyListener->onTouchBegan = CC_CALLBACK_2(UpgradeLayer::onSprTouchBegan, this);
	dispatcher2->addEventListenerWithSceneGraphPriority(buyListener, buy);

	return true;
}


bool UpgradeLayer::onCloseTouchBegan(Touch * touch, Event * event) {

	//터치한 객체를 타겟에 저장합니다.
	auto target = (Sprite *)event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);

	if (rect.containsPoint(pos)) {


		this->removeFromParentAndCleanup(target);
		return true;
	}
	return false;
}

bool UpgradeLayer::onSprTouchBegan(Touch * touch, Event * event) {

	//터치한 객체를 타겟에 저장합니다.
	auto target = (Sprite *)event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);

	if (rect.containsPoint(pos)) {

		auto buylayer = BuyLayer::create();
		this->addChild(buylayer);

		return true;
	}
	return false;
}

void UpgradeLayer::itemSelect(cocos2d::Ref* sender) {

	auto but = (MenuItem*)sender;
	Menu *item_1, *item_2, *item_3, *item_4;

	item_1 = (Menu*)this->getChildByTag(ITEM1);
	item_2 = (Menu*)this->getChildByTag(ITEM2);
	item_3 = (Menu*)this->getChildByTag(ITEM3);
	item_4 = (Menu*)this->getChildByTag(ITEM4);
	//	Sprite *item_1, *item_2;

	switch (but->getTag()) {
	case WEAPON:
	{
		item_1->setVisible(true);
		item_2->setVisible(false);
		item_3->setVisible(false);
		item_4->setVisible(false);
		break;
	}
	case SHILD:
	{
		item_1->setVisible(false);
		item_2->setVisible(true);
		item_3->setVisible(false);
		item_4->setVisible(false);
		break;
	}
	case ACC:
	{
		item_1->setVisible(false);
		item_2->setVisible(false);
		item_3->setVisible(true);
		item_4->setVisible(false);
		break;
	}
	case POTION:
	{
		item_1->setVisible(false);
		item_2->setVisible(false);
		item_3->setVisible(false);
		item_4->setVisible(true);
		break;
	}




	}
}

void UpgradeLayer::buyLayer(cocos2d::Ref* sender) {

}