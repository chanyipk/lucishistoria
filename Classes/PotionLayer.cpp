#include "PotionLayer.h"
#include "Jdata.h"
#include "../../cocos2d/external/json/rapidjson.h"
#include "../../cocos2d/external/json/document.h"
#include "../../cocos2d/external/json/stringbuffer.h"
#include "dataSingleton.h"
#include "BuyLayer.h"

using namespace rapidjson;

Document document;
Jdata* potionpL;
dataSingleton* dsl;

Scene* PotionLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PotionLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool PotionLayer::init() {

	if (!Layer::init()) {
		return false;
	}
	std::string p_uname = dataSingleton::getInstance()->user;
	//potion.json ����
	potionpL = dynamic_cast<Jdata*>(getParent());
	
	//(0208 �浹����)�� ���� �ϳ��� ������ ���
	//Jdata* userpL = dynamic_cast<Jdata*>(getParent());
	
	potionpL->jjPotionAppend(); //���� �߰��ϴ� �������� �ʿ� Append�Լ� ���� �������� �ڵ� �߰�
	//std::string potionfullPath = "C:\\json\\"
	std::string potionfullPath = "C:\\json\\";
	potionfullPath.append("potion.json");
	
	//�ʿ� ������ �ʱ�ȭ
	dataSingleton::getInstance()->price = 0;
	dataSingleton::getInstance()->userMoney = 0;
	cash = 0; //json�� datasingleton�� userMoney������ �Ű������Դϴ�.
	plminum = 1;//plus minus���� �����ϰ� ���� ������ִ� �����Դϴ�.
	selected = 0 ;//���õ� ������ �±װ��� �����ϴ� �����Դϴ�.

	//����path Ȯ��
	if (potionfullPath.size() == 0) {
		log("path failed");
	}

	//json�� �ִ� ������ data�� ������
	//std::string data;
	docdata.clear();//�� ���뵵 �ʱ�ȭ�� ����
	docdata = FileUtils::getInstance()->getStringFromFile(potionfullPath);

	//Document����
	//Document document;

	//json�� �ִ� data�� Document�������� �Ľ�
	if (!document.Parse<0>(docdata.c_str()).HasParseError())
	{
		//log("0213-----------------");
	}

	//������ �迭�� �̸����� value�� �����ؾ� �մϴ�.
	const rapidjson::Value& documentPotion = document["potion"];

	//////////////HP���� ���� ����

	//�迭�� ������� 0���� �����մϴ�. ���⼭ HP �±� ���� 0�̶� �迭�� 0��° HP�������� �ҷ��� �����Դϴ�.
	std::string hpfile = documentPotion[HP]["pngname"].GetString();
	std::string hpimg = documentPotion[HP]["infoimg"].GetString();

	auto item0 = MenuItemImage::create(hpfile,hpfile,CC_CALLBACK_1(PotionLayer::potionSelect,this));
	item0->setTag(HP);
	auto item0b = Menu::create(item0, NULL);
	item0b->setAnchorPoint(Point::ZERO);
	item0b->setPosition(1200, 850);
	this->addChild(item0b);

	auto hpSpr = Sprite::create(hpimg);
	hpSpr->setPosition(750, 650);
	hpSpr->setVisible(false);
	
	hpSpr->setTag(HPIMG);
	this->addChild(hpSpr);

	//////////////MP���� ���� ����
	std::string mpfile = documentPotion[MP]["pngname"].GetString();
	std::string mpimg = documentPotion[MP]["infoimg"].GetString();

	auto item1 = MenuItemImage::create(mpfile, mpfile, CC_CALLBACK_1(PotionLayer::potionSelect, this));
	item1->setTag(MP);
	auto item1b = Menu::create(item1, NULL);
	item1b->setAnchorPoint(Point::ZERO);
	item1b->setPosition(1600, 850);
	this->addChild(item1b);

	auto mpSpr = Sprite::create(mpimg);
	mpSpr->setPosition(750, 650);
	mpSpr->setVisible(false);
	mpSpr->setTag(MPIMG);
	this->addChild(mpSpr);

	///////////////���Źڽ� �̹��� ����
	auto shop = Sprite::create("shop.png");
	shop->setAnchorPoint(Point::ZERO);
	shop->setPosition(550, 250);
	shop->setScale(0.8);
	this->addChild(shop);

	auto plus = MenuItemImage::create("add.png", "add.png", CC_CALLBACK_1(PotionLayer::count, this));
	plus->setTag(PLUS);
	auto plusb = Menu::create(plus, NULL);
	plusb->setAnchorPoint(Point::ZERO);
	plusb->setPosition(850, 300);
	this->addChild(plusb);
	
	auto minus = MenuItemImage::create("minus.png", "minus.png", CC_CALLBACK_1(PotionLayer::count, this));
	minus->setTag(MINUS);
	auto minusb = Menu::create(minus, NULL);
	minusb->setAnchorPoint(Point::ZERO);
	minusb->setPosition(890, 300);
	this->addChild(minusb);
	
	auto numLabel = cocos2d::Label::create();
	numLabel->setString("1");
	numLabel->setTag(NUMB);
	numLabel->setScale(3);
	numLabel->setPosition(Point(760, 300));
	this->addChild(numLabel);

	auto userLabel = Label::create();

	//(0208 �浹����)data.json�� ������� �ʽ��ϴ�.
	//int ut = dataSingleton::getInstance()->usertag;
	//std::string ustr = itempL->jjgetuserName(ut);


	//cash = itempL->jjgetInt("money",ustr);
	cash = potionpL->jjgetInt("money", p_uname);

	std::string cashStr = std::to_string(cash);
	dataSingleton::getInstance()->userMoney = cash;
	userLabel->setString(cashStr);
	userLabel->setTag(MONEY);
	userLabel->setScale(3);
	userLabel->setPosition(Point(760, 355));
	this->addChild(userLabel);

	auto buy = Sprite::create("buy.png");
	buy->setAnchorPoint(Point(0.5, 0.5));
	buy->setPosition(Point(Director::getInstance()->getWinSize().width / 2, 80));
	this->addChild(buy);

	EventDispatcher * dispatcher3 = Director::getInstance()->getEventDispatcher();

	auto buyListener = EventListenerTouchOneByOne::create();
	buyListener->setSwallowTouches(true);
	buyListener->onTouchBegan = CC_CALLBACK_2(PotionLayer::onSprTouchBegan, this);
	dispatcher3->addEventListenerWithSceneGraphPriority(buyListener, buy);
	
	return true;
}

