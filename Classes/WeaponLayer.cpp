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
	//potion.json ����
	weaponpL = dynamic_cast<Jdata*>(getParent());

	//(0208 �浹����)�� ���� �ϳ��� ������ ���
	//Jdata* userpL = dynamic_cast<Jdata*>(getParent());

	//weaponpL->jjWeaponAppend(); //�������. weapon�� posion.json�� �ֽ��ϴ�.
	//std::string weaponfullPath = "C:\\json\\";
	std::string weaponfullPath = "C:\\json\\";;
	weaponfullPath.append("weapon.json");

	//�ʿ� ������ �ʱ�ȭ
	dataSingleton::getInstance()->price = 0;
	dataSingleton::getInstance()->userMoney = 0;
	wpcash = 0; //json�� datasingleton�� userMoney������ �Ű������Դϴ�.
	wplminum = 1;//plus minus���� �����ϰ� ���� ������ִ� �����Դϴ�.
	wpselected = 0;//���õ� ������ �±װ��� �����ϴ� �����Դϴ�.

				 //����path Ȯ��
	if (weaponfullPath.size() == 0) {
		log("path failed");
	}

	//json�� �ִ� ������ data�� ������
	//std::string data;
	wdocdata.clear();//�� ���뵵 �ʱ�ȭ�� ����
	wdocdata = FileUtils::getInstance()->getStringFromFile(weaponfullPath);

	//Document����
	//Document document;

	//json�� �ִ� data�� Document�������� �Ľ�
	if (!wpdoc.Parse<0>(wdocdata.c_str()).HasParseError())
	{
		//log("0213-----------------");
	}

	//������ �迭�� �̸����� value�� �����ؾ� �մϴ�.
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
	
/*	//////////////WP_2���� ���� ����
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
	
	///////////////���Źڽ� �̹��� ����
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
	//��ġ�� ��ü�� Ÿ�ٿ� �����մϴ�.
	auto target4 = (Sprite *)event->getCurrentTarget();
	Point pos4 = target4->convertToNodeSpace(touch->getLocation());
	Rect rect4 = Rect(0, 0, target4->getContentSize().width, target4->getContentSize().height);

	if (rect4.containsPoint(pos4)) {
		dataSingleton::getInstance()->itemnum = 200;
		Director::getInstance()->pushScene(BuyLayer::createScene());
		wprefresh();//�� �� refresh�� Scene�� pop�� ���Ŀ� ���� �����ϱ� ���� ����մϴ�.
				  //�Ʒ� �ڵ��� push pop ���
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
	//BuyLayer���� �����۾��� �����ϱ� ���� �ʿ��� ���� �Ѱ��ִ� �Լ�
	int itemPrice = 1;
	dataSingleton::getInstance()->cashtag = 0;//cashtag�� 0�̸� ���⸦ �����Ѱ�
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
	//+�� - ��ư�� ������ �� ���ڶ󺧰��� ������ �ִ� �Լ�
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
	//������ ������ ����ڰ� ������ �ݾ��� �������ִ� �Լ�
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