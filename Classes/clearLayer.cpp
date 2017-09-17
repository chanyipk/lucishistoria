#include "clearLayer.h"
#include "dataSingleton.h"
#include "Jdata.h"
#include "ElyonScene.h"

Jdata* pC;

Scene* clearLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = clearLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool clearLayer::init() {
	
	bg = Sprite::create("clearbg.png");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	this->addChild(bg);
	auto timef = CallFuncN::create(CC_CALLBACK_0(clearLayer::timef, this));
	auto rankf = CallFuncN::create(CC_CALLBACK_0(clearLayer::rankf, this));
	auto dt1 = DelayTime::create(1.0);
	auto rewardf = CallFuncN::create(CC_CALLBACK_0(clearLayer::rewardf, this));
	auto dt2 = DelayTime::create(3.0);
	auto dt3 = DelayTime::create(5.0);
	auto changescene = CallFuncN::create(CC_CALLBACK_0(clearLayer::changeScene, this));

	auto seq = Sequence::create(dt1, timef, dt1, rankf,dt2,rewardf, dt3, changescene,NULL);
	
	this->runAction(seq);

	return true;
}

void clearLayer::timef() {

	min = dataSingleton::getInstance()->minute;
	std::string mins = std::to_string(min);
	sec = dataSingleton::getInstance()->time;
	std::string secs = std::to_string(sec);
	cleartime = Label::createWithTTF(mins + " 분 " + secs + " 초 ", "nanumgo.ttf", 60);
	cleartime->setPosition(Point(730, 800));
	cleartime->setAnchorPoint(Point(0,0));
	this->addChild(cleartime);

}
void clearLayer::rankf() {
	
	if (min == 0) {
		if (sec <= 30) {
			rank = Sprite::create("S.png");
		}
		else
			rank = Sprite::create("A.png");
	}
	else {
		rank = Sprite::create("B.png");

	}

	
	rank->setPosition(Point(560, 256));
	this->addChild(rank);
}

void clearLayer::rewardf() {
	std::string clear_uname = dataSingleton::getInstance()->user;
	this->removeChild(cleartime);
	this->removeChild(rank);
	bg->setTexture(Director::getInstance()->getTextureCache()->addImage("rewardbg.png"));
	int ranknum;
	if (min == 0) {
		if (sec <= 30)
			ranknum = 4;
		else
			ranknum = 3;
	}
	else if (min == 1) {
		ranknum = 2;
	}
	else
		ranknum = 1;
	
	
	for (int i = 0; i < ranknum; i++) {
		int num = (rand() % 4) + 0;
		switch (num)
		{
		case 0: {//경험치
			auto rwexp = Sprite::create("rwexp.png");
			int expnum = (rand() % 101) + 100;
			std::string estr = std::to_string(expnum);
			auto elabel = Label::createWithTTF(estr + " EXP", "nanumgo.ttf", 24);
			int x = rwset(i);
			rwexp->setPosition(x, 580);
			elabel->setPosition(x, 480);
			this->addChild(rwexp);
			this->addChild(elabel);
			auto haveexp = pC->jjgetInt("exp", clear_uname);
			pC->jjsetInt(haveexp + expnum, "exp", clear_uname);
			break;
		}
		case 1: {//장비
			int itemnum = (rand() % 3);
			Sprite* rwitem;
			Label* ilabel;
			if(itemnum == 0){
				rwitem = Sprite::create("rwwp.png");
				
				ilabel = Label::createWithTTF("초보자 양날검", "nanumgo.ttf", 24);
			}
			else if(itemnum == 1){
				rwitem = Sprite::create("rwsh.png");
				ilabel = Label::createWithTTF("여행자 상의", "nanumgo.ttf", 24);
			}
			else if(itemnum == 2){
				rwitem = Sprite::create("rwpa.png");
				ilabel = Label::createWithTTF("여행자 하의", "nanumgo.ttf", 24);
			}
		
			int x = rwset(i);
			rwitem->setPosition(x, 580);
			ilabel->setPosition(x , 480);
			this->addChild(rwitem);
			this->addChild(ilabel);
			
			for (int i = 0; i < 4; ) {
				//비어있는  배열 찾기or 동일한 아이디 찾기
				auto keyid = pC->jjgetAry("keyid", "userweapon", clear_uname, i);
				if (keyid == 999) {
					pC->jjsetAry("keyid", "userweapon", clear_uname, itemnum, i);
					pC->jjsetAry("holding", "userweapon", clear_uname, 1, i);
					break;
				}
				else if (keyid == itemnum) {
					auto holding = pC->jjgetAry("holding", "userweapon", clear_uname, i);
					pC->jjsetAry("holding", "userweapon", clear_uname, holding + 1, i);
					break;
				}
				else
					i++;
			}
			break;

		}
		case 2: {//포션
			int potionnum = (rand() % 2);
			int pnum = (rand() % 3) + 1;
			std::string ponum = std::to_string(pnum);
			Sprite* rwpotion;
			Label* plabel;
			if (potionnum == 0) {
				
				rwpotion = Sprite::create("rwred.png");

				plabel = Label::createWithTTF("HP포션 x "+ ponum, "nanumgo.ttf", 24);
			}
			else if (potionnum == 1) {
				rwpotion = Sprite::create("rwblue.png");
				plabel = Label::createWithTTF("MP포션 x "+ ponum, "nanumgo.ttf", 24);
			}
		
			int x = rwset(i);
			rwpotion->setPosition(x, 580);
			plabel->setPosition(x, 480);
			this->addChild(rwpotion);
			this->addChild(plabel);
			for (int i = 0; i < 2; ) {
				//비어있는  배열 찾기or 동일한 아이디 찾기
				auto keyid = pC->jjgetAry("keyid", "userpotion", clear_uname, i);
				if (keyid == 999) {

					pC->jjsetAry("keyid", "userpotion", clear_uname, potionnum, i);
					pC->jjsetAry("holding", "userpotion", clear_uname, pnum, i);
					break;
				}
				else if (keyid == potionnum) {
					auto holding = pC->jjgetAry("holding", "userpotion", clear_uname, i);
					pC->jjsetAry("holding", "userpotion", clear_uname, holding + pnum, i);
					break;
				}
				else
					i++;
			}

			break;
		}
		case 3: {//돈
			auto rwmoney = Sprite::create("rwmoney.png");
			int moneynum = (rand() % 1001) + 1000;
			std::string mstr = std::to_string(moneynum);
			auto mlabel = Label::createWithTTF(mstr + " 크루", "nanumgo.ttf", 24);
			int x = rwset(i);
			rwmoney->setPosition(x, 580);
			mlabel->setPosition(x, 480);
			this->addChild(rwmoney);
			this->addChild(mlabel);
			auto havemoney = pC->jjgetInt("money", clear_uname);
			pC->jjsetInt(havemoney+ moneynum, "money", clear_uname);
			break;

		}
		default:
			break;
		}
	}
}
int clearLayer::rwset(int n){
	int x;
	switch (n)
	{
	case 0: {
		x = 360;
		break; }
	case 1: {
		x = 800;
		break; }
	case 2: {
		x = 1180;
		break;
	}
	case 3: {
		x = 1560;
		break; }
	default:
		break;
	}
	return x;
}

void clearLayer::changeScene() {

	Director::getInstance()->replaceScene(ElyonScene::createScene());
}