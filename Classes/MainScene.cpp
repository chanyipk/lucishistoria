#include "MainScene.h"
#include "PrologScene1.h"
#include "SimpleAudioEngine.h"
Jdata* mainpL;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainScene::create();

	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("In Game.mp3", true);
	initBG();

	dataSingleton::getInstance()->touch = true;//시작버튼 삭제버튼 클릭안되게
	dataSingleton::getInstance()->enable = true;//공지 이벤트 중첩방지
	listnum = 4;

	auto winback_1 = Sprite::create("winback.png");
	winback_1->setAnchorPoint(Point(0, 1));
	winback_1->setPosition(Point(1100, 1050));
	this->addChild(winback_1);

	auto winback_2 = Sprite::create("winback.png");
	winback_2->setAnchorPoint(Point(0, 1));
	winback_2->setPosition(Point(1100, 783));
	this->addChild(winback_2);

	auto winback_3 = Sprite::create("winback.png");
	winback_3->setAnchorPoint(Point(0, 1));
	winback_3->setPosition(Point(1100, 516));
	this->addChild(winback_3);

	auto winback_4 = Sprite::create("winback.png");
	winback_4->setAnchorPoint(Point(0, 1));
	winback_4->setPosition(Point(1100, 249));
	this->addChild(winback_4);

	//오른쪽 4개의 반투명 사각상자를 둘러쌓고 있는 금색 테두리

	//왼쪽 상단 2개 버튼 하나는 공지, 다른 하나는 이벤트 버튼 -> 새로운 씬을 만들어 해당 버튼 클릭 시 해당 씬으로 이동
	auto cirbut_1 = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(MainScene::ButtonCallBack1, this));
	auto cirbut_2 = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(MainScene::ButtonCallBack2, this));

	cirbut_1->setTag(CIRBUT_1);
	cirbut_2->setTag(CIRBUT_2);

	auto but_1 = Menu::create(cirbut_1, NULL);
	but_1->alignItemsVertically();
	but_1->setAnchorPoint(Point(0, 0));
	but_1->setPosition(Point(150, 900));
	but_1->setScale(0.6);
	this->addChild(but_1);

	auto but_2 = Menu::create(cirbut_2, NULL);
	but_2->alignItemsVertically();
	but_2->setAnchorPoint(Point(0, 0));
	but_2->setPosition(Point(150, 700));
	but_2->setScale(0.6);
	this->addChild(but_2);

	//왼쪽 하단 캐릭터 생성 및 삭제 버튼
	auto charmake = MenuItemImage::create("create.png", "create_push.png", CC_CALLBACK_1(MainScene::playerMake, this));
	auto chardelete = MenuItemImage::create("delete.png", "delete_push.png", CC_CALLBACK_1(MainScene::deletenotice, this));

	auto crebut = Menu::create(charmake, NULL);
	crebut->setAnchorPoint(Point(0, 0));
	crebut->setPosition(Point(200, 100));
	crebut->setScale(0.6);
	this->addChild(crebut);

	auto delbut = Menu::create(chardelete, NULL);
	delbut->setAnchorPoint(Point(0, 0));
	delbut->setPosition(Point(500, 100));
	delbut->setScale(0.6);
	this->addChild(delbut);

	player_but = MenuItemImage::create("selectwin.png", "selectwin_push.png", CC_CALLBACK_1(MainScene::playerSelect, this));
	player_but->setTag(PLAYER_0_BTN);
	plyr = Menu::create(player_but, NULL);
	plyr->setTag(PLAYER_0);
	plyr->setPosition(Point(1505, 915));
	plyr->setVisible(false);
	this->addChild(plyr);

	//player0 = Label::create();
	player0 = Label::createWithTTF("", "nanumgo.ttf", 40);
	player0->setColor(Color3B(255, 223, 36));
	player0->setPosition(1300, 950);
	player0->setVisible(false);
	player0->setTag(PLAYER_0_LB);	
	this->addChild(player0);

	//log("isUser: %d", dataSingleton::getInstance()->isUser);
	//log("mainPL: %d", mainpL->fileRead(uname));
	//0215추가

	mainpL->jjnamelist();

	namesize = mainpL->jjgetArySize("name", "name");
	if (namesize != 0) {
		log("2: namesize: %d", namesize);
		plyrListshow();
	}
	auto side = Sprite::create("side.png");
	side->setAnchorPoint(Point(0, 1));
	side->setPosition(Point(1100, 1050));
	this->addChild(side);

	
	auto enter = MenuItemImage::create("enter.png", "enter_push.png", CC_CALLBACK_1(MainScene::gotomapScene, this));
	enter->setScale(0.6);
	ebtn = Menu::create(enter, NULL);
	ebtn->setAnchorPoint(Point::ZERO);
	ebtn->setPosition(800, 100);
	ebtn->setTag(ENTERBTN);
	ebtn->setVisible(false);
	this->addChild(ebtn);



	

	return true;
}

