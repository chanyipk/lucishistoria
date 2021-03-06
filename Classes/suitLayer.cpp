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
	//weapon.json 생성
	suitpL = dynamic_cast<Jdata*>(getParent());

	//(0208 충돌방지)를 위해 하나의 포인터 사용
	//Jdata* userpL = dynamic_cast<Jdata*>(getParent());

	suitpL->jjPotionAppend(); //새로 추가하는 팀원한테 필요 Append함수 내에 생성여부 코드 추가
								//std::string suitfullPath = "C:\\json\\"
	std::string suitfullPath = "C:\\json\\";
	suitfullPath.append("weapon.json");

	//필요 데이터 초기화
	dataSingleton::getInstance()->price = 0;
	dataSingleton::getInstance()->userMoney = 0;
	cash = 0; //json과 datasingleton의 userMoney사이의 매개변수입니다.
	plminum = 1;//plus minus값을 저장하고 라벨을 만들어주는 변수입니다.
	selected = 0;//선택된 포션의 태그값을 전달하는 변수입니다.

				 //정상path 확인
	if (suitfullPath.size() == 0) {
		log("path failed");
	}

	//json에 있는 내용을 data로 가져옴
	//std::string data;
	docdata.clear();//이 내용도 초기화로 보냄
	docdata = FileUtils::getInstance()->getStringFromFile(suitfullPath);

	//Document생성
	//Document sdocument;

	//json에 있는 data를 Document형식으로 파싱
	if (!sdocument.Parse<0>(docdata.c_str()).HasParseError())
	{
		//log("0213-----------------");
	}

	//가져올 배열의 이름으로 value를 생성해야 합니다.
	const rapidjson::Value& documentPotion = sdocument["weapon"];

	//////////////SH물약 정보 생성

	//배열은 순서대로 0으로 시작합니다. 여기서 SH 태그 값이 0이라서 배열의 0번째 SH아이템을 불러온 상태입니다.
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

	//////////////PA물약 정보 생성
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

	///////////////구매박스 이미지 생성
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

	//(0208 충돌방지)data.json은 사용하지 않습니다.
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
	//터치한 객체를 타겟에 저장합니다.
	auto target3 = (Sprite *)event->getCurrentTarget();
	Point pos3 = target3->convertToNodeSpace(touch->getLocation());
	Rect rect3 = Rect(0, 0, target3->getContentSize().width, target3->getContentSize().height);

	if (rect3.containsPoint(pos3)) {
		dataSingleton::getInstance()->itemnum = 100;
		Director::getInstance()->pushScene(BuyLayer::createScene());
		refresh();//이 때 refresh는 Scene이 pop된 이후에 값을 갱신하기 위해 사용합니다.
				  //아래 코드대신 push pop 사용
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
	//BuyLayer에서 구매작업을 수행하기 위해 필요한 값을 넘겨주는 함수
	int itemPrice = 1;
	dataSingleton::getInstance()->cashtag = 2;//cashtag가 2인건 장비
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
	//+와 - 버튼을 눌렀을 때 숫자라벨값을 변경해 주는 함수
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
	//아이템 구매후 사용자가 보유한 금액을 갱신해주는 함수
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
