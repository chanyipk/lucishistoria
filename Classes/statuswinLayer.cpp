#include "statuswinLayer.h"
#include "Jdata.h"
#include "dataSingleton.h"
Jdata* pS;

Scene* statuswinLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = statuswinLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool statuswinLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	std::string st_uname = dataSingleton::getInstance()->user;
	dataSingleton::getInstance()->open = true;

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background);

	status_win = Sprite::create("status.png");
	status_win->setAnchorPoint(Point(0.5, 0.5));
	status_win->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	status_win->setTag(STATUSW);
	this->addChild(status_win);

	auto exit = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(statuswinLayer::closebut, this));
	auto exit_b = Menu::create(exit, NULL);
	exit_b->setTag(EXIT);
	exit_b->setPosition(Point(1685, 962));
	this->addChild(exit_b);

	int classnum = pS->jjgetInt("class", st_uname);

	std::string name = pS->jjgetString("name", st_uname);

	int level = pS->jjgetInt("level", st_uname);
	std::string levelstr = std::to_string(level);

	int maxhp = pS->jjgetInt("maxhp", st_uname);
	std::string maxhpstr = std::to_string(maxhp);

	int hp = pS->jjgetInt("hp", st_uname);
	std::string hpstr = std::to_string(hp);

	int maxmp = pS->jjgetInt("maxmp", st_uname);
	std::string maxmpstr = std::to_string(maxmp);

	int mp = pS->jjgetInt("mp", st_uname);
	std::string mpstr = std::to_string(mp);

	int maxexp = pS->jjgetInt("maxexp", st_uname);
	std::string maxexpstr = std::to_string(maxexp);

	int exp = pS->jjgetInt("exp", st_uname);
	std::string expstr = std::to_string(exp);

	int money = pS->jjgetInt("money", st_uname);
	std::string moneystr = std::to_string(money);



	int atk = pS->jjgetInt("atk", st_uname);
	std::string atkstr = std::to_string(atk);

/*	int atkst = pS->jjgetInt("atkst", st_uname);
	std::string atkststr = std::to_string(atkst);
	*/
	int def = pS->jjgetInt("def", st_uname);
	std::string defstr = std::to_string(def);