void MainScene::plyrListshow() {

	std::string userPath = "C:\\json\\";
	userPath.append("name.json");

	bool isF = FileUtils::sharedFileUtils()->isFileExist(userPath);
	if (isF == true) {
		std::string userdocdata;
		userdocdata.clear();
		userdocdata = FileUtils::getInstance()->getStringFromFile(userPath);

		Document udoc;

		if (!udoc.Parse<0>(userdocdata.c_str()).HasParseError()) {
			log("failed Parsing from userdocdata");
		}

		const rapidjson::Value& docP = udoc["name"];

		std::string user0 = docP[0].GetString();  //이름
		user_name = user0;
		
		int level = mainpL->jjgetInt("level", user0.c_str()); //레벨
		std::string user1 = std::to_string(level); 
		std::string user2 = "LV. " + user1 + "  " + user0;
		dataSingleton::getInstance()->user = user0;
		plyr->setVisible(true);
		player0->setString(user2);
		player0->setVisible(true);
	}
	else {
		log("player list show error");
	}
}

void MainScene::gotomapScene(Ref *sender)
{
	std::string main_uname = mainpL->jjgetuserName(0);
	bool ispro = mainpL->jjgetBool("pro", main_uname);

	if (ispro == true) {
		if (dataSingleton::getInstance()->touch) {
			playerSpr->stopAllActions();
			dataSingleton::getInstance()->user = user_name;
			Director::getInstance()->replaceScene(MapScene::createScene());
		}
	}
	else if (ispro == false) {
		if (dataSingleton::getInstance()->touch) {
			playerSpr->stopAllActions();
			dataSingleton::getInstance()->user = user_name;
			Director::getInstance()->replaceScene(PrologScene1::createScene());
		}
	}
	else {
		log("MainScene::gotomapScene failed");
	}
}
void MainScene::deletenotice(Ref* sender) {
	log("listnum : %d", listnum);
	if (listnum != 4) {
		auto back = Sprite::create("background.png");
		back->setTag(BACK);
		back->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, Director::getInstance()->
			getWinSize().height / 2));
		this->addChild(back);


		auto notice = Sprite::create("deletenotice.png");
		notice->setTag(DNOTICE);
		notice->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, Director::getInstance()->
			getWinSize().height / 2 + 150));
		this->addChild(notice);


		auto check = MenuItemImage::create("check.png", "check_push.png", CC_CALLBACK_1(MainScene::playerDelete, this));
		auto cancel = MenuItemImage::create("cancel.png", "cancel_push.png", CC_CALLBACK_1(MainScene::playerDelete, this));


		auto chbtn = Menu::create(check, NULL);
		chbtn->setAnchorPoint(Point::ZERO);
		chbtn->setPosition(700, 380);
		check->setTag(CH);
		chbtn->setTag(CHBTN);
		this->addChild(chbtn);


		auto cabtn = Menu::create(cancel, NULL);
		cabtn->setAnchorPoint(Point::ZERO);
		cabtn->setPosition(1250, 380);
		cancel->setTag(CA);
		cabtn->setTag(CABTN);
		this->addChild(cabtn);

		auto nL = Label::createWithTTF(user_name, "nanumgo.ttf", 70);
		nL->setPosition(Point(960, 770));
		nL->setTag(NL);
		this->addChild(nL);
	}

}

void MainScene::playerDelete(Ref* sender) {
	this->removeChildByTag(BACK, 1);
	this->removeChildByTag(DNOTICE, 1);
	this->removeChildByTag(CHBTN, 1);
	this->removeChildByTag(CABTN, 1);
	this->removeChildByTag(NL, 1);


	auto buttag = (MenuItem*)sender;

	switch (buttag->getTag()) {
	case CH: {
		this->removeChild(startwin);
		ebtn->setVisible(false);
		//std::string username = mainpL->jjgetString("name", user_name);
		player0->setVisible(false);
		plyr->setVisible(false);
		mainpL->jjnamedelete(user_name);
		mainpL->jjplyrdelete(user_name);
		listnum = 4;
		break;
	}
	case CA: {

		break;
	}
	default: {
		break;
	}
	}
	

}