bool PotionLayer::onSprTouchBegan(Touch * touch, Event * event) {
	potionBuy();
	//��ġ�� ��ü�� Ÿ�ٿ� �����մϴ�.
	auto target3 = (Sprite *)event->getCurrentTarget();
	Point pos3 = target3->convertToNodeSpace(touch->getLocation());
	Rect rect3 = Rect(0, 0, target3->getContentSize().width, target3->getContentSize().height);

	if (rect3.containsPoint(pos3)) {
		dataSingleton::getInstance()->itemnum = 100;
		Director::getInstance()->pushScene(BuyLayer::createScene());
		refresh();//�� �� refresh�� Scene�� pop�� ���Ŀ� ���� �����ϱ� ���� ����մϴ�.
		//�Ʒ� �ڵ��� push pop ���
		//auto buylayer = BuyLayer::create();
		//this->addChild(buylayer);
		return true;
	}
	return false;
}

void PotionLayer::potionSelect(cocos2d::Ref* sender) {
	
	auto potionbtn = (MenuItem*)sender;

	cocos2d::Sprite *hSpr, *mSpr;
	hSpr = (Sprite*)this->getChildByTag(HPIMG);
	mSpr = (Sprite*)this->getChildByTag(MPIMG);

	if (potionbtn->getTag() == HP)
	{
		hSpr->setVisible(true);
		mSpr->setVisible(false);
		selected = HPIMG;
	}
	else if (potionbtn->getTag() == MP) 
	{
		hSpr->setVisible(false);
		mSpr->setVisible(true);
		selected = MPIMG;
	}
	else 
	{
		hSpr->setVisible(false);
		mSpr->setVisible(false);
		selected = 0;
	}
}

void PotionLayer::potionBuy() {
	//BuyLayer���� �����۾��� �����ϱ� ���� �ʿ��� ���� �Ѱ��ִ� �Լ�
	int itemPrice = 1;
	dataSingleton::getInstance()->cashtag = 1;//cashtag�� 1�ΰ� ������ �����Ѱ�
	if (selected == HPIMG) {
		
	itemPrice = 1000;
	dataSingleton::getInstance()->itemkeyid = potionpL->jjgetAry("keyid", "potion", "potion", 0);
	}
	else if (selected == MPIMG) {
	
	itemPrice = 1100;
	dataSingleton::getInstance()->itemkeyid = potionpL->jjgetAry("keyid", "potion", "potion", 1);
	}
	dataSingleton::getInstance()->holdingnum = plminum;
	dataSingleton::getInstance()->price = plminum * itemPrice;
}

void PotionLayer::count(cocos2d::Ref* sender) {
	//+�� - ��ư�� ������ �� ���ڶ󺧰��� ������ �ִ� �Լ�
	auto countbtn = (MenuItemImage*)sender;
	cocos2d::Label *numlb;
	numlb = (Label*)this->getChildByTag(NUMB);
	
	if (countbtn->getTag() == PLUS && plminum<100)
	{
		plminum++;
	}
	else if (countbtn->getTag() == MINUS)
	{
		if (plminum > 1) {
			plminum--;
		}
	}
	numlb->setString(StringUtils::format("%d", plminum));
	
}

void PotionLayer::refresh() {
	//������ ������ ����ڰ� ������ �ݾ��� �������ִ� �Լ�
	int um;
	std::string umwon;
	um = dataSingleton::getInstance()->userMoney;
	auto uLabel = (Label*)this->getChildByTag(MONEY);
	umwon = std::to_string(um);
	uLabel->setString(umwon);
	auto nLabel = (Label*)this->getChildByTag(NUMB);
	plminum = 1;
	nLabel->setString(std::to_string(plminum));
}
