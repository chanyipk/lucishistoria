#include "ElyonScene.h"
#include "TopLayer.h"
#include "dataSingleton.h"
#include "StoreLayer.h"
#include "UpgradeLayer.h"
#include "DungeonmapScene.h"
#include "UserLayer.h"
#include "statuswinLayer.h"
#include "itemwinLayer.h"
#include "StoresaleLayer.h"
#include "jdata.h"

bool book = false;
Sprite* comuwin;
Sprite* questwin;
bool open2 = false;

Label* notice1;
Label* notice2;
Label* notice3;
Label* notice4;
Label* notice5;
Label* O_t;

Jdata *pK;
bool TopLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	dataSingleton::getInstance()->open = false;
	dataSingleton::getInstance()->open2 = false;
	dataSingleton::getInstance()->isCM = false;

	npc1_i = MenuItemImage::create("npc1_Q.png", "npc1_Q.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//부모님
	npc1 = Menu::create(npc1_i, NULL);
	npc1->setAnchorPoint(Point(0, 0));
	npc1_i->setTag(NPC1);

	auto npc1_h = Sprite::create("npc1_h.png");
	npc1_h->setAnchorPoint(Point(0, 0));

	npc2_i = MenuItemImage::create("npc2.png", "npc2.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//촌장
	auto npc2 = Menu::create(npc2_i, NULL);
	npc2->setAnchorPoint(Point(0, 0));
	npc2_i->setTag(NPC2);


	auto npc2_h = Sprite::create("npc2_h.png");
	npc2_h->setAnchorPoint(Point(0, 0));

	npc3_i = MenuItemImage::create("npc3.png", "npc3.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//이웃주민
	auto npc3 = Menu::create(npc3_i, NULL);
	npc3->setAnchorPoint(Point(0, 0));
	npc3_i->setTag(NPC3);

	auto npc3_h = Sprite::create("npc3_h.png");
	npc3_h->setAnchorPoint(Point(0, 0));

	npc4_i = MenuItemImage::create("npc4.png", "npc4.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//상점
	auto npc4 = Menu::create(npc4_i, NULL);
	npc4->setAnchorPoint(Point(0, 0));
	npc4_i->setTag(NPC4);


	auto store = Sprite::create("store.png");
	store->setAnchorPoint(Point(0, 0));

	npc5_i = MenuItemImage::create("npc5.png", "npc5.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//대장간
	auto npc5 = Menu::create(npc5_i, NULL);
	npc5->setAnchorPoint(Point(0, 0));
	npc5_i->setTag(NPC5);


	auto upgrade = Sprite::create("upgrade.png");
	upgrade->setAnchorPoint(Point(0, 0));


	ground = Sprite::create("sand1.png");
	ground->setAnchorPoint(Point(0, 0));


	auto magic = MenuItemImage::create("magic1.png", "magic1.png", CC_CALLBACK_1(TopLayer::changeScene, this));
	auto go = Menu::create(magic, NULL);
	go->setAnchorPoint(Point(0.5, 0.5));

	auto magic2 = Sprite::create("magic2.png");
	magic2->setAnchorPoint(Point(0.5, 0.5));
	auto magic2move1 = MoveBy::create(1, Point(0, 30));
	auto magic2move2 = MoveBy::create(1, Point(0, -30));
	auto moveseq1 = Sequence::create(magic2move1, magic2move2, NULL);
	auto remoseq1 = RepeatForever::create(moveseq1);
	magic2->runAction(remoseq1);

	auto magic3 = Sprite::create("magic3.png");
	magic3->setAnchorPoint(Point(0.5, 0.5));
	auto magic3move1 = MoveBy::create(1, Point(0, 20));
	auto magic3move2 = MoveBy::create(1, Point(0, -20));
	auto moveseq2 = Sequence::create(magic3move1, magic3move2, NULL);
	auto remoseq2 = RepeatForever::create(moveseq2);
	magic3->runAction(remoseq2);




	voidNode = ParallaxNode::create();

	voidNode->addChild(npc1_h, 1, Point(1.0f, 0.0f), Point(1500, 340));
	voidNode->addChild(npc2_h, 1, Point(1.0f, 0.0f), Point(3000, 340));
	voidNode->addChild(store, 1, Point(1.0f, 0.0f), Point(4500, 340));
	voidNode->addChild(npc3_h, 1, Point(1.0f, 0.0f), Point(6000, 340));
	voidNode->addChild(upgrade, 1, Point(1.0f, 0.0f), Point(7500, 340));
	voidNode->addChild(ground, 1, Point(1.0f, 0.0f), Point(0, 0));//땅
	voidNode->addChild(npc1, 1, Point(1.0f, 0.0f), Point(1550, 490));//부모님
	voidNode->addChild(npc2, 1, Point(1.0f, 0.0f), Point(3100, 460));//마을촌장
	voidNode->addChild(npc4, 1, Point(1.0f, 0.0f), Point(4550, 490));//상점
	voidNode->addChild(npc3, 1, Point(1.0f, 0.0f), Point(6050, 480));//이웃주민
	voidNode->addChild(npc5, 1, Point(1.0f, 0.0f), Point(7550, 500));//대장간
	voidNode->addChild(go, 1, Point(1.0f, 0.0f), Point(9100, 335));//마법진
	voidNode->addChild(magic3, 1, Point(1.0f, 0.0f), Point(9100, 370));//마법진
	voidNode->addChild(magic2, 1, Point(1.0f, 0.0f), Point(9100, 405));//마법진

	voidNode->setTag(1);

	this->addChild(voidNode, 0);



	isMove = false;
	isLeftPressed = false;
	isRightPressed = false;
	jumpYN = false;


	playerSpr = Sprite::create("player1.png");
	//playerSpr->setPosition(Vec2(390, 860));
	playerSpr->setPosition(Point(200, 480));
	playerSpr->setTag(TAG_PLAYER_SPRITE);

	this->addChild(playerSpr);//여기 this는 TopLayer입니다.
			
							  //this->scheduleUpdate();
	std::string top_uname = dataSingleton::getInstance()->user;
	//plyr_lb = Label::create();
	int lev = pK->jjgetInt("level", top_uname);
	std::string lev_lb = std::to_string(lev);
	plyr_lb = Label::createWithTTF("Lv." + lev_lb + " " + top_uname, "nanumgo.ttf", 15);
	plyr_lb->enableOutline(Color4B::BLACK, 2);
	plyr_lb->setAnchorPoint(Point(0.5, 0));
	plyr_lb->setPosition(Point(80, 310));
	playerSpr->addChild(plyr_lb);

	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(TopLayer::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(TopLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listner, this);




	quest_ing();
	

	auto userLayer = UserLayer::create();//캐릭터 사용 아이템들
	this->addChild(userLayer);


	this->scheduleUpdate();

	return true;
}

void TopLayer::update(float delta)
{
	
	dataSingleton::getInstance()->x = playerSpr->getPositionX();
	dataSingleton::getInstance()->y = playerSpr->getPositionY();
	std::string top_uname1 = dataSingleton::getInstance()->user;
	
	int lev = pK->jjgetInt("level", top_uname1);
	std::string lev_lb = std::to_string(lev);
	plyr_lb->setString("Lv." + lev_lb + " " + top_uname1);

	if (!dataSingleton::getInstance()->isCM) {
		if (!pK->jjgetArray("done", top_uname1, 1)) {
			if (pK->jjgetQint("condition", top_uname1, 1) == pK->jjgetQint("nowing", top_uname1, 1)) {
				npc1_i->removeChild(qming);
				cm = Sprite::create("CM.png");
				cm->setPosition(Point(45, 335));
				cm->setTag(CM);
				npc1_i->addChild(cm);
				dataSingleton::getInstance()->isCM = true;
			}
		}
		else if (!pK->jjgetArray("done", top_uname1, 2)) {
			if (pK->jjgetQint("condition", top_uname1, 2) == pK->jjgetQint("nowing", top_uname1, 2)) {
				npc1_i->removeChild(qming);
				cm = Sprite::create("CM.png");
				cm->setPosition(Point(45, 335));
				cm->setTag(CM);
				npc1_i->addChild(cm);
				dataSingleton::getInstance()->isCM = true;
			}
		}
	}

}
void TopLayer::quest_ing() {
	std::string top_uname2 = dataSingleton::getInstance()->user;
	if (pK->jjgetArray("read", top_uname2, 0) == false) {//첫번째 퀘스틑 읽지 않았다.

		label_num = 0;
		char notice1arr[500];
		WideCharToMultiByte(CP_UTF8, 0, L"촌장님을 클릭해 퀘스트를 받으세요.", -1, notice1arr, 1024, NULL, NULL);
		auto notice1 = Label::createWithTTF(notice1arr, "nanumgo.ttf", 35);
		notice1->setPosition(Point(1000, 800));
		//notice1->enableOutline(Color4B::WHITE);
		notice1->setColor(Color3B(0, 15, 117));

		auto act1 = DelayTime::create(2);
		auto act2 = FadeOut::create(2);
		auto act3 = Sequence::create(act1, act2, CallFuncN::create(CC_CALLBACK_0(TopLayer::changeLabel, this)), NULL);
		notice1->runAction(act3);
		this->addChild(notice1);

		//auto qmx = npc2_i->getPositionX();
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc2_i->addChild(qm);


	}
	else if (pK->jjgetArray("done", top_uname2, 0) == false) {//첫번째 퀘스트는 읽었으나 아직 완료하지 않았다.
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc1_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;

	}
	else if (!pK->jjgetArray("read", top_uname2, 1)) {//두번째 퀘스트의 읽지 않음
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 1) == false) {//두번째 퀘스트를 읽었으나 완료는 아니다.
		if (pK->jjgetQint("condition", top_uname2, 1) == pK->jjgetQint("nowing", top_uname2, 1)) {//조건을 모두 충족은 하였다.
			cm = Sprite::create("CM.png");
			cm->setPosition(Point(45, 335));
			cm->setTag(CM);
			npc1_i->addChild(cm);
			dataSingleton::getInstance()->isCM = true;

		}
		else {//아직 조건 충족도 못했다.
			qming = Sprite::create("QMing.png");
			qming->setPosition(Point(45, 335));
			npc1_i->addChild(qming);
		}
	}
	else if (!pK->jjgetArray("read", top_uname2, 2)) {//세번째 퀘스트를 읽지 않음
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 2) == false) {//세번째 퀘스트를 읽었으나 완료는 아니다.
		if (pK->jjgetQint("condition", top_uname2, 2) == pK->jjgetQint("nowing", top_uname2, 2)) {//조건을 모두 충족은 하였다.
			cm = Sprite::create("CM.png");
			cm->setPosition(Point(45, 335));
			cm->setTag(CM);
			npc1_i->addChild(cm);
			dataSingleton::getInstance()->isCM = true;

		}
		else {//아직 조건 충족도 못했다.
			qming = Sprite::create("QMing.png");
			qming->setPosition(Point(45, 335));
			npc1_i->addChild(qming);
		}
	}
	else if (!pK->jjgetArray("read", top_uname2, 3)) {//네번째 퀘스트를 읽지 않음
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 3) == false) {//네번째 퀘스트를 읽었으나 완료는 아니다.
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc2_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;
	}
	else if (!pK->jjgetArray("read", top_uname2, 4)) {//다섯번째 퀘스트를 읽지 않음
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc2_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 4) == false) {//다섯번째 퀘스트를 읽었으나 완료는 아니다.
		if (pK->jjgetQint("condition", top_uname2, 4) == pK->jjgetQint("nowing", top_uname2, 4)) {//조건을 모두 충족은 하였다.
			cm = Sprite::create("CM.png");
			cm->setPosition(Point(45, 335));
			cm->setTag(CM);
			npc2_i->addChild(cm);
			dataSingleton::getInstance()->isCM = true;

		}
		else {//아직 조건 충족도 못했다.
			qming = Sprite::create("QMing.png");
			qming->setPosition(Point(45, 335));
			npc2_i->addChild(qming);
		}
	}


}
//라벨창
void TopLayer::changeLabel()
{
	//	auto P_right = (Sprite*)this->getChildByTag(P_RIGHT);

	char notice2arr[500];
	WideCharToMultiByte(CP_UTF8, 0, L"오른쪽 방향키를 눌러 이동하세요.", -1, notice2arr, 1024, NULL, NULL);
	notice2 = Label::createWithTTF(notice2arr, "nanumgo.ttf", 35);
	notice2->setPosition(Point(1000, 800));
	notice2->setColor(Color3B(0, 15, 117));
	this->addChild(notice2);

	auto act5 = FadeOut::create(2);
	auto act4 = FadeIn::create(2);
	auto act6 = Sequence::create(act4, act5, NULL);
	auto act7 = RepeatForever::create(act6);
	notice2->runAction(act7);


	//	P_right->setOpacity(200);


}

void TopLayer::questClicked(Ref *sender)
{
	std::string top_uname3 = dataSingleton::getInstance()->user;
	if (dataSingleton::getInstance()->open2 == false)
	{

		dataSingleton::getInstance()->open2 = true;
		auto background = Sprite::create("background.png");
		background->setAnchorPoint(Point(0, 0));
		background->setPosition(Point(0, 0));
		background->setTag(BACK);
		this->addChild(background);

		questwin = Sprite::create("store1.png");
		questwin->setAnchorPoint(Point(0.5, 0.5));
		questwin->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, Director::getInstance()->
			getWinSize().height / 2));
		this->addChild(questwin);
		questwin->setTag(Q_WIN);

		auto exit = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
		auto exit_b = Menu::create(exit, NULL);
		exit_b->setPosition(Point(1350, 850));
		questwin->addChild(exit_b);

		auto npcQ = (MenuItem*)sender;

		switch (npcQ->getTag()) {

		case NPC1_Q: {
			if (pK->jjgetArray("done", top_uname3, 1) == false && pK->jjgetArray("read", top_uname3, 1) == true) {
				auto ep1_2 = MenuItemImage::create("ep1-2.png", "ep1-2_push.png", CC_CALLBACK_1(TopLayer::questText, this));
				ep1_2->setTag(EP1_2);
				auto ep_2 = Menu::create(ep1_2, NULL);
				ep_2->setPosition(Point(270, 793));
				questwin->addChild(ep_2);

				ep1_2_t = Sprite::create("ep1-2_text.png");
				ep1_2_t->setAnchorPoint(Point(0, 1));
				ep1_2_t->setPosition(0, 900);
				ep1_2_t->setVisible(false);
				questwin->addChild(ep1_2_t);


			}
			else if (pK->jjgetArray("done", top_uname3, 2) == false && pK->jjgetArray("read", top_uname3, 2) == true) {
				auto ep1_3 = MenuItemImage::create("ep1-3.png", "ep1-3_push.png", CC_CALLBACK_1(TopLayer::questText, this));
				ep1_3->setTag(EP1_3);
				auto ep_3 = Menu::create(ep1_3, NULL);
				ep_3->setPosition(Point(270, 793));
				questwin->addChild(ep_3);

				ep1_3_t = Sprite::create("ep1-3_text.png");
				ep1_3_t->setAnchorPoint(Point(0, 1));
				ep1_3_t->setPosition(0, 900);
				ep1_3_t->setVisible(false);
				questwin->addChild(ep1_3_t);
			}
			else if (pK->jjgetArray("done", top_uname3, 3) == false && pK->jjgetArray("read", top_uname3, 3) == true) {
				auto ep1_4 = MenuItemImage::create("ep1-4.png", "ep1-4_push.png", CC_CALLBACK_1(TopLayer::questText, this));
				ep1_4->setTag(EP1_4);
				auto ep_4 = Menu::create(ep1_4, NULL);
				ep_4->setPosition(Point(270, 793));
				questwin->addChild(ep_4);

				ep1_4_t = Sprite::create("ep1-4_text.png");
				ep1_4_t->setAnchorPoint(Point(0, 1));
				ep1_4_t->setPosition(0, 900);
				ep1_4_t->setVisible(false);
				questwin->addChild(ep1_4_t);
			}

			break;
		}
		case NPC2_Q: {
			if (pK->jjgetArray("done", top_uname3, 0) == false && pK->jjgetArray("read", top_uname3, 0) == true) {
				auto ep1_1 = MenuItemImage::create("ep1-1.png", "ep1-1_push.png", CC_CALLBACK_1(TopLayer::questText, this));
				ep1_1->setTag(EP1_1);
				auto ep_1 = Menu::create(ep1_1, NULL);
				ep_1->setPosition(Point(270, 793));
				questwin->addChild(ep_1);

				ep1_1_t = Sprite::create("ep1-1_text.png");
				ep1_1_t->setAnchorPoint(Point(0, 1));
				ep1_1_t->setPosition(0, 900);
				ep1_1_t->setVisible(false);
				questwin->addChild(ep1_1_t);
			}
			else if (pK->jjgetArray("done", top_uname3, 4) == false && pK->jjgetArray("read", top_uname3, 4) == true) {
				auto ep1_5 = MenuItemImage::create("ep1-5.png", "ep1-5_push.png", CC_CALLBACK_1(TopLayer::questText, this));
				ep1_5->setTag(EP1_5);
				auto ep_5 = Menu::create(ep1_5, NULL);
				ep_5->setPosition(Point(270, 793));
				questwin->addChild(ep_5);

				ep1_5_t = Sprite::create("ep1-5_text.png");
				ep1_5_t->setAnchorPoint(Point(0, 1));
				ep1_5_t->setPosition(0, 900);
				ep1_5_t->setVisible(false);
				questwin->addChild(ep1_5_t);
			}
			break;
		}
		default: {
			break;
		}
		}


	}


}
void TopLayer::questText(Ref *sender)
{
	std::string top_uname7 = dataSingleton::getInstance()->user;
	auto questTag = (MenuItem*)sender;

	switch (questTag->getTag()) {

	case EP1_1: {

		if (ep1_1_t->isVisible())
			ep1_1_t->setVisible(false);
		else
			ep1_1_t->setVisible(true);
		break;
	}
	case EP1_2: {
		int cond = pK->jjgetQint("condition", top_uname7, 1);
		int now = pK->jjgetQint("nowing", top_uname7, 1);
		std::string conds = std::to_string(cond);
		std::string nows = std::to_string(now);
		auto connow = Label::createWithTTF(nows + " / " + conds, "nanumgo.ttf", 23);
		connow->setPosition(Point(770, 344));
		connow->setVisible(false);
		questwin->addChild(connow);
		if (ep1_2_t->isVisible()) {
			ep1_2_t->setVisible(false);
			connow->setVisible(false);
		}

		else {
			ep1_2_t->setVisible(true);
			connow->setVisible(true);
		}
		break;
	}
	case EP1_3: {
		int cond = pK->jjgetQint("condition", top_uname7, 2);
		int now = pK->jjgetQint("nowing", top_uname7, 2);
		std::string conds = std::to_string(cond);
		std::string nows = std::to_string(now);
		auto connow = Label::createWithTTF(nows + " / " + conds, "nanumgo.ttf", 23);
		connow->setPosition(Point(770, 344));
		connow->setVisible(false);

		if (ep1_3_t->isVisible()) {
			connow->setVisible(false);
			ep1_3_t->setVisible(false);
		}
		else{
			connow->setVisible(true);
			ep1_3_t->setVisible(true);
		}
		break;
	}
	case EP1_4: {

		if (ep1_4_t->isVisible())
			ep1_4_t->setVisible(false);
		else
			ep1_4_t->setVisible(true);
		break;
	}
	case EP1_5: {
		int cond = pK->jjgetQint("condition", top_uname7, 1);
		int now = pK->jjgetQint("nowing", top_uname7, 1);
		std::string conds = std::to_string(cond);
		std::string nows = std::to_string(now);
		auto connow = Label::createWithTTF(nows + " / " + conds, "nanumgo.ttf", 23);
		connow->setPosition(Point(770, 344));
		connow->setVisible(false);

		if (ep1_5_t->isVisible()) {
			connow->setVisible(false);
			ep1_5_t->setVisible(false);
		}
		else {
			connow->setVisible(true);
			ep1_5_t->setVisible(true);
		}
		break;
	}
	default: {
		break;
	}
	}

}