void MainScene::playerSelect(Ref* sender) {
	
	this->removeChild(startwin, 1);

	listnum = 0;
	
	startwin = Sprite::create("startwin.png");
	startwin->setPosition(Point(680, 600));
	startwin->setScale(0.8);
	this->addChild(startwin);

	playerSpr = Sprite::create("a1.png");
	playerSpr->setAnchorPoint(Point(0.5, 0.5));
	playerSpr->setPosition(Point(450, 650));
	playerSpr->setTag(PLAYER_SPRITE);
	startwin->addChild(playerSpr);

	std::string main_uname2 = mainpL->jjgetuserName(0);
	//dataSingleton::getInstance()->user = user_name;
	auto playerbtn = (MenuItem*)sender;
	cocos2d::Menu *etbtn;
	etbtn = (Menu*)this->getChildByTag(ENTERBTN);
	etbtn->setVisible(true);


	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2);

	animation->addSpriteFrameWithFile("a1.png");
	animation->addSpriteFrameWithFile("a2.png");
	animation->addSpriteFrameWithFile("a3.png");
	animation->addSpriteFrameWithFile("a2.png");
	auto animate = Animate::create(animation);
	auto act = RepeatForever::create(animate);
	playerSpr->runAction(act);
	act->setTag(PLAYER_ACTION);

	std::string name = mainpL->jjgetString("name", main_uname2);

	int level = mainpL->jjgetInt("level", main_uname2);
	std::string levelstr = std::to_string(level);

	
	int atk = mainpL->jjgetInt("atk", main_uname2);
	std::string atkstr = std::to_string(atk);

	int atkst = mainpL->jjgetInt("atkst", main_uname2);
	std::string atkststr = std::to_string(atkst);

	int def = mainpL->jjgetInt("def", main_uname2);
	std::string defstr = std::to_string(def);

	int defst = mainpL->jjgetInt("defst", main_uname2);
	std::string defststr = std::to_string(defst);

	int cri = mainpL->jjgetInt("cri", main_uname2);
	std::string cristr = std::to_string(cri);

	int cridam = mainpL->jjgetInt("cridam", main_uname2);
	std::string cridamstr = std::to_string(cridam);

	auto levelnamettf = Label::createWithTTF("Lv.  " + levelstr + " " + name, "nanumgo.ttf", 40);
	levelnamettf->setAnchorPoint(Point(0.5, 0.5));
	levelnamettf->setPosition(Point(450, 400));
	startwin->addChild(levelnamettf);

	auto atkatkstttf = Label::createWithTTF("ATK  " + atkstr + "(+" + atkststr + ")", "nanumgo.ttf", 35);
	atkatkstttf->setAnchorPoint(Point(0.5, 0.5));
	atkatkstttf->setPosition(Point(300, 300));
	startwin->addChild(atkatkstttf);

	auto defdefstttf = Label::createWithTTF("DEF  " + defstr + "(+" + defststr + ")", "nanumgo.ttf", 35);
	defdefstttf->setAnchorPoint(Point(0.5, 0.5));
	defdefstttf->setPosition(Point(600, 300));
	startwin->addChild(defdefstttf);

	auto crittf = Label::createWithTTF("CRITICAL  " + cristr + " (%)", "nanumgo.ttf", 35);//+0은 장비 착용시 증각하도록
	crittf->setAnchorPoint(Point(0.5, 0.5));
	crittf->setPosition(Point(450, 220));
	startwin->addChild(crittf);

	auto cridamttf = Label::createWithTTF("CRITICAL DAMAGE  " + cridamstr + " (%)", "nanumgo.ttf", 35);//+0은 장비 착용시 증각하도록
	cridamttf->setAnchorPoint(Point(0.5, 0.5));
	cridamttf->setPosition(Point(450, 140));
	startwin->addChild(cridamttf);
}

void MainScene::initBG()
{
	auto backimg = Sprite::create("back.png");
	backimg->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	this->addChild(backimg);

}

void MainScene::ButtonCallBack1(cocos2d::Ref *sender)
{
	if (dataSingleton::getInstance()->enable)
	{
		dataSingleton::getInstance()->enable = false;

		auto noticelayer = NoticeLayer::create();
		this->addChild(noticelayer);
	}

}

void MainScene::ButtonCallBack2(cocos2d::Ref *sender)
{
	if (dataSingleton::getInstance()->enable)
	{
		dataSingleton::getInstance()->enable = false;

		auto eventlayer = EventLayer::create();
		this->addChild(eventlayer);
	}
}

void MainScene::ButtonCallBack3(cocos2d::Ref *sender)
{
	auto mainlayer = MainLayer::create();
	this->addChild(mainlayer);
}

void MainScene::playerMake(Ref *sender)
{
	if (dataSingleton::getInstance()->touch) {

	
		Director::getInstance()->replaceScene(CharacterScene::createScene());
	}
}