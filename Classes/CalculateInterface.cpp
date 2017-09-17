#include "CalculateInterface.h"

Scene* CalculateInterface::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CalculateInterface::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CalculateInterface::init()
{

	if (!Layer::init()) {
		return false;
	}

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background);

	auto info_img = Sprite::create("cal_txt.png");//라벨로 바꿔도 됨
	info_img->setAnchorPoint(Point(0.5, 0.5));
	info_img->setScaleX(0.8);
	info_img->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 + 400));
	this->addChild(info_img);

	auto result_box = Sprite::create("cal_result.png");
	result_box->setAnchorPoint(Point(0.5, 0.5));
	result_box->setScale(0.8);
	result_box->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 + 300));
	this->addChild(result_box);

	auto num_back = MenuItemImage::create("cal_back.png", "cal_back.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_back->setScale(0.8);
	num_back->setTag(NUMBACK);
	auto backB = Menu::create(num_back, NULL);
	backB->setAnchorPoint(Point(0.5, 0.5));
	backB->alignItemsHorizontally();
	backB->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 + 520, Director::getInstance()->
		getWinSize().height / 2 + 300));
	this->addChild(backB);

	//숫자 버튼 목록
	auto num_1 = MenuItemImage::create("num_1.png", "num_1.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_1->setScale(0.8);
	num_1->setTag(NUM_1);

	auto num_2 = MenuItemImage::create("num_2.png", "num_2.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_2->setScale(0.8);
	num_2->setTag(NUM_2);

	auto num_3 = MenuItemImage::create("num_3.png", "num_3.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_3->setScale(0.8);
	num_3->setTag(NUM_3);

	auto row1 = Menu::create(num_1, num_2, num_3, NULL);
	row1->setAnchorPoint(Point(0.5, 0.5));
	row1->alignItemsHorizontally();
	row1->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 + 80));
	this->addChild(row1);

	auto num_4 = MenuItemImage::create("num_4.png", "num_4.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_4->setScale(0.8);
	num_4->setTag(NUM_4);

	auto num_5 = MenuItemImage::create("num_5.png", "num_5.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_5->setScale(0.8);
	num_5->setTag(NUM_5);

	auto num_6 = MenuItemImage::create("num_6.png", "num_6.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_6->setScale(0.8);
	num_6->setTag(NUM_6);

	auto row2 = Menu::create(num_4, num_5, num_6, NULL);
	row2->setAnchorPoint(Point(0.5, 0.5));
	row2->alignItemsHorizontally();
	row2->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 - 20));
	this->addChild(row2);

	auto num_7 = MenuItemImage::create("num_7.png", "num_7.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_7->setScale(0.8);
	num_7->setTag(NUM_7);

	auto num_8 = MenuItemImage::create("num_8.png", "num_8.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_8->setScale(0.8);
	num_8->setTag(NUM_8);

	auto num_9 = MenuItemImage::create("num_9.png", "num_9.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_9->setScale(0.8);
	num_9->setTag(NUM_9);

	auto row3 = Menu::create(num_7, num_8, num_9, NULL);
	row3->setAnchorPoint(Point(0.5, 0.5));
	row3->alignItemsHorizontally();
	row3->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 - 120));
	this->addChild(row3);

	auto insert = MenuItemImage::create("cal_insert.png", "cal_insert.png", CC_CALLBACK_1(CalculateInterface::enter, this));
	insert->setScale(0.8);
	insert->setTag(NUM_0);

	auto num_0 = MenuItemImage::create("num_0.png", "num_0.png", CC_CALLBACK_1(CalculateInterface::calculate, this));
	num_0->setScale(0.8);
	num_0->setTag(NUM_0);

	auto cancel = MenuItemImage::create("cal_cancel.png", "cal_cancel.png", CC_CALLBACK_1(CalculateInterface::close, this));
	cancel->setScale(0.8);
	cancel->setTag(NUM_0);

	auto row4 = Menu::create(insert, num_0, cancel, NULL);
	row4->setAnchorPoint(Point(0.5, 0.5));
	row4->alignItemsHorizontally();
	row4->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 - 230));
	this->addChild(row4);

	result_lb = Label::createWithTTF("0", "nanumgo.ttf", 120);
	result_lb->setAnchorPoint(Point(0.5, 0.5));
	result_lb->setPosition(Point(750, 80));
	result_lb->setColor(Color3B::WHITE);
	result_box->addChild(result_lb, 100);
}

void CalculateInterface::calculate(cocos2d::Ref* sender) {
	auto numbtn = (MenuItem*)sender;
	int numtag = numbtn->getTag();
	int input_num;
	int delete_num;

	switch (numtag) {
	case NUMBACK: {
		delete_num = resultnum % 10;
		resultnum -= delete_num;
		if (resultnum != 0) {
			resultnum = resultnum / 10;
		}
		break;
	}
	default: {
		input_num = numtag;

		if (isDigit) {
			resultnum *= 10;
			resultnum += input_num;
		}
		else {
			resultnum += input_num;
			isDigit = true;
		}
		break;
	}
	}

	result_lb->setString(std::to_string(resultnum));
}

void CalculateInterface::enter(cocos2d::Ref* sender) {
	std::string cal_uname = dataSingleton::getInstance()->user;

	if (resultnum != 0) {
		int aryindex = dataSingleton::getInstance()->aryIndex;
		std::string keyStr2 = dataSingleton::getInstance()->keystr;
		int u_holding = pCal->jjgetAry("holding", keyStr2.c_str(), cal_uname, aryindex);
		if (u_holding < resultnum) {
			//(case1. 입력한 값이 사용자가 가진 값보다 큰 경우)
			//입력값이 너무 큽니다. 메세지 띄워주기

			auto label1 = Label::createWithTTF("입력값이 너무 큽니다", "nanumgo.ttf", 100);
			label1->setPosition(Point(960, 700));
			label1->setColor(Color3B::RED);
			this->addChild(label1, 100);

			auto dte1 = DelayTime::create(1.0);
			auto fde1 = FadeOut::create(2.0);
			auto seqe1 = Sequence::create(dte1, fde1, NULL);
			label1->runAction(seqe1);

			isDigit = false;
			resultnum = 0;
			log("toomuch");
		}
		else {
			//(case2. 사용자가 가진 값이 입력한 값보다 크거나 같은 경우)
			//수량 선택이 완료된 상태
			log("done");

			dataSingleton::getInstance()->cal_qty = resultnum;
			StoresaleLayer* sL = dynamic_cast<StoresaleLayer*>(getParent());
			sL->movetoList();
			close(this);
		}
	}
	else {
		//(case0. 아무 값도 입력 안하고 <입력>버튼을 누른 경우)
		//값을 입력해주세요. 메세지 띄워주기

		auto label0 = Label::createWithTTF("수량을 입력해 주세요", "nanumgo.ttf", 100);
		label0->setPosition(Point(960, 700));
		label0->setColor(Color3B::RED);
		this->addChild(label0, 100);

		auto dte0 = DelayTime::create(1.0);
		auto fde0 = FadeOut::create(2.0);
		auto seqe0 = Sequence::create(dte0, fde0, NULL);
		label0->runAction(seqe0);

		log("none");
	}
}

void CalculateInterface::close(cocos2d::Ref* sender) {
	this->removeAllChildren();//removeAllChildren
}