void TopLayer::npcClicked(Ref *sender) {
	std::string top_uname4 = dataSingleton::getInstance()->user;
	if (dataSingleton::getInstance()->open == false) {
		auto npc = (MenuItem*)sender;
		comuwin = Sprite::create("comuwin.png");
		comuwin->setAnchorPoint(Point(1, 0));
		comuwin->setPosition(Point(1920, 0));//0->100
		comuwin->setTag(COMU);
		this->addChild(comuwin);

		auto n = MenuItemImage::create("next.png", "next.png", CC_CALLBACK_1(TopLayer::nextClicked, this));
		next = Menu::create(n, NULL);
		next->setPosition(Point(1400, 80));
		next->setTag(NEXT);



		dataSingleton::getInstance()->open = true;

		switch (npc->getTag()) {

		case NPC1: {
			comupro = Sprite::create("NPC1_mom_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);
			
			char parents[500];
			WideCharToMultiByte(CP_UTF8, 0, L"부모님 사란", -1, parents, 1024, NULL, NULL);
			O_t = Label::createWithTTF(parents, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			comuwin->addChild(O_t);

			if (pK->jjgetArray("read", top_uname4, 0) && !pK->jjgetArray("done", top_uname4, 0)) {//퀘스트1을 읽었으나 아직 완료X


				this->removeChild(notice3);


				dataSingleton::getInstance()->isCM = false;

				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);



				char parentscom[500];
				WideCharToMultiByte(CP_UTF8, 0, L"어서와라. 기다리고 있었단다.  ", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comuwin->addChild(comunication);

				pK->jjsetQint("nowing", top_uname4, 1, 0);
			}
			else if (pK->jjgetArray("done", top_uname4, 0) && !pK->jjgetArray("read", top_uname4, 1)) {//두번째 퀘스트를 읽겠다
			

				auto questO = MenuItemImage::create("okay.png", "okay_push.png", CC_CALLBACK_0(TopLayer::OKClicked, this));
				quest_ok = Menu::create(questO, NULL);
				quest_ok->setScale(0.6);
				quest_ok->setAnchorPoint(Point(0, 0));
				quest_ok->setPosition(Point(1150, 420));
				quest_ok->setVisible(false);
				comuwin->addChild(quest_ok);
				//	quest_ok->setTag(QUEST_O);

				auto questC = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
				auto quest_cancel = Menu::create(questC, NULL);
				quest_cancel->setScale(0.6);
				quest_cancel->setAnchorPoint(Point(0, 0));
				quest_cancel->setPosition(Point(1420, 420));
				comuwin->addChild(quest_cancel);

			

				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"촌장님이랑 대화하는데 급히 불러 미안하구나. \n\n오늘따라 너의 아버지가 너무 늦어서 걱정이 되는구나.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			
				nextnum = 7;
				comuwin->addChild(next);




			}
			else if (!pK->jjgetArray("done", top_uname4, 1) && (pK->jjgetQint("condition", top_uname4, 1) == pK->jjgetQint("nowing", top_uname4, 1))) {//두번째 퀘스트 완료후


		
				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);

		
				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"정말 잘 어울리는 구나.\n\n좋은 장비를 착용할 수록 사냥이 더욱 수월해질테니 장비에도 신경써야한단다.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			}
			else if (pK->jjgetArray("done", top_uname4, 1) && !pK->jjgetArray("read", top_uname4, 2)) {//세번째 퀘스트


				auto questO = MenuItemImage::create("okay.png", "okay_push.png", CC_CALLBACK_0(TopLayer::OKClicked, this));
				quest_ok = Menu::create(questO, NULL);
				quest_ok->setScale(0.6);
				quest_ok->setAnchorPoint(Point(0, 0));
				quest_ok->setPosition(Point(1150, 420));
				comuwin->addChild(quest_ok);
				//	quest_ok->setTag(QUEST_O);

				auto questC = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
				auto quest_cancel = Menu::create(questC, NULL);
				quest_cancel->setScale(0.6);
				quest_cancel->setAnchorPoint(Point(0, 0));
				quest_cancel->setPosition(Point(1420, 420));
				comuwin->addChild(quest_cancel);

			
				
				O_t->setVisible(true);

				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L" 이제 장비를 착용했으니 너의 아버지가 나가신 '마을입구'로 가보거라.\n\n그리고 그 곳에 출연하는 몬스터 5마리를 잡고, 아버지를 찾아보거라. 부탁한다.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);

			}
			else if (!pK->jjgetArray("done", top_uname4, 2) && (pK->jjgetQint("condition", top_uname4, 2) == pK->jjgetQint("nowing", top_uname4, 2))) {//세번째 퀘스트 완료후



				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);

\
				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"무사히 돌아와 줬구나.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			}
			else if (pK->jjgetArray("done", top_uname4, 2) && !pK->jjgetArray("read", top_uname4, 3)) {//네번째 퀘스트


				auto questO = MenuItemImage::create("okay.png", "okay_push.png", CC_CALLBACK_0(TopLayer::OKClicked, this));
				quest_ok = Menu::create(questO, NULL);
				quest_ok->setScale(0.6);
				quest_ok->setAnchorPoint(Point(0, 0));
				quest_ok->setPosition(Point(1150, 420));
				quest_ok->setVisible(false);
				comuwin->addChild(quest_ok);
				//	quest_ok->setTag(QUEST_O);

				auto questC = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
				auto quest_cancel = Menu::create(questC, NULL);
				quest_cancel->setScale(0.6);
				quest_cancel->setAnchorPoint(Point(0, 0));
				quest_cancel->setPosition(Point(1420, 420));
				comuwin->addChild(quest_cancel);

				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"오늘은 그 곳으로 가신다고 했는데 없다니...어찌된 일이지.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				nextnum = 16;
				comuwin->addChild(next);
				comuwin->addChild(comunication);

			}
			else {//새롭게 받을 퀘스트가 없을 때
				auto questbut = MenuItemImage::create("questb.png", "questb_push.png", CC_CALLBACK_1(TopLayer::questClicked, this));
				auto quest = Menu::create(questbut, NULL);
				questbut->setTag(NPC1_Q);
				quest->setScale(0.6);
				quest->setAnchorPoint(Point(0, 0));
				quest->setPosition(Point(1150, 420));
				comuwin->addChild(quest);
				//quest_ok->setTag(QUEST_O);

				auto closebut = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
				auto close = Menu::create(closebut, NULL);
				close->setScale(0.6);
				close->setAnchorPoint(Point(0, 0));
				close->setPosition(Point(1420, 420));
				comuwin->addChild(close);

				char parentscom[500];
				WideCharToMultiByte(CP_UTF8, 0, L"너 자신을 소중히 하거라.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);


			}



			break;
		}
		case NPC2: { // 촌장님

			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);


			char chonjang[500];
			WideCharToMultiByte(CP_UTF8, 0, L"촌장 베인", -1, chonjang, 1024, NULL, NULL);
			O_t = Label::createWithTTF(chonjang, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //외곽선 효과를 주는 함수. 색깔과 두께.

			comuwin->addChild(O_t);

			if (!pK->jjgetArray("read", top_uname4, 0)) { //퀘스트1가 있을 때

				this->removeChild(notice2);
				auto questO = MenuItemImage::create("okay.png", "okay_push.png", CC_CALLBACK_0(TopLayer::OKClicked, this));
				quest_ok = Menu::create(questO, NULL);
				quest_ok->setScale(0.6);
				quest_ok->setAnchorPoint(Point(0, 0));
				quest_ok->setPosition(Point(1150, 420));
				quest_ok->setVisible(false);
				comuwin->addChild(quest_ok);
				//	quest_ok->setTag(QUEST_O);

				auto questC = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
				auto quest_cancel = Menu::create(questC, NULL);
				quest_cancel->setScale(0.6);
				quest_cancel->setAnchorPoint(Point(0, 0));
				quest_cancel->setPosition(Point(1420, 420));
				comuwin->addChild(quest_cancel);
				//	quest_cancel->setTag(QUEST_C);



				char chonjangcom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"자네 왔는가. 그렇지 않아도 자네를 찾아가려고 했었는데 이렇게 와주다니 고맙구나.\n\n신탁에 따라 여행을 떠나기로 했다면서?   ", -1, chonjangcom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comunication->setTag(CO1);
				comuwin->addChild(comunication);

				nextnum = 0;
				comuwin->addChild(next);


			}
			else if (pK->jjgetArray("read", top_uname4, 3) && !pK->jjgetArray("done", top_uname4, 3)) {//퀘스트3을 읽었으나 아직 완료X


				this->removeChild(notice3);


				dataSingleton::getInstance()->isCM = false;

				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);



				char parentscom[500];
				WideCharToMultiByte(CP_UTF8, 0, L"마침 잘 왔네. 자네에게 해줄 말이 있구나", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comuwin->addChild(comunication);

				pK->jjsetQint("nowing", top_uname4, 1, 3);
			}
			else if (pK->jjgetArray("done",top_uname4,3) && !pK->jjgetArray("read", top_uname4, 4)) { //퀘스트5가 있을 때

				auto questO = MenuItemImage::create("okay.png", "okay_push.png", CC_CALLBACK_0(TopLayer::OKClicked, this));
				quest_ok = Menu::create(questO, NULL);
				quest_ok->setScale(0.6);
				quest_ok->setAnchorPoint(Point(0, 0));
				quest_ok->setPosition(Point(1150, 420));
				quest_ok->setVisible(false);
				comuwin->addChild(quest_ok);
				//	quest_ok->setTag(QUEST_O);

				auto questC = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
				auto quest_cancel = Menu::create(questC, NULL);
				quest_cancel->setScale(0.6);
				quest_cancel->setAnchorPoint(Point(0, 0));
				quest_cancel->setPosition(Point(1420, 420));
				comuwin->addChild(quest_cancel);
				//	quest_cancel->setTag(QUEST_C);

				char chonjangcom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"사란에게 들었다. 아직 에반이 돌아오지 않았다고.\n\n그 뿐만 아니라 다른 마을 사람들도 아직 돌아오지 않았다고 하더구나.", -1, chonjangcom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comunication->setTag(CO1);
				comuwin->addChild(comunication);

				nextnum = 18;
				comuwin->addChild(next);


			}
			else if (!pK->jjgetArray("done", top_uname4, 4) && (pK->jjgetQint("condition", top_uname4, 4) == pK->jjgetQint("nowing", top_uname4, 4))) {//다섯번째 퀘스트 완료후


				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);

				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"너라면 해낼 줄 알았다.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			}
			else {//진행할 퀘스트가 없을 때
				auto questbut = MenuItemImage::create("questb.png", "questb_push.png", CC_CALLBACK_1(TopLayer::questClicked, this));
				auto quest = Menu::create(questbut, NULL);
				questbut->setTag(NPC2_Q);
				quest->setScale(0.6);
				quest->setAnchorPoint(Point(0, 0));
				quest->setPosition(Point(1150, 420));
				comuwin->addChild(quest);
				//quest_ok->setTag(QUEST_O);

				auto closebut = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
				auto close = Menu::create(closebut, NULL);
				close->setScale(0.6);
				close->setAnchorPoint(Point(0, 0));
				close->setPosition(Point(1420, 420));
				comuwin->addChild(close);
				//quest_cancel->setTag(QUEST_C);


				char chonjangcom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"빛의 신께서 길을 인도해주실게다.", -1, chonjangcom, 1024, NULL, NULL);
				auto comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);



			}

			break;
		}

		case NPC3: {
			auto questbut = MenuItemImage::create("questb.png", "questb_push.png", CC_CALLBACK_1(TopLayer::questClicked, this));
			auto quest = Menu::create(questbut, NULL);
			questbut->setTag(NPC3_Q);
			quest->setScale(0.6);
			quest->setAnchorPoint(Point(0, 0));
			quest->setPosition(Point(1150, 420));
			comuwin->addChild(quest);
			//quest_ok->setTag(QUEST_O);

			auto closebut = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
			auto close = Menu::create(closebut, NULL);
			close->setScale(0.6);
			close->setAnchorPoint(Point(0, 0));
			close->setPosition(Point(1420, 420));
			comuwin->addChild(close);
			//quest_cancel->setTag(QUEST_C);

			char flowernuna[500];
			WideCharToMultiByte(CP_UTF8, 0, L"이웃주민 레닌", -1, flowernuna, 1024, NULL, NULL);
			O_t = Label::createWithTTF(flowernuna, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //외곽선 효과를 주는 함수. 색깔과 두께.
			
			comuwin->addChild(O_t);

			char flowernunacom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"꽃향기를 맡으면 마음이 진정이 돼.", -1, flowernunacom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(flowernunacom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);

			break;
		}
		case NPC4: {
			comupro = Sprite::create("NPC4_store_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-420, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);
			//진행할 퀘스트가 없을 때
			auto storebut = MenuItemImage::create("buy.png", "buy_push.png", CC_CALLBACK_1(TopLayer::storelayer, this));
			auto store = Menu::create(storebut, NULL);
			storebut->setTag(NPC4_Q);
			store->setScale(0.6);
			store->setAnchorPoint(Point(0, 0));
			store->setPosition(Point(880, 420));
			comuwin->addChild(store);
			//quest_ok->setTag(QUEST_O);

			auto salebut = MenuItemImage::create("saleb.png", "saleb_push.png", CC_CALLBACK_1(TopLayer::salelayer, this));
			auto sale = Menu::create(salebut, NULL);
			salebut->setTag(NPC4_Q);
			sale->setScale(0.6);
			sale->setAnchorPoint(Point(0, 0));
			sale->setPosition(Point(1150, 420));
			comuwin->addChild(sale);

			auto closebut = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
			auto close = Menu::create(closebut, NULL);
			close->setScale(0.6);
			close->setAnchorPoint(Point(0, 0));
			close->setPosition(Point(1420, 420));
			comuwin->addChild(close);
			//quest_cancel->setTag(QUEST_C);

			char storebro[500];
			WideCharToMultiByte(CP_UTF8, 0, L"상인 하론", -1, storebro, 1024, NULL, NULL);
			O_t = Label::createWithTTF(storebro, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //외곽선 효과를 주는 함수. 색깔과 두께.
			
			comuwin->addChild(O_t);

			char storebrocom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"어서와! 없는 건 빼곤 다 있어!", -1, storebrocom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(storebrocom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));

			comuwin->addChild(comunication);

			/*

			}
			auto sLayer = StoreLayer::create();
			this->addChild(sLayer);*/
			break;

		}
		case NPC5: {
			//진행할 퀘스트가 없을 때
			auto questbut = MenuItemImage::create("upgradeb.png", "upgradeb_push.png", CC_CALLBACK_1(TopLayer::questClicked, this));
			auto quest = Menu::create(questbut, NULL);
			questbut->setTag(NPC5_Q);
			quest->setScale(0.6);
			quest->setAnchorPoint(Point(0, 0));
			quest->setPosition(Point(1150, 420));
			comuwin->addChild(quest);
			//quest_ok->setTag(QUEST_O);

			auto closebut = MenuItemImage::create("close.png", "close_push.png", CC_CALLBACK_0(TopLayer::closeClicked, this));
			auto close = Menu::create(closebut, NULL);
			close->setScale(0.6);
			close->setAnchorPoint(Point(0, 0));
			close->setPosition(Point(1420, 420));
			comuwin->addChild(close);
			//quest_cancel->setTag(QUEST_C);

			char dajangjang[500];
			WideCharToMultiByte(CP_UTF8, 0, L"대장장이 턱스", -1, dajangjang, 1024, NULL, NULL);
			O_t = Label::createWithTTF(dajangjang, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //외곽선 효과를 주는 함수. 색깔과 두께.
			
			comuwin->addChild(O_t);

			char dajangjangcom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"하하, 뜨거운 공기로 숨쉴 때, 살아있음을 느끼지!", -1, dajangjangcom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(dajangjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));

			comuwin->addChild(comunication);

			break;
		}

		default: {
			break;
		}
		}
	}

}
void TopLayer::completeClicked() {
	std::string top_uname5 = dataSingleton::getInstance()->user;

	auto qc = Sprite::create("questcomplete.png");
	qc->setAnchorPoint(Point(0.5, 0.5));
	qc->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, 800));
	this->addChild(qc);
	auto fade = FadeOut::create(1.0f);
	auto move = MoveBy::create(3, Point(0, 50));
	auto spaw = Spawn::create(move, fade, NULL);
	qc->runAction(spaw);

	dataSingleton::getInstance()->open = false;
	this->removeChild(getChildByTag(COMU));

	char rwrdexpget[100];
	WideCharToMultiByte(CP_UTF8, 0, L" 경험치 획득", -1, rwrdexpget, 1024, NULL, NULL);
	char rwrdmoneyget[100];
	WideCharToMultiByte(CP_UTF8, 0, L" 크루 획득", -1, rwrdmoneyget, 1024, NULL, NULL);
	char potionget[100];
	WideCharToMultiByte(CP_UTF8, 0, L" 획득", -1, potionget, 1024, NULL, NULL);
	char hppotion[100];
	WideCharToMultiByte(CP_UTF8, 0, L" HP포션(소)X", -1, hppotion, 1024, NULL, NULL);
	char mppotion[100];
	WideCharToMultiByte(CP_UTF8, 0, L" MP포션(소)X", -1, mppotion, 1024, NULL, NULL);

	if (pK->jjgetArray("done", top_uname5, 0) == false) {//퀘스트 1_1 완료

		npc1_i->removeChild(cm);
		dataSingleton::getInstance()->isCM = false;

		auto rwrdexp = pK->jjgetQint("rwrdExp", top_uname5, 0);
		auto rwrdcash = pK->jjgetQint("rwrdcash", top_uname5, 0);
		auto plexp = pK->jjgetInt("exp", top_uname5);
		auto plmoney = pK->jjgetInt("money", top_uname5);

		std::string rwrdexpStr = std::to_string(rwrdexp);
		auto explabel = Label::createWithTTF(rwrdexpStr + rwrdexpget, "nanumgo.ttf", 20);
		explabel->setAnchorPoint(Point(0, 0));
		explabel->setPosition(100, 350);
		this->addChild(explabel);

		auto dte = DelayTime::create(3.0);
		auto fde = FadeOut::create(2.0);
		auto seqe = Sequence::create(dte, fde, NULL);
		explabel->runAction(seqe);

		std::string rwrdmoneyStr = std::to_string(rwrdcash);
		auto moneylabel = Label::createWithTTF(rwrdmoneyStr + rwrdmoneyget, "nanumgo.ttf", 20);
		moneylabel->setAnchorPoint(Point(0, 0));
		moneylabel->setPosition(100, 300);
		this->addChild(moneylabel);

		auto dtm = DelayTime::create(3.0);
		auto fdm = FadeOut::create(2.0);
		auto seqm = Sequence::create(dtm, fdm, NULL);
		moneylabel->runAction(seqm);

		plexp += rwrdexp;
		dataSingleton::getInstance()->pEXP = plexp;
		plmoney += rwrdcash;
		pK->jjsetInt(plexp, "exp", top_uname5);
		pK->jjsetInt(plmoney, "money", top_uname5);
		pK->jjsetArray("done", top_uname5, true, 0);
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);
	}

	else if (pK->jjgetArray("done", top_uname5, 1) == false) {//퀘스트 1_2 완료
		npc1_i->removeChild(cm);
		dataSingleton::getInstance()->isCM = false;

		auto rwrdexp = pK->jjgetQint("rwrdExp", top_uname5, 1);
		auto rwrdcash = pK->jjgetQint("rwrdcash", top_uname5, 1);
		auto plexp = pK->jjgetInt("exp", top_uname5);
		auto plmoney = pK->jjgetInt("money", top_uname5);

		std::string rwrdexpStr = std::to_string(rwrdexp);
		auto explabel = Label::createWithTTF(rwrdexpStr + rwrdexpget, "nanumgo.ttf", 20);
		explabel->setAnchorPoint(Point(0, 0));
		explabel->setPosition(100, 350);
		this->addChild(explabel);

		auto dte = DelayTime::create(3.0);
		auto fde = FadeOut::create(2.0);
		auto seqe = Sequence::create(dte, fde, NULL);
		explabel->runAction(seqe);

		std::string rwrdmoneyStr = std::to_string(rwrdcash);
		auto moneylabel = Label::createWithTTF(rwrdmoneyStr + rwrdmoneyget, "nanumgo.ttf", 20);
		moneylabel->setAnchorPoint(Point(0, 0));
		moneylabel->setPosition(100, 300);
		this->addChild(moneylabel);

		auto dtm = DelayTime::create(3.0);
		auto fdm = FadeOut::create(2.0);
		auto seqm = Sequence::create(dtm, fdm, NULL);
		moneylabel->runAction(seqm);

		plexp += rwrdexp;
		dataSingleton::getInstance()->pEXP = plexp;
		plmoney += rwrdcash;
		pK->jjsetInt(plexp, "exp", top_uname5);
		pK->jjsetInt(plmoney, "money", top_uname5);
		pK->jjsetArray("done", top_uname5, true, 1);

		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);
	}
	else if (pK->jjgetArray("done", top_uname5, 2) == false) {//퀘스트 1_3 완료

		npc1_i->removeChild(cm);
		dataSingleton::getInstance()->isCM = false;

		auto rwrdexp = pK->jjgetQint("rwrdExp", top_uname5, 2);
		auto rwrdcash = pK->jjgetQint("rwrdcash", top_uname5, 2);
		auto rwrdhp = pK->jjgetQint("rwrdhp", top_uname5, 2);
		auto plexp = pK->jjgetInt("exp", top_uname5);
		auto plmoney = pK->jjgetInt("money", top_uname5);
		int plred;
		for (int i = 0; i < 4; i++) {
			auto pid = pK->jjgetAry("keyid", "userpotion", top_uname5, i);
			if (pid == 0) {
				plred = pK->jjgetpArray("holding", top_uname5, i);
				break;
			}
			else if (pid == 999)
				plred = 0;
		}

		std::string rwrdexpStr = std::to_string(rwrdexp);
		auto explabel = Label::createWithTTF(rwrdexpStr + rwrdexpget, "nanumgo.ttf", 20);
		explabel->setAnchorPoint(Point(0, 0));
		explabel->setPosition(100, 350);
		this->addChild(explabel);

		auto dte = DelayTime::create(3.0);
		auto fde = FadeOut::create(2.0);
		auto seqe = Sequence::create(dte, fde, NULL);
		explabel->runAction(seqe);

		std::string rwrdmoneyStr = std::to_string(rwrdcash);
		auto moneylabel = Label::createWithTTF(rwrdmoneyStr + rwrdmoneyget, "nanumgo.ttf", 20);
		moneylabel->setAnchorPoint(Point(0, 0));
		moneylabel->setPosition(100, 300);
		this->addChild(moneylabel);

		auto dtm = DelayTime::create(3.0);
		auto fdm = FadeOut::create(2.0);
		auto seqm = Sequence::create(dtm, fdm, NULL);
		moneylabel->runAction(seqm);


		std::string rwrdhpStr = std::to_string(rwrdhp);
		auto potionlabel = Label::createWithTTF(hppotion + rwrdhpStr + potionget, "nanumgo.ttf", 20);
		potionlabel->setAnchorPoint(Point(0, 0));
		potionlabel->setPosition(100, 250);
		this->addChild(potionlabel);

		auto dtr = DelayTime::create(3.0);
		auto fdr = FadeOut::create(2.0);
		auto seqr = Sequence::create(dtr, fdr, NULL);
		potionlabel->runAction(seqr);

		plexp += rwrdexp;
		dataSingleton::getInstance()->pEXP = plexp;
		plmoney += rwrdcash;
		plred += rwrdhp;
		pK->jjsetInt(plexp, "exp", top_uname5);
		pK->jjsetInt(plmoney, "money", top_uname5);
		
		for (int i = 0; i < 4; i++) {
			auto pid = pK->jjgetAry("keyid", "userpotion", top_uname5, i);
			if (pid == 0) {
				pK->jjsetAry("holding", "userpotion",top_uname5, plred, i);
				break;
			}
			else if (pid == 999) {
				pK->jjsetAry("keyid", "userpotion", top_uname5, plred, 0);
				pK->jjsetAry("holding", "userpotion", top_uname5, plred, i);
				break;
			}
		}
		
		pK->jjsetArray("done", top_uname5, true, 2);

		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);
	}
	else if (pK->jjgetArray("done", top_uname5, 3) == false) {//퀘스트 1_4 완료

		npc2_i->removeChild(cm);
		dataSingleton::getInstance()->isCM = false;

		auto rwrdexp = pK->jjgetQint("rwrdExp", top_uname5, 3);
		auto rwrdcash = pK->jjgetQint("rwrdcash", top_uname5, 3);
		auto rwrdhp = pK->jjgetQint("rwrdhp", top_uname5, 3);
		auto plexp = pK->jjgetInt("exp", top_uname5);
		auto plmoney = pK->jjgetInt("money", top_uname5);
		int plred;
		for (int i = 0; i < 4; i++) {
			auto pid = pK->jjgetAry("keyid", "userpotion", top_uname5, i);
			if (pid == 0) {
				plred = pK->jjgetpArray("holding", top_uname5, i);
				break;
			}
			else if (pid == 999)
				plred = 0;
		}


		std::string rwrdexpStr = std::to_string(rwrdexp);
		auto explabel = Label::createWithTTF(rwrdexpStr + rwrdexpget, "nanumgo.ttf", 20);
		explabel->setAnchorPoint(Point(0, 0));
		explabel->setPosition(100, 350);
		this->addChild(explabel);

		auto dte = DelayTime::create(3.0);
		auto fde = FadeOut::create(2.0);
		auto seqe = Sequence::create(dte, fde, NULL);
		explabel->runAction(seqe);

		std::string rwrdmoneyStr = std::to_string(rwrdcash);
		auto moneylabel = Label::createWithTTF(rwrdmoneyStr + rwrdmoneyget, "nanumgo.ttf", 20);
		moneylabel->setAnchorPoint(Point(0, 0));
		moneylabel->setPosition(100, 300);
		this->addChild(moneylabel);

		auto dtm = DelayTime::create(3.0);
		auto fdm = FadeOut::create(2.0);
		auto seqm = Sequence::create(dtm, fdm, NULL);
		moneylabel->runAction(seqm);


		std::string rwrdhpStr = std::to_string(rwrdhp);
		auto potionlabel = Label::createWithTTF(hppotion + rwrdhpStr + potionget, "nanumgo.ttf", 20);
		potionlabel->setAnchorPoint(Point(0, 0));
		potionlabel->setPosition(100, 250);
		this->addChild(potionlabel);

		auto dtr = DelayTime::create(3.0);
		auto fdr = FadeOut::create(2.0);
		auto seqr = Sequence::create(dtr, fdr, NULL);
		potionlabel->runAction(seqr);

		plexp += rwrdexp;
		dataSingleton::getInstance()->pEXP = plexp;
		plmoney += rwrdcash;
		plred += rwrdhp;
		pK->jjsetInt(plexp, "exp", top_uname5);
		pK->jjsetInt(plmoney, "money", top_uname5);
		for (int i = 0; i < 4; i++) {
			auto pid = pK->jjgetAry("keyid", "userpotion", top_uname5, i);
			if (pid == 0) {
				pK->jjsetAry("holding", "userpotion", top_uname5, plred, i);
				break;
			}
			else if (pid == 999) {
				pK->jjsetAry("keyid", "userpotion", top_uname5, plred, 0);
				pK->jjsetAry("holding", "userpotion", top_uname5, plred, i);
				break;
			}
		}
		pK->jjsetArray("done", top_uname5, true, 3);

		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc2_i->addChild(qm);
	}
	else if (pK->jjgetArray("done", top_uname5, 4) == false) {//퀘스트 1_5 완료

		npc2_i->removeChild(cm);
		dataSingleton::getInstance()->isCM = false;

		auto rwrdexp = pK->jjgetQint("rwrdExp", top_uname5, 4);
		auto rwrdcash = pK->jjgetQint("rwrdcash", top_uname5, 4);
		auto rwrdhp = pK->jjgetQint("rwrdhp", top_uname5, 4);
		auto plexp = pK->jjgetInt("exp", top_uname5);
		auto plmoney = pK->jjgetInt("money", top_uname5);
		int plred;
		for (int i = 0; i < 4; i++) {
			auto pid = pK->jjgetAry("keyid", "userpotion", top_uname5, i);
			if (pid == 0) {
				plred = pK->jjgetpArray("holding", top_uname5, i);
				break;
			}
			else if (pid == 999)
				plred = 0;
		}


		std::string rwrdexpStr = std::to_string(rwrdexp);
		auto explabel = Label::createWithTTF(rwrdexpStr + rwrdexpget, "nanumgo.ttf", 20);
		explabel->setAnchorPoint(Point(0, 0));
		explabel->setPosition(100, 350);
		this->addChild(explabel);

		auto dte = DelayTime::create(3.0);
		auto fde = FadeOut::create(2.0);
		auto seqe = Sequence::create(dte, fde, NULL);
		explabel->runAction(seqe);

		std::string rwrdmoneyStr = std::to_string(rwrdcash);
		auto moneylabel = Label::createWithTTF(rwrdmoneyStr + rwrdmoneyget, "nanumgo.ttf", 20);
		moneylabel->setAnchorPoint(Point(0, 0));
		moneylabel->setPosition(100, 300);
		this->addChild(moneylabel);

		auto dtm = DelayTime::create(3.0);
		auto fdm = FadeOut::create(2.0);
		auto seqm = Sequence::create(dtm, fdm, NULL);
		moneylabel->runAction(seqm);


		std::string rwrdhpStr = std::to_string(rwrdhp);
		auto potionlabel = Label::createWithTTF(hppotion + rwrdhpStr + potionget, "nanumgo.ttf", 20);
		potionlabel->setAnchorPoint(Point(0, 0));
		potionlabel->setPosition(100, 250);
		this->addChild(potionlabel);

		auto dtr = DelayTime::create(3.0);
		auto fdr = FadeOut::create(2.0);
		auto seqr = Sequence::create(dtr, fdr, NULL);
		potionlabel->runAction(seqr);

		plexp += rwrdexp;
		dataSingleton::getInstance()->pEXP = plexp;
		plmoney += rwrdcash;
		plred += rwrdhp;
		pK->jjsetInt(plexp, "exp", top_uname5);
		pK->jjsetInt(plmoney, "money", top_uname5);
		for (int i = 0; i < 4; i++) {
			auto pid = pK->jjgetAry("keyid", "userpotion", top_uname5, i);
			if (pid == 0) {
				pK->jjsetAry("holding", "userpotion", top_uname5, plred, i);
				break;
			}
			else if (pid == 999) {
				pK->jjsetAry("keyid", "userpotion", top_uname5, plred, 0);
				pK->jjsetAry("holding", "userpotion", top_uname5, plred, i);
				break;
			}
		}
		pK->jjsetArray("done", top_uname5, true, 4);

	/*	qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);*/
	}
}
void TopLayer::closeClicked() {
	//if (dataSingleton::getInstance()->open2 == true) {
	dataSingleton::getInstance()->open2 = false;
	this->removeChild(getChildByTag(Q_WIN));
	this->removeChildByTag(BACK);
	//}
	//else if (dataSingleton::getInstance()->open == true) {
	dataSingleton::getInstance()->open = false;
	this->removeChild(getChildByTag(COMU));
	//}
}

