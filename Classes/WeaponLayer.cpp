#include "WeaponLayer.h"
#include "Jdata.h"
#include "../../cocos2d/external/json/rapidjson.h"
#include "../../cocos2d/external/json/document.h"
#include "../../cocos2d/external/json/stringbuffer.h"
#include "dataSingleton.h"
#include "BuyLayer.h"
#include "PotionLayer.h"

using namespace rapidjson;

Document wpdoc;
Jdata* weaponpL;

Scene* WeaponLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WeaponLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool WeaponLayer::init() {

	if (!Layer::init()) {
		return false;
	}
	std::string w_uname = dataSingleton::getInstance()->user;
	//potion.json 생성
	weaponpL = dynamic_cast<Jdata*>(getParent());

	//(0208 충돌방지)를 위해 하나의 포인터 사용
	//Jdata* userpL = dynamic_cast<Jdata*>(getParent());

	//weaponpL->jjWeaponAppend(); //변경금지. weapon도 posion.json에 있습니다.
	//std::string weaponfullPath = "C:\\json\\";
	std::string weaponfullPath = "C:\\json\\";;
	weaponfullPath.append("weapon.json");

	//필요 데이터 초기화
	dataSingleton::getInstance()->price = 0;
	dataSingleton::getInstance()->userMoney = 0;
	wpcash = 0; //json과 datasingleton의 userMoney사이의 매개변수입니다.
	wplminum = 1;//plus minus값을 저장하고 라벨을 만들어주는 변수입니다.
	wpselected = 0;//선택된 포션의 태그값을 전달하는 변수입니다.

				 //정상path 확인
	if (weaponfullPath.size() == 0) {
		log("path failed");
	}

	//json에 있는 내용을 data로 가져옴
	//std::string data;
	wdocdata.clear();//이 내용도 초기화로 보냄
	wdocdata = FileUtils::getInstance()->getStringFromFile(weaponfullPath);

	//Document생성
	//Document document;

	//json에 있는 data를 Document형식으로 파싱
	if (!wpdoc.Parse<0>(wdocdata.c_str()).HasParseError())
	{
		//log("0213-----------------");
	}

	//가져올 배열의 이름으로 value를 생성해야 합니다.
	const rapidjson::Value& docWP = wpdoc["weapon"];

	std::string wp1file = docWP[WP_1]["shoppng"].GetString();
	std::string wp1img = docWP[WP_1]["infoimg"].GetString();

	auto item1 = MenuItemImage::create(wp1file, wp1file, CC_CALLBACK_1(WeaponLayer::weaponSelect, this));
	item1->setTag(WP_1);
	auto item1b = Menu::create(item1, NULL);
	item1b->setAnchorPoint(Point::ZERO);
	item1b->setPosition(1200, 850);

	this->addChild(item1b);

	
	auto wp1Spr = Sprite::create(wp1img);
	wp1Spr->setPosition(750, 650);
	wp1Spr->setVisible(false);
	
	wp1Spr->setTag(WP_1IMG);
	this->addChild(wp1Spr);
	
/*	//////////////WP_2물약 정보 생성
	std::string wp2file = docWP[WP_2]["shoppng"].GetString();
	std::string wp2img = docWP[WP_2]["infoimg"].GetString();

	auto item2 = MenuItemImage::create(wp2file, wp2file, CC_CALLBACK_1(WeaponLayer::weaponSelect, this));
	item2->setTag(WP_2);
	auto item2b = Menu::create(item2, NULL);
	item2b->setAnchorPoint(Point::ZERO);
	item2b->setPosition(1600, 850);
	item2b->setScale(0.5);
	this->addChild(item2b);
	
	auto wp2Spr = Sprite::create(wp2img);
	wp2Spr->setPosition(750, 650);
	wp2Spr->setVisible(false);
	wp2Spr->setScale(0.7);
	wp2Spr->setTag(WP_2IMG);
	this->addChild(wp2Spr);*/
	
	///////////////구매박스 이미지 생성
	auto wpshop = Sprite::create("shop.png");
	wpshop->setAnchorPoint(Point::ZERO);
	wpshop->setPosition(550, 250);
	wpshop->setScale(0.8);
	this->addChild(wpshop);
	
	auto wplus = MenuItemImage::create("add.png", "add.png", CC_CALLBACK_1(WeaponLayer::wpcount, this));
	wplus->setTag(WP_PLUS);
	auto wplusb = Menu::create(wplus, NULL);
	wplusb->setAnchorPoint(Point::ZERO);
	wplusb->setPosition(850, 300);
	this->addChild(wplusb);

	auto wminus = MenuItemImage::create("minus.png", "minus.png", CC_CALLBACK_1(WeaponLayer::wpcount, this));
	wminus->setTag(WP_MINUS);
	auto wminusb = Menu::create(wminus, NULL);
	wminusb->setAnchorPoint(Point::ZERO);
	wminusb->setPosition(890, 300);
	this->addChild(wminusb);

	auto wnumLabel = cocos2d::Label::create();
	wnumLabel->setString("1");
	wnumLabel->setTag(WP_NUM);
	wnumLabel->setScale(3);
	wnumLabel->setPosition(Point(760, 300));
	this->addChild(wnumLabel);

	auto userLabel = Label::create();

	wpcash = weaponpL->jjgetInt("money", w_uname);

	std::string cashStr = std::to_string(wpcash);
	dataSingleton::getInstance()->userMoney = wpcash;
	userLabel->setString(cashStr);
	userLabel->setTag(WP_MONEY);
	userLabel->setScale(3);
	userLabel->setPosition(Point(760, 355));
	this->addChild(userLabel);

	auto wbuy = Sprite::create("buy.png");
	wbuy->setAnchorPoint(Point(0.5, 0.5));
	wbuy->setPosition(Point(Director::getInstance()->getWinSize().width / 2, 80));
	this->addChild(wbuy);

	EventDispatcher * dispatcher4 = Director::getInstance()->getEventDispatcher();

	auto buyListener4 = EventListenerTouchOneByOne::create();
	buyListener4->setSwallowTouches(true);
	buyListener4->onTouchBegan = CC_CALLBACK_2(WeaponLayer::wponSprTouchBegan, this);
	dispatcher4->addEventListenerWithSceneGraphPriority(buyListener4, wbuy);
	
	return true;
}

