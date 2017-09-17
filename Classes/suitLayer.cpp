#include "suitLayer.h"
#include "Jdata.h"
#include "../../cocos2d/external/json/rapidjson.h"
#include "../../cocos2d/external/json/document.h"
#include "../../cocos2d/external/json/stringbuffer.h"
#include "dataSingleton.h"
#include "BuyLayer.h"

using namespace rapidjson;

Document sdocument;
Jdata* suitpL;

Scene* suitLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = suitLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool suitLayer::init() {

	if (!Layer::init()) {
		return false;
	}
	std::string p_uname = dataSingleton::getInstance()->user;
	//weapon.json ����
	suitpL = dynamic_cast<Jdata*>(getParent());

	//(0208 �浹����)�� ���� �ϳ��� ������ ���
	//Jdata* userpL = dynamic_cast<Jdata*>(getParent());

	suitpL->jjPotionAppend(); //���� �߰��ϴ� �������� �ʿ� Append�Լ� ���� �������� �ڵ� �߰�
								//std::string suitfullPath = "C:\\json\\"
	std::string suitfullPath = "C:\\json\\";
	suitfullPath.append("weapon.json");

	//�ʿ� ������ �ʱ�ȭ
	dataSingleton::getInstance()->price = 0;
	dataSingleton::getInstance()->userMoney = 0;
	cash = 0; //json�� datasingleton�� userMoney������ �Ű������Դϴ�.
	plminum = 1;//plus minus���� �����ϰ� ���� ������ִ� �����Դϴ�.
	selected = 0;//���õ� ������ �±װ��� �����ϴ� �����Դϴ�.

				 //����path Ȯ��
	if (suitfullPath.size() == 0) {
		log("path failed");
	}

	//json�� �ִ� ������ data�� ������
	//std::string data;
	docdata.clear();//�� ���뵵 �ʱ�ȭ�� ����
	docdata = FileUtils::getInstance()->getStringFromFile(suitfullPath);

	//Document����
	//Document sdocument;

	//json�� �ִ� data�� Document�������� �Ľ�
	if (!sdocument.Parse<0>(docdata.c_str()).HasParseError())
	{
		//log("0213-----------------");
	}

	//������ �迭�� �̸����� value�� �����ؾ� �մϴ�.
	const rapidjson::Value& documentPotion = sdocument["weapon"];

	//////////////SH���� ���� ����

	//�迭�� ������� 0���� �����մϴ�. ���⼭ SH �±� ���� 0�̶� �迭�� 0��° SH�������� �ҷ��� �����Դϴ�.
	std::string hpfile = documentPotion[SH]["shoppng"].GetString();
	std::string hpimg = documentPotion[SH]["infoimg"].GetString();

	auto item0 = MenuItemImage::create(hpfile, hpfile, CC_CALLBACK_1(suitLayer::suitSelect, this));
	item0->setTag(SH);
	auto item0b = Menu::create(item0, NULL);
	item0b->setAnchorPoint(Point::ZERO);
	item0b->setPosition(1200, 850);
	this->addChild(item0b);

	auto hpSpr = Sprite::create(hpimg);
	hpSpr->setPosition(750, 650);
	hpSpr->setVisible(false);

	hpSpr->setTag(SHIMG);
	this->addChild(hpSpr);

	//////////////PA���� ���� ����
	std::string mpfile = documentPotion[PA]["shoppng"].GetString();
	std::string mpimg = documentPotion[PA]["infoimg"].GetString();

	auto item1 = MenuItemImage::create(mpfile, mpfile, CC_CALLBACK_1(suitLayer::suitSelect, this));
	item1->setTag(PA);
	auto item1b = Menu::create(item1, NULL);
	item1b->setAnchorPoint(Point::ZERO);
	item1b->setPosition(1600, 850);
	this->addChild(item1b);

	auto mpSpr = Sprite::create(mpimg);
	mpSpr->setPosition(750, 650);
	mpSpr->setVisible(false);
	mpSpr->setTag(PAIMG);
	this->addChild(mpSpr);

	///////////////���Źڽ� �̹��� ����
	auto shop = Sprite::create("shop.png");
	shop->setAnchorPoint(Point::ZERO);
	shop->setPosition(550, 250);
	shop->setScale(0.8);
	this->addChild(shop);

	auto plus = MenuItemImage::create("add.png", "add.png", CC_CALLBACK_1(suitLayer::count, this));
	plus->setTag(PLUS);
	auto plusb = Menu::create(plus, NULL);
	plusb->setAnchorPoint(Point::ZERO);
	plusb->setPosition(850, 300);
	this->addChild(plusb);

	auto minus = MenuItemImage::create("minus.png", "minus.png", CC_CALLBACK_1(suitLayer::count, this));
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
	cash = suitpL->jjgetInt("money", p_uname);

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
	buyListener->onTouchBegan = CC_CALLBACK_2(suitLayer::onSprTouchBegan, this);
	dispatcher3->addEventListenerWithSceneGraphPriority(buyListener, buy);

	return true;
}

bool suitLayer::onSprTouchBegan(Touch * touch, Event * event) {
	suitBuy();
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

void suitLayer::suitSelect(cocos2d::Ref* sender) {

	auto suitbtn = (MenuItem*)sender;

	cocos2d::Sprite *hSpr, *mSpr;
	hSpr = (Sprite*)this->getChildByTag(SHIMG);
	mSpr = (Sprite*)this->getChildByTag(PAIMG);

	if (suitbtn->getTag() == SH)
	{
		hSpr->setVisible(true);
		mSpr->setVisible(false);
		selected = SHIMG;
	}
	else if (suitbtn->getTag() == PA)
	{
		hSpr->setVisible(false);
		mSpr->setVisible(true);
		selected = PAIMG;
	}
	else
	{
		hSpr->setVisible(false);
		mSpr->setVisible(false);
		selected = 0;
	}
}

void suitLayer::suitBuy() {
	//BuyLayer���� �����۾��� �����ϱ� ���� �ʿ��� ���� �Ѱ��ִ� �Լ�
	int itemPrice = 1;
	dataSingleton::getInstance()->cashtag = 2;//cashtag�� 2�ΰ� ���
	if (selected == SHIMG) {

		itemPrice = suitpL->jjgetAry("money", "weapon", "weapon", 1);
		dataSingleton::getInstance()->itemkeyid = suitpL->jjgetAry("keyid", "weapon", "weapon", 1);
	}
	else if (selected == PAIMG) {

		itemPrice = suitpL->jjgetAry("money", "weapon", "weapon", 2);
		dataSingleton::getInstance()->itemkeyid = suitpL->jjgetAry("keyid", "weapon", "weapon", 2);
	}
	dataSingleton::getInstance()->holdingnum = plminum;
	dataSingleton::getInstance()->price = plminum * itemPrice;
}

void suitLayer::count(cocos2d::Ref* sender) {
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

void suitLayer::refresh() {
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