void TopLayer::OKClicked()//퀘스트 수락
{
	std::string top_uname6 = dataSingleton::getInstance()->user;
	dataSingleton::getInstance()->open = false;

	this->removeChild(getChildByTag(COMU));//창을 삭제한다.


	if (!pK->jjgetArray("read", top_uname6, 0)) {//첫번째 퀘스트를 읽은 것이라면
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc1_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // 닫혀 있는 책 이미지 삭제.
		npc2_i->removeChild(qm);
		this->removeChild(notice2);



		pK->jjsetArray("read", top_uname6, true, 0);//첫번째 퀘스트를 읽음

												//세번째 공지

		char notice3arr[500];
		WideCharToMultiByte(CP_UTF8, 0, L"부모님을 클릭해 퀘스트를 완료하세요.", -1, notice3arr, 1024, NULL, NULL);
		notice3 = Label::createWithTTF(notice3arr, "nanumgo.ttf", 35);
		notice3->setPosition(Point(1000, 800));
		notice3->setColor(Color3B(0, 15, 117));
		this->addChild(notice3);

		auto act5 = FadeOut::create(2);
		auto act4 = FadeIn::create(2);
		auto act6 = Sequence::create(act4, act5, NULL);
		auto act7 = RepeatForever::create(act6);

		notice3->runAction(act7);


	}
	else if (!pK->jjgetArray("read", top_uname6, 1)) {//두번째 퀘스트를 읽은 것이라면
		//아이템 부여
		pK->jjsetAry("keyid", "userweapon", top_uname6, 0, 0);
		pK->jjsetAry("holding", "userweapon", top_uname6, 1, 0);

		qming = Sprite::create("QMing.png");
		qming->setPosition(Point(45, 335));
		qming->setTag(QMING);
		npc1_i->addChild(qming);
		npc1_i->removeChild(qm);
		pK->jjsetArray("read", top_uname6, true, 1);//두번째 퀘스트를 읽음

	}
	else if (!pK->jjgetArray("read", top_uname6, 2)) {//세번째 퀘스트를 읽은 것이라면
		qming = Sprite::create("QMing.png");
		qming->setPosition(Point(45, 335));
		qming->setTag(QMING);
		npc1_i->addChild(qming);
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // 닫혀 있는 책 이미지 삭제.
		npc1_i->removeChild(qm);

		pK->jjsetArray("read", top_uname6, true, 2);//첫번째 퀘스트를 읽음

												//세번째 공지
		label_num = 2;
		char notice5arr[500];
		WideCharToMultiByte(CP_UTF8, 0, L"마을 오른쪽 끝으로 이동해 '마을입구' 던전에 입장하세요.", -1, notice5arr, 1024, NULL, NULL);
		notice5 = Label::createWithTTF(notice5arr, "nanumgo.ttf", 35);
		notice5->setPosition(Point(1000, 800));
		notice5->setColor(Color3B(0, 15, 117));
		this->addChild(notice5);


		auto act8 = FadeOut::create(2);
		auto act9 = FadeIn::create(2);
		auto act10 = Sequence::create(act8, act9, NULL);
		auto act11 = RepeatForever::create(act10);
		notice5->runAction(act11);


	}
	else if (!pK->jjgetArray("read", top_uname6, 3)) {//네번째 퀘스트를 읽은 것이라면
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc2_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // 닫혀 있는 책 이미지 삭제.
		npc1_i->removeChild(qm);
		pK->jjsetArray("read", top_uname6, true, 3);
	}

	else if (!pK->jjgetArray("read", top_uname6, 4)) {//다섯번째 퀘스트를 읽은 것이라면
		qming = Sprite::create("QMing.png");
		qming->setPosition(Point(45, 335));
		qming->setTag(QMING);
		npc2_i->addChild(qming);
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // 닫혀 있는 책 이미지 삭제.
		npc2_i->removeChild(qm);

		pK->jjsetArray("read", top_uname6, true, 4);//첫번째 퀘스트를 읽음
	}

}


