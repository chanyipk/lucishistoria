#include "StoreLayer.h"
#include "ElyonScene.h"
#include "BuyLayer.h"
#include "Jdata.h"
#include "dataSingleton.h"
#include "StoreLayer.h"
#include "PotionLayer.h"

int hnum;
int arrayorder;
Jdata* buypL;
int result;
int userCash;
int itemPrice;

Scene* BuyLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BuyLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool BuyLayer::init() {

	std::string buy_uname = dataSingleton::getInstance()->user;

	if (!Layer::init()) {
		return false;
	}

	buypL = dynamic_cast<Jdata*>(getParent());


	result = 0;
	userCash = dataSingleton::getInstance()->userMoney;
	itemPrice = dataSingleton::getInstance()->price;

	if (userCash >= itemPrice && itemPrice != 0) {
		result = userCash - itemPrice;
		dataSingleton::getInstance()->userMoney = result;
		

		hnum = dataSingleton::getInstance()->holdingnum;
		arrayorder = dataSingleton::getInstance()->cashtag;

		/* 포션만 구매가능한 원본 코드
		buypL->jjsetInt(result, "money", buy_uname);
		hnum = hnum+ buypL->jjgetpArray("holding", buy_uname, arrayorder);
		buypL->jjsetpArray("holding",buy_uname,hnum, arrayorder);
		*/

		int keyid = dataSingleton::getInstance()->itemkeyid;
		buypL->jjsetInt(result, "money", buy_uname);

		if (arrayorder == 0) {//무기를 구매했다는 것
			if (keyid == 0) {
				for (int i = 0; i < 4;) {
					auto id1 = buypL->jjgetAry("keyid", "userweapon", buy_uname, i);
					if (id1 == keyid) {
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else if (id1 == 999) {
						buypL->jjsetAry("keyid", "userweapon", buy_uname, keyid, i);
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else i++;
				}
			}
			else if (keyid == 1) {
				for (int i = 0; i < 4;) {
					auto id1 = buypL->jjgetAry("keyid", "userweapon", buy_uname, i);
					if (id1 == keyid) {
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else if (id1 == 999) {
						buypL->jjsetAry("keyid", "userweapon", buy_uname, keyid, i);
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else i++;
				}
			}
		}
		else if (arrayorder == 1) {//포션을 구매했다는 것
			if (keyid == 0) {
				for (int i = 0; i < 2;) {
					auto id1 = buypL->jjgetAry("keyid", "userpotion", buy_uname, i);
					if (id1 == keyid) {
						hnum = hnum + buypL->jjgetAry("holding", "userpotion", buy_uname, i);
						buypL->jjsetAry("holding", "userpotion", buy_uname, hnum, i);
						break;
					}
					else if (id1 == 999) {
						buypL->jjsetAry("keyid", "userpotion", buy_uname, keyid, i);
						hnum = hnum + buypL->jjgetAry("holding", "userpotion", buy_uname, i);
						buypL->jjsetAry("holding", "userpotion", buy_uname, hnum, i);
						break;
					}
					else i++;
				}
			}
			else if (keyid == 1) {
				for (int i = 0; i < 2;) {
					auto id1 = buypL->jjgetAry("keyid", "userpotion", buy_uname, i);
					if (id1 == keyid) {
						hnum = hnum + buypL->jjgetAry("holding", "userpotion", buy_uname, i);
						buypL->jjsetAry("holding", "userpotion", buy_uname, hnum, i);
						break;
					}
					else if (id1 == 999) {
						buypL->jjsetAry("keyid", "userpotion", buy_uname, keyid, i);
						hnum = hnum + buypL->jjgetAry("holding", "userpotion", buy_uname, i);
						buypL->jjsetAry("holding", "userpotion", buy_uname, hnum, i);
						break;
					}
					else i++;
				}
			}
		}
		else if (arrayorder == 2) {//방어구 구매했다는 것
			if (keyid == 1) {
				for (int i = 0; i < 2;) {
					auto id1 = buypL->jjgetAry("keyid", "userweapon", buy_uname, i);
					if (id1 == keyid) {
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else if (id1 == 999) {
						buypL->jjsetAry("keyid", "userweapon", buy_uname, keyid, i);
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else i++;
				}
			}
			else if (keyid == 2) {
				for (int i = 0; i < 2;) {
					auto id1 = buypL->jjgetAry("keyid", "userweapon", buy_uname, i);
					if (id1 == keyid) {
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else if (id1 == 999) {
						buypL->jjsetAry("keyid", "userweapon", buy_uname, keyid, i);
						hnum = hnum + buypL->jjgetAry("holding", "userweapon", buy_uname, i);
						buypL->jjsetAry("holding", "userweapon", buy_uname, hnum, i);
						break;
					}
					else i++;
				}
			}
		}

		auto done = MenuItemImage::create("market.png", "market.png");
		auto check = MenuItemImage::create("close.png", "close.png", CC_CALLBACK_1(BuyLayer::ok, this));
		auto checkb = Menu::create(done, check, NULL);
		checkb->setAnchorPoint(Point(0.5,0.5));
		checkb->alignItemsVertically();
		checkb->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, Director::getInstance()->
			getWinSize().height / 2));
		this->addChild(checkb);
	}
	else {
		auto notice = MenuItemImage::create("notice.png", "notice.png");
		auto cancel = MenuItemImage::create("close.png", "close.png", CC_CALLBACK_1(BuyLayer::exit, this));
		auto cancelb = Menu::create(notice, cancel, NULL);
		cancelb->alignItemsVertically();
		cancelb->setAnchorPoint(Point(0.5,0.5));
	
		cancelb->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, Director::getInstance()->
			getWinSize().height / 2));
		this->addChild(cancelb);
	}

	return true;
}

void BuyLayer::exit(cocos2d::Ref* sender) {
	//auto exitbut = (MenuItem*)sender;
	//this->removeFromParentAndCleanup(exitbut);
	Director::getInstance()->popScene();
}


void BuyLayer::ok(cocos2d::Ref* sender) {
	//PotionLayer* potion = dynamic_cast<PotionLayer*>(getParent());

	Director::getInstance()->popScene();
	//auto okbut = (MenuItem*)sender;
	//this->removeFromParentAndCleanup(okbut);
}