bool WeaponLayer::wponSprTouchBegan(Touch * touch, Event * event) {
	weaponBuy();
	//터치한 객체를 타겟에 저장합니다.
	auto target4 = (Sprite *)event->getCurrentTarget();
	Point pos4 = target4->convertToNodeSpace(touch->getLocation());
	Rect rect4 = Rect(0, 0, target4->getContentSize().width, target4->getContentSize().height);

	if (rect4.containsPoint(pos4)) {
		dataSingleton::getInstance()->itemnum = 200;
		Director::getInstance()->pushScene(BuyLayer::createScene());
		wprefresh();//이 때 refresh는 Scene이 pop된 이후에 값을 갱신하기 위해 사용합니다.
				  //아래 코드대신 push pop 사용
				  //auto buylayer = BuyLayer::create();
				  //this->addChild(buylayer);
		return true;
	}
	return false;
}

void WeaponLayer::weaponSelect(cocos2d::Ref* sender) {

	auto wponbtn = (MenuItem*)sender;

	cocos2d::Sprite *wp1Spr, *wp2Spr;
	wp1Spr = (Sprite*)this->getChildByTag(WP_1IMG);
	//wp2Spr = (Sprite*)this->getChildByTag(WP_2IMG);

	if (wponbtn->getTag() == WP_1)
	{
		wp1Spr->setVisible(true);
//		wp2Spr->setVisible(false);
		wpselected = WP_1IMG;
	}
	else if (wponbtn->getTag() == WP_2)
	{
		wp1Spr->setVisible(false);
//		wp2Spr->setVisible(true);
		wpselected = WP_2IMG;
	}
	else
	{
		wp1Spr->setVisible(false);
		wp2Spr->setVisible(false);
		wpselected = 0;
	}
}

void WeaponLayer::weaponBuy() {
	//BuyLayer에서 구매작업을 수행하기 위해 필요한 값을 넘겨주는 함수
	int itemPrice = 1;
	dataSingleton::getInstance()->cashtag = 0;//cashtag가 0이면 무기를 구입한것
	if (wpselected == WP_1IMG) {
		itemPrice = 3000;
		dataSingleton::getInstance()->itemkeyid = weaponpL->jjgetAry("keyid", "weapon", "weapon", 0);
	}
	/*else if (wpselected == WP_2IMG) {
		itemPrice = 4000;
		dataSingleton::getInstance()->itemkeyid = weaponpL->jjgetAry("keyid", "weapon", "weapon", 1);
	}*/
	dataSingleton::getInstance()->holdingnum = wplminum;
	dataSingleton::getInstance()->price = wplminum * itemPrice;
}

void WeaponLayer::wpcount(cocos2d::Ref* sender) {
	//+와 - 버튼을 눌렀을 때 숫자라벨값을 변경해 주는 함수
	auto countbtn = (MenuItemImage*)sender;
	cocos2d::Label *numlb;
	numlb = (Label*)this->getChildByTag(WP_NUM);

	if (countbtn->getTag() == WP_PLUS && wplminum<100 )
	{
		wplminum++;
	}
	else if (countbtn->getTag() == WP_MINUS)
	{
		if (wplminum > 1) {
			wplminum--;
		}
	}
	numlb->setString(StringUtils::format("%d", wplminum));
	
}

void WeaponLayer::wprefresh() {
	//아이템 구매후 사용자가 보유한 금액을 갱신해주는 함수
	int um;
	std::string umwon;
	um = dataSingleton::getInstance()->userMoney;
	auto uLabel = (Label*)this->getChildByTag(WP_MONEY);
	umwon = std::to_string(um);
	uLabel->setString(umwon);
	auto nLabel = (Label*)this->getChildByTag(WP_NUM);
	wplminum = 1;
	nLabel->setString(std::to_string(wplminum));
}