void TopLayer::nextClicked(Ref *sender)
{
	comuwin->removeChild(comunication, 1);
	comuwin->removeChild(comupro,0);
	switch (nextnum)
	{
	case 0: {
		comupro = Sprite::create("NPC2_chon_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);
		char chonjangcom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"아직 너의 어릴 때 모습이 아른거리는데...\n\n벌써 이렇게 혼자 여행을 떠날 정도로 훌쩍 커버렸구나.", -1, chonjangcom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);

		nextnum = 1;
		break;
	}
	case 1: {
		O_t->setVisible(false);
		comupro = Sprite::create("man_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);

		char chonjangcom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"그러게요. 한 번도 마을 주변을 벗어난 본 적이 없어 많이 걱정돼요. \n\n게다가 아직 신탁에서 말하는 '빛의 색을 가진 자'가 저인지에 대해선 자신도 없고요.", -1, chonjangcom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);

		nextnum = 2;

		break;
	}
	case 2: {
		O_t->setVisible(true);
		comupro = Sprite::create("NPC2_chon_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);
		char chonjangcom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"얘야, 나는 네가 자신을 가졌으면 좋겠구나. \n\n네가 그 빛나는 머리카락을 가진 것도,\n\n빛의 신을 섬기는 이 마을에 온 것도 다 이유가 있어서겠지", -1, chonjangcom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);

		nextnum = 3;

		break;
	}
	case 3: {

		comupro = Sprite::create("NPC2_chon_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);

		char chonjangcom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"그리고 인간인 네가‘마력’을 지닌 것도 우연은 아니라고 생각한다. \n\n부디 너 자신을 믿었으면 좋겠구나.\n\n그래야 앞으로 시작할 여행이 조금이라도 순탄하지 않겠느냐", -1, chonjangcom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);

		nextnum = 4;

		break;

	}
	case 4: {
		O_t->setVisible(false);
		comupro = Sprite::create("man_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);
		char chonjangcom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"네, 명심할게요. 촌장님 말씀처럼 이 모든 것이 우연이 아니라면\n\n신탁에 나온 것처럼 미약하게라도 이 세계에 도움이 될 수 있으면 좋겠습니다.", -1, chonjangcom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);

		nextnum = 5;

		break;

	}
	case 5: {
		O_t->setVisible(true);
		comupro = Sprite::create("NPC2_chon_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);
		char chonjangcom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"그래, 너라면 할 수 있을게다. 저기 너의 어머니가 너를 급히 찾는 듯 하구나. 얼른 가보거라.\n\n한동안 부모님 얼굴 못 볼 테니 많이 대화 나누고 잘 다녀오거라.", -1, chonjangcom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);

		nextnum = 6;

		break;
	}
	case 6: {
		comupro = Sprite::create("NPC2_chon_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);
		char chonjangcom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"하리온의 축복이 함께 하길.", -1, chonjangcom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);
		next->setVisible(false);
		quest_ok->setVisible(true);
		break;

	}
	case 7: {

		comupro = Sprite::create("NPC1_mom_normal.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);
		char parentscom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"너도 알다시피 최근에 몬스터들이 폭주하여 여러 마을에 피해를 주고 있단다.\n\n우리 마을은 용병출신이 너의 아버지께서 지켜주고 있고.", -1, parentscom, 1024, NULL, NULL);

		comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);
		
		nextnum = 8;
		break;

			}
	case 8: {

		comupro = Sprite::create("NPC1_mom_sad.png");
		comupro->setAnchorPoint(Point(0, 0));
		comupro->setPosition(Point(-345, 0));
		comupro->setScale(0.8);
		comuwin->addChild(comupro);
		char parentscom[1000];
		WideCharToMultiByte(CP_UTF8, 0, L"그런데 그이가 말하길 신탁이 내려온 뒤로\n\n마을 주변의 몬스터들의 분위기가 심상치 않다고 하더구나", -1, parentscom, 1024, NULL, NULL);
		comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
		comunication->setAnchorPoint(Point(0, 0));
		comunication->setPosition(Point(210, 0));
		comuwin->addChild(comunication);

		nextnum = 9;

		break;

	}
		case 9: {
			comupro = Sprite::create("NPC1_mom_sad.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"평소엔 돌아오시고도 남았을텐데...\n\n게다가 곧 해가 질 시간이라 걱정이구나.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);

		
			nextnum = 10;

			break;

			}
		case 10: {
			O_t->setVisible(false);
			comupro = Sprite::create("man_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);


			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"그러면 제가 얼른 아버지를 찾으러 나갔다 오겠습니다.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);

			nextnum = 11;
			break;

		}
		case 11: {
			O_t->setVisible(true);
			comupro = Sprite::create("NPC1_mom_angle.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"혼자선 안된다. 위험해. \n\n아버지와 함께 나간 마을분들도 아직 다 돌아오시지 않아\n\n현재 마을에 너와 함께 같이 가줄 수 있는 분들이 없구나.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);


			nextnum = 12;
			break;

			}
		case 12: {
			O_t->setVisible(false);
			comupro = Sprite::create("man_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"전 괜찮습니다, 어머니. 앞으로 여행하는 동안 위험한 몬스터를 마주칠 수도 있는데\n\n마을 주변 몬스터 조차 혼자 해결하지 못하면 안되잖아요.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);

			nextnum = 13;
			break;

		}
		case 13: {

			comupro = Sprite::create("man_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"그리고 평소에 아버지랑 함께 몬스터 토벌하고 다녔으니 혼자서도 괜찮습니다.\n\n시간을 지체할수록 아버지가 더욱 위험해질 수 있으니 보내주세요.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);

			nextnum = 14;
			break;
		}
		case 14: {
			O_t->setVisible(true);
			comupro = Sprite::create("NPC1_mom_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"...알았다.하여튼 고집은 여전하구나.너 말처럼 지체할 시간이 없구나.\n\n대신 위험한 듯 싶으면 바로 돌아오거라.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);

			nextnum = 15;
			break;
		}
		case 15: {
			comupro = Sprite::create("NPC1_mom_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"그리고 가기 전에 이걸 받거라\n\n아버지가 너의 여행을 위해 턱스씨께 부탁해 만든 것들이다. 우선 이것부터 착용해보거라.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			next->setVisible(false);
			quest_ok->setVisible(true);
			break;
		}
		case 16: {
			comupro = Sprite::create("NPC1_mom_sad.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			quest_ok->setVisible(true);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"더 걱정이구나. 혹시 촌장님께서 뭔가를 알고 계실지 모르니 가보지 않겠니?", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			next->setVisible(false);
			nextnum = 17;

			break;
		}
		case 17: {
			comupro = Sprite::create("NPC1_mom_noraml.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			quest_ok->setVisible(true);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"걱정이구나. 혹시 촌장님께서 뭔가를 알고 계실지 모르니 가보지 않겠니?", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			next->setVisible(false);
			nextnum = 18;

			break;
		}
		case 18: {
			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"마을 상황이 좋지 않구나.\n\n마을 입구에 아무것도 없더냐?", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 19;

			break;
		}
		case 19: {
			O_t->setVisible(false);
			comupro = Sprite::create("man_sad.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"네. 그래서 마을입구에 가봤는데 아무도 없었습니다. 흔적 조차요.\n\n혹시 촌장님께서 아버지에게 들으신게 없으십니까?", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 20;

			break;
		}
		case 20: {
			O_t->setVisible(true);
			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"...아무래도 그 소문이 신경쓰이는구나.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 21;

			break;
		}
		case 21: {
			O_t->setVisible(false);
			comupro = Sprite::create("man_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"소문...이요?", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 22;

			break;
		}
		case 22: {
			O_t->setVisible(true);
			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"그래. '플레투스 숲'에 '사람을 잡아먹는 식물'이 있다는 소문이 돌고 있단다.\n\n최근부터 그 숲에 기묘한 울음소리가 들린다고 하는데...\n\n아무래도 에반은 그 숲에 간 듯 하구나.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 23;

			break;
		}
		case 23: {
			O_t->setVisible(false);
			comupro = Sprite::create("man_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"사람을 잡아먹는 식물이요?", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 24;

			break;
		}
		case 24: {
			O_t->setVisible(true);
			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"에반은 아마 '만드라곤'이라는 몬스터의 소행같다고 하더구나.\n\n에반이 그 몬스터를 토벌할 거라고 하던데 아무래도 오늘 간 것 같구나.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 25;

			break;
		}
		case 25: {
			O_t->setVisible(false);
			comupro = Sprite::create("man_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"...촌장님, 저...", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 26;

			break;
		}
		case 26: {
			O_t->setVisible(true);
			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);

			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"말하지 않아도 안다. 말리지 않으마. 이것 또한 운명이고 경험이 될테지.\n\n'플레투스 숲'은 '마을 입구'에서 깊숙히 들어가면 된단다.\n\n단, 위험하다 싶으면 바로 돌아오거라.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 27;

			break;
		}
		case 27: {
			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);
			
			char parentscom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"가서 '만드라곤'을 사냥하고, 에반을 찾아보거라.", -1, parentscom, 1024, NULL, NULL);
			comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
			comunication->setAnchorPoint(Point(0, 0));
			comunication->setPosition(Point(210, 0));
			comuwin->addChild(comunication);
			nextnum = 28;

			next->setVisible(false);
			quest_ok->setVisible(true);

			break;
		}
			
	default: {
		break;
	}
	}


}

void TopLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto player = (Sprite*)this->getChildByTag(TAG_PLAYER_SPRITE);


	switch (keyCode) {//키 코드값 확인
	case EventKeyboard::KeyCode::KEY_P:
	{
		if (!dataSingleton::getInstance()->winopen) {
			auto itemLayer = statuswinLayer::create();
			this->addChild(itemLayer);
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_I:
	{
		if (!dataSingleton::getInstance()->winopen) {
			auto itemLayer = itemwinLayer::create();
			this->addChild(itemLayer);
		}

		break;
	}

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW://왼쪽
	{
		isLeftPressed = true;
		isRightPressed = false;
		startMovingBackground();
		playerSpr->stopAllActions();

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1);


		animation->addSpriteFrameWithFile("p1.png");
		animation->addSpriteFrameWithFile("p2.png");
		animation->addSpriteFrameWithFile("p3.png");
		animation->addSpriteFrameWithFile("p4.png");
		animation->addSpriteFrameWithFile("p5.png");
		animation->addSpriteFrameWithFile("p6.png");
		animation->addSpriteFrameWithFile("p7.png");
		animation->addSpriteFrameWithFile("p8.png");
		auto animate = Animate::create(animation);
		auto act = RepeatForever::create(animate);
		playerSpr->runAction(act);
		act->setTag(TAG_SPRITE_PLAYER_ACTION_LEFT);

		moveBackground(1.0);




		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW://오른쪽
	{

		isLeftPressed = false;
		isRightPressed = true;
		startMovingBackground();
		playerSpr->stopAllActions();

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1);

		animation->addSpriteFrameWithFile("p1.png");
		animation->addSpriteFrameWithFile("p2.png");
		animation->addSpriteFrameWithFile("p3.png");
		animation->addSpriteFrameWithFile("p4.png");
		animation->addSpriteFrameWithFile("p5.png");
		animation->addSpriteFrameWithFile("p6.png");
		animation->addSpriteFrameWithFile("p7.png");
		animation->addSpriteFrameWithFile("p8.png");
		auto animate = Animate::create(animation);
		auto act = RepeatForever::create(animate);
		playerSpr->runAction(act);
		act->setTag(TAG_SPRITE_PLAYER_ACTION_RIGHT);

		moveBackground(1.0);


		break;
	}

	default:
		break;
	}

}

void TopLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//아래는 태그를 통해 스프라이트를 가져올 수 있는 참고용 코드입니다.
	//auto player = (Sprite*)this->getChildByTag(TAG_PLAYER_SPRITE);


	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A: {
		break;
	}
	case EventKeyboard::KeyCode::KEY_UP_ARROW: {
		isUpPressed = false;
		//태그를 위해 애니메이션을 삭제하기 위한 참고용 코드입니다.
		//auto action = (Action*)player->getActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
		//player->getActionManager()->removeAction(action);
		break;
	}



	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
		isLeftPressed = false;
		//걷기 애니메이션을 위한 코드입니다.
		auto action = (Action*)playerSpr->getActionByTag(TAG_SPRITE_PLAYER_ACTION_LEFT);
		playerSpr->getActionManager()->removeAction(action);
		if (isRightPressed == false)
			stopMovingBackground();

		break;
	}

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
		//걷기 애니메이션을 위한 코드입니다.
		isRightPressed = false;
		auto action = (Action*)playerSpr->getActionByTag(TAG_SPRITE_PLAYER_ACTION_RIGHT);
		playerSpr->getActionManager()->removeAction(action);
		if (isLeftPressed == false)
			stopMovingBackground();

		break;
	}
	default:
		break;
	}
	if (isRightPressed == false && isLeftPressed == false)
		playerSpr->setTexture(Director::getInstance()->getTextureCache()->addImage("player1.png"));

}