/*
	int defst = pS->jjgetInt("defst", st_uname);
	std::string defststr = std::to_string(defst);
	*/
	int cri = pS->jjgetInt("cri", st_uname);
	std::string cristr = std::to_string(cri);

	int cridam = pS->jjgetInt("cridam", st_uname);
	std::string cridamstr = std::to_string(cridam);

	switch (classnum)
	{
	case 1: {
		auto pro = Sprite::create("man.png");
		pro->setScale(0.50);
		pro->setAnchorPoint(Point(0.5, 0));
		pro->setPosition(Point(630, 93));
		status_win->addChild(pro);
		auto classttf = Label::createWithTTF("KNIGHT", "nanumgo.ttf", 30);
		classttf->setAnchorPoint(Point(0.5, 0.5));
		classttf->setPosition(Point(620, 850));
		status_win->addChild(classttf);

		break;
	}
	default:
		break;
	}


	auto levelnamettf = Label::createWithTTF("Lv.  " + levelstr + " " + name, "nanumgo.ttf", 40);
	levelnamettf->setAnchorPoint(Point(0.5, 0.5));
	levelnamettf->setPosition(Point(620, 900));
	status_win->addChild(levelnamettf);

	auto hpmaxhpttf = Label::createWithTTF("HP  " + hpstr + " / " + maxhpstr, "nanumgo.ttf", 35);
	hpmaxhpttf->setAnchorPoint(Point(0, 0));
	hpmaxhpttf->setPosition(Point(1050, 840));
	status_win->addChild(hpmaxhpttf);

	auto mpmaxmpttf = Label::createWithTTF("MP  " + mpstr + " / " + maxmpstr, "nanumgo.ttf", 35);
	mpmaxmpttf->setAnchorPoint(Point(0, 0));
	mpmaxmpttf->setPosition(Point(1360, 840));
	status_win->addChild(mpmaxmpttf);

	auto expmaxexpttf = Label::createWithTTF("EXP  " + expstr + " / " + maxexpstr, "nanumgo.ttf", 35);
	expmaxexpttf->setAnchorPoint(Point(0, 0));
	expmaxexpttf->setPosition(Point(1050, 760));
	status_win->addChild(expmaxexpttf);


	auto atkatkstttf = Label::createWithTTF("ATK  " + atkstr , "nanumgo.ttf", 35);
	atkatkstttf->setAnchorPoint(Point(0, 0));
	atkatkstttf->setPosition(Point(1050, 680));
	status_win->addChild(atkatkstttf);

	auto defdefstttf = Label::createWithTTF("DEF  " + defstr , "nanumgo.ttf", 35);
	defdefstttf->setAnchorPoint(Point(0, 0));
	defdefstttf->setPosition(Point(1360, 680));
	status_win->addChild(defdefstttf);

	auto crittf = Label::createWithTTF("CRITICAL  " + cristr + " (%)", "nanumgo.ttf", 35);//+0은 장비 착용시 증각하도록
	crittf->setAnchorPoint(Point(0, 0));
	crittf->setPosition(Point(1050, 600));
	status_win->addChild(crittf);

	auto cridamttf = Label::createWithTTF("CRITICAL DAMAGE  " + cridamstr + " (%)", "nanumgo.ttf", 35);//+0은 장비 착용시 증각하도록
	cridamttf->setAnchorPoint(Point(0, 0));
	cridamttf->setPosition(Point(1050, 520));
	status_win->addChild(cridamttf);


	auto moneyttf = Label::createWithTTF(moneystr, "nanumgo.ttf", 35);
	moneyttf->setAnchorPoint(Point(1, 0));
	moneyttf->setPosition(Point(1600, 105));
	status_win->addChild(moneyttf);

	statinfo();


}
void statuswinLayer::statinfo() {
	std::string st_uname2 = dataSingleton::getInstance()->user;
	//stat
	int stat = pS->jjgetInt("stat", st_uname2);
	std::string statstr = std::to_string(stat);

	int atkst = pS->jjgetInt("atkst", st_uname2);
	std::string atkststr = std::to_string(atkst);

	int defst = pS->jjgetInt("defst", st_uname2);
	std::string defststr = std::to_string(defst);

	atkstL = Label::createWithTTF(" (+" + atkststr + ")", "nanumgo.ttf", 35);
	atkstL->setAnchorPoint(Point(0, 0));
	atkstL->setPosition(Point(1200, 681));
	status_win->addChild(atkstL);


	defstL = Label::createWithTTF(" (+" + defststr + ")", "nanumgo.ttf", 35);
	defstL->setAnchorPoint(Point(0, 0));
	defstL->setPosition(Point(1510, 679));
	status_win->addChild(defstL);

	statttf = Label::createWithTTF("All Stat: " + statstr, "nanumgo.ttf", 35);
	statttf->setAnchorPoint(Point(0, 0));
	statttf->setPosition(Point(1050, 333));
	status_win->addChild(statttf);

	atkstttf = Label::createWithTTF("ATK Stat: " + atkststr, "nanumgo.ttf", 35);
	atkstttf->setAnchorPoint(Point(0, 0));
	atkstttf->setPosition(Point(1050, 265));
	status_win->addChild(atkstttf);

	auto addatk = MenuItemImage::create("add.png", "add.png", CC_CALLBACK_1(statuswinLayer::addstat, this, 0));
	auto addatk_b = Menu::create(addatk, NULL);
	addatk_b->setAnchorPoint(Point(0, 0));
	addatk_b->setPosition(Point(1310, 290));
	this->addChild(addatk_b);

	defstttf = Label::createWithTTF("DEF Stat: " + defststr, "nanumgo.ttf", 35);
	defstttf->setAnchorPoint(Point(0, 0));
	defstttf->setPosition(Point(1050, 195));
	status_win->addChild(defstttf);

	auto adddef = MenuItemImage::create("add.png", "add.png", CC_CALLBACK_1(statuswinLayer::addstat, this, 1));
	auto adddef_b = Menu::create(adddef, NULL);
	adddef_b->setAnchorPoint(Point(0, 0));
	adddef_b->setPosition(Point(1310, 220));
	this->addChild(adddef_b);


}
void statuswinLayer::addstat(Ref *sender, int n) {
	std::string st_uname3 = dataSingleton::getInstance()->user;
	int atkst = pS->jjgetInt("atkst", st_uname3);
	int defst = pS->jjgetInt("defst", st_uname3);
	auto nowstat = pS->jjgetInt("stat", st_uname3);
	if (nowstat > 0) {
		pS->jjsetInt(nowstat - 1, "stat", st_uname3);
		String *downstat = String::createWithFormat("All Stat: %d", nowstat - 1);
		statttf->setString(downstat->getCString());
		if (n == 0) {
			pS->jjsetInt(atkst + 1, "atkst", st_uname3);
			String *upatk = String::createWithFormat("ATK Stat: %d", atkst + 1);
			atkstttf->setString(upatk->getCString());

			pS->jjsetInt(atkst + 1, "atkst", st_uname3);
			String *upatkL = String::createWithFormat(" (+%d)", atkst + 1);
			atkstL->setString(upatkL->getCString());
		}
		else if (n == 1) {
			pS->jjsetInt(defst + 1, "defst", st_uname3);
			String *updef = String::createWithFormat("DEF Stat: %d", defst + 1);
			defstttf->setString(updef->getCString());

			pS->jjsetInt(defst + 1, "defst", st_uname3);
			String *updefL = String::createWithFormat(" (+%d)", defst + 1);
			defstL->setString(updefL->getCString());
		}
	}
	

	
	//statinfo();

}
void statuswinLayer::closebut(Ref *sender) {
	dataSingleton::getInstance()->open = false;
	this->removeAllChildren();
}


