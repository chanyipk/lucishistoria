#include "StoreLayer.h"
#include "BuyLayer.h"
#include "ElyonScene.h"
#include "PotionLayer.h"
#include "WeaponLayer.h"
#include "suitLayer.h"
#include "dataSingleton.h"

bool ispLayer = false;
bool iswLayer = false;

Scene* StoreLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StoreLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StoreLayer::init() {

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
	
	auto exit = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(StoreLayer::closebut, this));
	auto exit_b = Menu::create(exit, NULL);
	exit_b->setPosition(Point(1800, 962));
	this->addChild(exit_b);
	
	iswLayer = true;
	auto wp = WeaponLayer::create();
	this->addChild(wp, 100, W_LAYER);

	//좌측 아이템 선택버튼   //무기
	auto weapon = MenuItemImage::create("weapon.png", "weapon.png", CC_CALLBACK_1(StoreLayer::itemSelect, this));
	auto weaponb = Menu::create(weapon, NULL);
	weaponb->setAnchorPoint(Point(0, 0));
	weaponb->setPosition(Point(250, 830));
	weapon->setTag(WEAPON);
	this->addChild(weaponb);

	//방어구
	auto shild = MenuItemImage::create("shild.png", "shild.png", CC_CALLBACK_1(StoreLayer::itemSelect, this));
	shild->setTag(SHILD);
	auto shildb = Menu::create(shild, NULL);
	shildb->setAnchorPoint(Point(0, 0));
	shildb->setPosition(Point(250, 670));
	this->addChild(shildb);


	//엑세서리
	auto acc = MenuItemImage::create("acc.png", "acc.png", CC_CALLBACK_1(StoreLayer::itemSelect, this));
	acc->setTag(ACC);
	auto accb = Menu::create(acc, NULL);
	accb->setAnchorPoint(Point(0, 0));
	accb->setPosition(Point(250, 510));
	this->addChild(accb);


	//물약
	auto potion = MenuItemImage::create("potion.png", "potion.png", CC_CALLBACK_1(StoreLayer::itemSelect, this));
	potion->setTag(POTION);
	auto potionb = Menu::create(potion, NULL);
	potionb->setAnchorPoint(Point(0, 0));
	potionb->setPosition(Point(250, 350));
	this->addChild(potionb);


	return true;
}

void StoreLayer::closebut(Ref *sender) {
	dataSingleton::getInstance()->open = false;
	this->removeAllChildren();
}



void StoreLayer::itemSelect(cocos2d::Ref* sender) {

	auto but = (MenuItem*)sender;
	this->removeChildByTag(P_LAYER,1);
	this->removeChildByTag(W_LAYER, 1);
	this->removeChildByTag(S_LAYER, 1);

	if (but->getTag() == WEAPON) {

			auto wp = WeaponLayer::create();
			this->addChild(wp, 100, W_LAYER);

	}
	else if (but->getTag() == SHILD) {

			auto su = suitLayer::create();
			this->addChild(su, 100, S_LAYER);

	}
	else if (but->getTag() == POTION) {
		auto player = PotionLayer::create();
		this->addChild(player, 200, P_LAYER);
	}
}