void TopLayer::startMovingBackground()
{
	if (isLeftPressed == true && isRightPressed == true)
		return;//void인데 어떻게 리턴이 되는지 의문...? 뭔가 예외확인을 해주는 것 같은.. 하나만 f면 if빠져나감..
			   //   log("start moving");
	this->schedule(schedule_selector(TopLayer::moveBackground));//스케쥴링 시작
}

void TopLayer::stopMovingBackground()
{
	this->unschedule(schedule_selector(TopLayer::moveBackground));
}

void TopLayer::moveBackground(float t)
{

	auto moveStep = 13;

	if (isLeftPressed)//왼쪽이면 -6
	{
		moveStep = -13;

		playerSpr->setFlippedX(true);
		//좌우 반전 함수.
	}
	else//오른쪽이면 6
	{
		moveStep = 13;

		playerSpr->setFlippedX(false);
		//좌우 반전 함수.
	}
	auto newPos = Point(playerSpr->getPosition().x, playerSpr->getPosition().y);
	auto newPos2 = Point(voidNode->getPosition().x, voidNode->getPosition().y);
	float f = voidNode->getPositionX();

	if (isRightPressed) {
		if (newPos.x < 20) {
			newPos.x = 20;
		}
		else if (newPos.x > 0 && newPos.x < 960) {
			newPos.x += moveStep;
		}
		else if (newPos.x > 1900) {
			newPos.x = 1900;
		}
		else {
			if (f > -7680) {
				newPos2.x -= moveStep;
			}
			else {
				newPos.x += moveStep;
			}
		}
	}
	else if (isLeftPressed) {
		if (newPos.x > 960 && newPos.x <= 1900) {
			newPos.x += moveStep;
		}
		else if (newPos.x < 20) {
			newPos.x = 20;
		}
		else {
			if (f < 0) {
				newPos2.x -= moveStep;
			}
			else {
				newPos.x += moveStep;
			}
		}
	}


	playerSpr->setPosition(newPos);
	float xx = playerSpr->getPositionX();
	float yy = playerSpr->getPositionY();
	dataSingleton::getInstance()->x = xx;
	dataSingleton::getInstance()->y = yy;

	voidNode->setPosition(newPos2);
	dataSingleton::getInstance()->groundx = newPos2.x;
	gx = dataSingleton::getInstance()->groundx;

}

void TopLayer::storelayer(Ref* Sender) {


	auto StoreLayer = StoreLayer::create();
	this->addChild(StoreLayer);

}

void TopLayer::salelayer(Ref* Sender) {


	auto Salelayer = StoresaleLayer::create();
	this->addChild(Salelayer);

}

void TopLayer::upgradelayer(Ref* Sender) {


	auto UpgradeLayer = UpgradeLayer::create();
	this->addChild(UpgradeLayer);

}



void TopLayer::changeScene(Ref* Sender)
{
	this->stopAllActions();
	Director::getInstance()->pushScene(DungeonmapScene::createScene());
}


