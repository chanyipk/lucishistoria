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

	npc1_i = MenuItemImage::create("npc1_Q.png", "npc1_Q.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//�θ��
	npc1 = Menu::create(npc1_i, NULL);
	npc1->setAnchorPoint(Point(0, 0));
	npc1_i->setTag(NPC1);

	auto npc1_h = Sprite::create("npc1_h.png");
	npc1_h->setAnchorPoint(Point(0, 0));

	npc2_i = MenuItemImage::create("npc2.png", "npc2.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//����
	auto npc2 = Menu::create(npc2_i, NULL);
	npc2->setAnchorPoint(Point(0, 0));
	npc2_i->setTag(NPC2);


	auto npc2_h = Sprite::create("npc2_h.png");
	npc2_h->setAnchorPoint(Point(0, 0));

	npc3_i = MenuItemImage::create("npc3.png", "npc3.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//�̿��ֹ�
	auto npc3 = Menu::create(npc3_i, NULL);
	npc3->setAnchorPoint(Point(0, 0));
	npc3_i->setTag(NPC3);

	auto npc3_h = Sprite::create("npc3_h.png");
	npc3_h->setAnchorPoint(Point(0, 0));

	npc4_i = MenuItemImage::create("npc4.png", "npc4.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//����
	auto npc4 = Menu::create(npc4_i, NULL);
	npc4->setAnchorPoint(Point(0, 0));
	npc4_i->setTag(NPC4);


	auto store = Sprite::create("store.png");
	store->setAnchorPoint(Point(0, 0));

	npc5_i = MenuItemImage::create("npc5.png", "npc5.png", CC_CALLBACK_1(TopLayer::npcClicked, this));//���尣
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
	voidNode->addChild(ground, 1, Point(1.0f, 0.0f), Point(0, 0));//��
	voidNode->addChild(npc1, 1, Point(1.0f, 0.0f), Point(1550, 490));//�θ��
	voidNode->addChild(npc2, 1, Point(1.0f, 0.0f), Point(3100, 460));//��������
	voidNode->addChild(npc4, 1, Point(1.0f, 0.0f), Point(4550, 490));//����
	voidNode->addChild(npc3, 1, Point(1.0f, 0.0f), Point(6050, 480));//�̿��ֹ�
	voidNode->addChild(npc5, 1, Point(1.0f, 0.0f), Point(7550, 500));//���尣
	voidNode->addChild(go, 1, Point(1.0f, 0.0f), Point(9100, 335));//������
	voidNode->addChild(magic3, 1, Point(1.0f, 0.0f), Point(9100, 370));//������
	voidNode->addChild(magic2, 1, Point(1.0f, 0.0f), Point(9100, 405));//������

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

	this->addChild(playerSpr);//���� this�� TopLayer�Դϴ�.
			
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
	

	auto userLayer = UserLayer::create();//ĳ���� ��� �����۵�
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
	if (pK->jjgetArray("read", top_uname2, 0) == false) {//ù��° �����z ���� �ʾҴ�.

		label_num = 0;
		char notice1arr[500];
		WideCharToMultiByte(CP_UTF8, 0, L"������� Ŭ���� ����Ʈ�� ��������.", -1, notice1arr, 1024, NULL, NULL);
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
	else if (pK->jjgetArray("done", top_uname2, 0) == false) {//ù��° ����Ʈ�� �о����� ���� �Ϸ����� �ʾҴ�.
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc1_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;

	}
	else if (!pK->jjgetArray("read", top_uname2, 1)) {//�ι�° ����Ʈ�� ���� ����
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 1) == false) {//�ι�° ����Ʈ�� �о����� �Ϸ�� �ƴϴ�.
		if (pK->jjgetQint("condition", top_uname2, 1) == pK->jjgetQint("nowing", top_uname2, 1)) {//������ ��� ������ �Ͽ���.
			cm = Sprite::create("CM.png");
			cm->setPosition(Point(45, 335));
			cm->setTag(CM);
			npc1_i->addChild(cm);
			dataSingleton::getInstance()->isCM = true;

		}
		else {//���� ���� ������ ���ߴ�.
			qming = Sprite::create("QMing.png");
			qming->setPosition(Point(45, 335));
			npc1_i->addChild(qming);
		}
	}
	else if (!pK->jjgetArray("read", top_uname2, 2)) {//����° ����Ʈ�� ���� ����
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 2) == false) {//����° ����Ʈ�� �о����� �Ϸ�� �ƴϴ�.
		if (pK->jjgetQint("condition", top_uname2, 2) == pK->jjgetQint("nowing", top_uname2, 2)) {//������ ��� ������ �Ͽ���.
			cm = Sprite::create("CM.png");
			cm->setPosition(Point(45, 335));
			cm->setTag(CM);
			npc1_i->addChild(cm);
			dataSingleton::getInstance()->isCM = true;

		}
		else {//���� ���� ������ ���ߴ�.
			qming = Sprite::create("QMing.png");
			qming->setPosition(Point(45, 335));
			npc1_i->addChild(qming);
		}
	}
	else if (!pK->jjgetArray("read", top_uname2, 3)) {//�׹�° ����Ʈ�� ���� ����
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc1_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 3) == false) {//�׹�° ����Ʈ�� �о����� �Ϸ�� �ƴϴ�.
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc2_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;
	}
	else if (!pK->jjgetArray("read", top_uname2, 4)) {//�ټ���° ����Ʈ�� ���� ����
		qm = Sprite::create("QM.png");
		qm->setPosition(Point(45, 335));
		qm->setTag(QM);
		npc2_i->addChild(qm);

	}
	else if (pK->jjgetArray("done", top_uname2, 4) == false) {//�ټ���° ����Ʈ�� �о����� �Ϸ�� �ƴϴ�.
		if (pK->jjgetQint("condition", top_uname2, 4) == pK->jjgetQint("nowing", top_uname2, 4)) {//������ ��� ������ �Ͽ���.
			cm = Sprite::create("CM.png");
			cm->setPosition(Point(45, 335));
			cm->setTag(CM);
			npc2_i->addChild(cm);
			dataSingleton::getInstance()->isCM = true;

		}
		else {//���� ���� ������ ���ߴ�.
			qming = Sprite::create("QMing.png");
			qming->setPosition(Point(45, 335));
			npc2_i->addChild(qming);
		}
	}


}
//��â
void TopLayer::changeLabel()
{
	//	auto P_right = (Sprite*)this->getChildByTag(P_RIGHT);

	char notice2arr[500];
	WideCharToMultiByte(CP_UTF8, 0, L"������ ����Ű�� ���� �̵��ϼ���.", -1, notice2arr, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�θ�� ���", -1, parents, 1024, NULL, NULL);
			O_t = Label::createWithTTF(parents, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			comuwin->addChild(O_t);

			if (pK->jjgetArray("read", top_uname4, 0) && !pK->jjgetArray("done", top_uname4, 0)) {//����Ʈ1�� �о����� ���� �Ϸ�X


				this->removeChild(notice3);


				dataSingleton::getInstance()->isCM = false;

				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);



				char parentscom[500];
				WideCharToMultiByte(CP_UTF8, 0, L"��Ͷ�. ��ٸ��� �־��ܴ�.  ", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comuwin->addChild(comunication);

				pK->jjsetQint("nowing", top_uname4, 1, 0);
			}
			else if (pK->jjgetArray("done", top_uname4, 0) && !pK->jjgetArray("read", top_uname4, 1)) {//�ι�° ����Ʈ�� �аڴ�
			

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
				WideCharToMultiByte(CP_UTF8, 0, L"������̶� ��ȭ�ϴµ� ���� �ҷ� �̾��ϱ���. \n\n���õ��� ���� �ƹ����� �ʹ� �ʾ ������ �Ǵ±���.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			
				nextnum = 7;
				comuwin->addChild(next);




			}
			else if (!pK->jjgetArray("done", top_uname4, 1) && (pK->jjgetQint("condition", top_uname4, 1) == pK->jjgetQint("nowing", top_uname4, 1))) {//�ι�° ����Ʈ �Ϸ���


		
				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);

		
				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"���� �� ��︮�� ����.\n\n���� ��� ������ ���� ����� ���� ���������״� ��񿡵� �Ű����Ѵܴ�.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			}
			else if (pK->jjgetArray("done", top_uname4, 1) && !pK->jjgetArray("read", top_uname4, 2)) {//����° ����Ʈ


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
				WideCharToMultiByte(CP_UTF8, 0, L" ���� ��� ���������� ���� �ƹ����� ������ '�����Ա�'�� �����Ŷ�.\n\n�׸��� �� ���� �⿬�ϴ� ���� 5������ ���, �ƹ����� ã�ƺ��Ŷ�. ��Ź�Ѵ�.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);

			}
			else if (!pK->jjgetArray("done", top_uname4, 2) && (pK->jjgetQint("condition", top_uname4, 2) == pK->jjgetQint("nowing", top_uname4, 2))) {//����° ����Ʈ �Ϸ���



				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);

\
				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"������ ���ƿ� �ᱸ��.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			}
			else if (pK->jjgetArray("done", top_uname4, 2) && !pK->jjgetArray("read", top_uname4, 3)) {//�׹�° ����Ʈ


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
				WideCharToMultiByte(CP_UTF8, 0, L"������ �� ������ ���Ŵٰ� �ߴµ� ���ٴ�...����� ������.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				nextnum = 16;
				comuwin->addChild(next);
				comuwin->addChild(comunication);

			}
			else {//���Ӱ� ���� ����Ʈ�� ���� ��
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
				WideCharToMultiByte(CP_UTF8, 0, L"�� �ڽ��� ������ �ϰŶ�.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);


			}



			break;
		}
		case NPC2: { // �����

			comupro = Sprite::create("NPC2_chon_normal.png");
			comupro->setAnchorPoint(Point(0, 0));
			comupro->setPosition(Point(-345, 0));
			comupro->setScale(0.8);
			comuwin->addChild(comupro);


			char chonjang[500];
			WideCharToMultiByte(CP_UTF8, 0, L"���� ����", -1, chonjang, 1024, NULL, NULL);
			O_t = Label::createWithTTF(chonjang, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //�ܰ��� ȿ���� �ִ� �Լ�. ����� �β�.

			comuwin->addChild(O_t);

			if (!pK->jjgetArray("read", top_uname4, 0)) { //����Ʈ1�� ���� ��

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
				WideCharToMultiByte(CP_UTF8, 0, L"�ڳ� �Դ°�. �׷��� �ʾƵ� �ڳ׸� ã�ư����� �߾��µ� �̷��� ���ִٴ� ������.\n\n��Ź�� ���� ������ ������� �ߴٸ鼭?   ", -1, chonjangcom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comunication->setTag(CO1);
				comuwin->addChild(comunication);

				nextnum = 0;
				comuwin->addChild(next);


			}
			else if (pK->jjgetArray("read", top_uname4, 3) && !pK->jjgetArray("done", top_uname4, 3)) {//����Ʈ3�� �о����� ���� �Ϸ�X


				this->removeChild(notice3);


				dataSingleton::getInstance()->isCM = false;

				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);



				char parentscom[500];
				WideCharToMultiByte(CP_UTF8, 0, L"��ħ �� �Գ�. �ڳ׿��� ���� ���� �ֱ���", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comuwin->addChild(comunication);

				pK->jjsetQint("nowing", top_uname4, 1, 3);
			}
			else if (pK->jjgetArray("done",top_uname4,3) && !pK->jjgetArray("read", top_uname4, 4)) { //����Ʈ5�� ���� ��

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
				WideCharToMultiByte(CP_UTF8, 0, L"������� �����. ���� ������ ���ƿ��� �ʾҴٰ�.\n\n�� �Ӹ� �ƴ϶� �ٸ� ���� ����鵵 ���� ���ƿ��� �ʾҴٰ� �ϴ�����.", -1, chonjangcom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(chonjangcom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));
				comunication->setTag(CO1);
				comuwin->addChild(comunication);

				nextnum = 18;
				comuwin->addChild(next);


			}
			else if (!pK->jjgetArray("done", top_uname4, 4) && (pK->jjgetQint("condition", top_uname4, 4) == pK->jjgetQint("nowing", top_uname4, 4))) {//�ټ���° ����Ʈ �Ϸ���


				auto questCom = MenuItemImage::create("completebut.png", "completebut_push.png", CC_CALLBACK_0(TopLayer::completeClicked, this));
				auto quest_complete = Menu::create(questCom, NULL);
				quest_complete->setScale(0.6);
				quest_complete->setAnchorPoint(Point(0, 0));
				quest_complete->setPosition(Point(1420, 420));
				comuwin->addChild(quest_complete);

				char parentscom[1000];
				WideCharToMultiByte(CP_UTF8, 0, L"�ʶ�� �س� �� �˾Ҵ�.", -1, parentscom, 1024, NULL, NULL);
				comunication = Label::createWithTTF(parentscom, "nanumgo.ttf", 30, Size(1400, 250), TextHAlignment::LEFT, TextVAlignment::TOP);
				comunication->setAnchorPoint(Point(0, 0));
				comunication->setPosition(Point(210, 0));

				comuwin->addChild(comunication);
			}
			else {//������ ����Ʈ�� ���� ��
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
				WideCharToMultiByte(CP_UTF8, 0, L"���� �Ų��� ���� �ε����ֽǰԴ�.", -1, chonjangcom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�̿��ֹ� ����", -1, flowernuna, 1024, NULL, NULL);
			O_t = Label::createWithTTF(flowernuna, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //�ܰ��� ȿ���� �ִ� �Լ�. ����� �β�.
			
			comuwin->addChild(O_t);

			char flowernunacom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"����⸦ ������ ������ ������ ��.", -1, flowernunacom, 1024, NULL, NULL);
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
			//������ ����Ʈ�� ���� ��
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
			WideCharToMultiByte(CP_UTF8, 0, L"���� �Ϸ�", -1, storebro, 1024, NULL, NULL);
			O_t = Label::createWithTTF(storebro, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //�ܰ��� ȿ���� �ִ� �Լ�. ����� �β�.
			
			comuwin->addChild(O_t);

			char storebrocom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"���! ���� �� ���� �� �־�!", -1, storebrocom, 1024, NULL, NULL);
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
			//������ ����Ʈ�� ���� ��
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
			WideCharToMultiByte(CP_UTF8, 0, L"�������� �ν�", -1, dajangjang, 1024, NULL, NULL);
			O_t = Label::createWithTTF(dajangjang, "nanumgo.ttf", 40);
			O_t->setAnchorPoint(Point(0, 0));
			O_t->setPosition(Point(130, 290));
			O_t->setColor(Color3B(255, 187, 0));
			//O_t->enableOutline(Color4B::BLACK, 3);        //�ܰ��� ȿ���� �ִ� �Լ�. ����� �β�.
			
			comuwin->addChild(O_t);

			char dajangjangcom[1000];
			WideCharToMultiByte(CP_UTF8, 0, L"����, �߰ſ� ����� ���� ��, ��������� ������!", -1, dajangjangcom, 1024, NULL, NULL);
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
	WideCharToMultiByte(CP_UTF8, 0, L" ����ġ ȹ��", -1, rwrdexpget, 1024, NULL, NULL);
	char rwrdmoneyget[100];
	WideCharToMultiByte(CP_UTF8, 0, L" ũ�� ȹ��", -1, rwrdmoneyget, 1024, NULL, NULL);
	char potionget[100];
	WideCharToMultiByte(CP_UTF8, 0, L" ȹ��", -1, potionget, 1024, NULL, NULL);
	char hppotion[100];
	WideCharToMultiByte(CP_UTF8, 0, L" HP����(��)X", -1, hppotion, 1024, NULL, NULL);
	char mppotion[100];
	WideCharToMultiByte(CP_UTF8, 0, L" MP����(��)X", -1, mppotion, 1024, NULL, NULL);

	if (pK->jjgetArray("done", top_uname5, 0) == false) {//����Ʈ 1_1 �Ϸ�

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

	else if (pK->jjgetArray("done", top_uname5, 1) == false) {//����Ʈ 1_2 �Ϸ�
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
	else if (pK->jjgetArray("done", top_uname5, 2) == false) {//����Ʈ 1_3 �Ϸ�

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
	else if (pK->jjgetArray("done", top_uname5, 3) == false) {//����Ʈ 1_4 �Ϸ�

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
	else if (pK->jjgetArray("done", top_uname5, 4) == false) {//����Ʈ 1_5 �Ϸ�

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

void TopLayer::OKClicked()//����Ʈ ����
{
	std::string top_uname6 = dataSingleton::getInstance()->user;
	dataSingleton::getInstance()->open = false;

	this->removeChild(getChildByTag(COMU));//â�� �����Ѵ�.


	if (!pK->jjgetArray("read", top_uname6, 0)) {//ù��° ����Ʈ�� ���� ���̶��
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc1_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // ���� �ִ� å �̹��� ����.
		npc2_i->removeChild(qm);
		this->removeChild(notice2);



		pK->jjsetArray("read", top_uname6, true, 0);//ù��° ����Ʈ�� ����

												//����° ����

		char notice3arr[500];
		WideCharToMultiByte(CP_UTF8, 0, L"�θ���� Ŭ���� ����Ʈ�� �Ϸ��ϼ���.", -1, notice3arr, 1024, NULL, NULL);
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
	else if (!pK->jjgetArray("read", top_uname6, 1)) {//�ι�° ����Ʈ�� ���� ���̶��
		//������ �ο�
		pK->jjsetAry("keyid", "userweapon", top_uname6, 0, 0);
		pK->jjsetAry("holding", "userweapon", top_uname6, 1, 0);

		qming = Sprite::create("QMing.png");
		qming->setPosition(Point(45, 335));
		qming->setTag(QMING);
		npc1_i->addChild(qming);
		npc1_i->removeChild(qm);
		pK->jjsetArray("read", top_uname6, true, 1);//�ι�° ����Ʈ�� ����

	}
	else if (!pK->jjgetArray("read", top_uname6, 2)) {//����° ����Ʈ�� ���� ���̶��
		qming = Sprite::create("QMing.png");
		qming->setPosition(Point(45, 335));
		qming->setTag(QMING);
		npc1_i->addChild(qming);
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // ���� �ִ� å �̹��� ����.
		npc1_i->removeChild(qm);

		pK->jjsetArray("read", top_uname6, true, 2);//ù��° ����Ʈ�� ����

												//����° ����
		label_num = 2;
		char notice5arr[500];
		WideCharToMultiByte(CP_UTF8, 0, L"���� ������ ������ �̵��� '�����Ա�' ������ �����ϼ���.", -1, notice5arr, 1024, NULL, NULL);
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
	else if (!pK->jjgetArray("read", top_uname6, 3)) {//�׹�° ����Ʈ�� ���� ���̶��
		cm = Sprite::create("CM.png");
		cm->setPosition(Point(45, 335));
		cm->setTag(CM);
		npc2_i->addChild(cm);
		dataSingleton::getInstance()->isCM = true;
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // ���� �ִ� å �̹��� ����.
		npc1_i->removeChild(qm);
		pK->jjsetArray("read", top_uname6, true, 3);
	}

	else if (!pK->jjgetArray("read", top_uname6, 4)) {//�ټ���° ����Ʈ�� ���� ���̶��
		qming = Sprite::create("QMing.png");
		qming->setPosition(Point(45, 335));
		qming->setTag(QMING);
		npc2_i->addChild(qming);
		//auto qmtag = (Sprite*)this->getChildByTag(QM);  // ���� �ִ� å �̹��� ����.
		npc2_i->removeChild(qm);

		pK->jjsetArray("read", top_uname6, true, 4);//ù��° ����Ʈ�� ����
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
		WideCharToMultiByte(CP_UTF8, 0, L"���� ���� � �� ����� �Ƹ��Ÿ��µ�...\n\n���� �̷��� ȥ�� ������ ���� ������ ��½ Ŀ���ȱ���.", -1, chonjangcom, 1024, NULL, NULL);
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
		WideCharToMultiByte(CP_UTF8, 0, L"�׷��Կ�. �� ���� ���� �ֺ��� ��� �� ���� ���� ���� �����ſ�. \n\n�Դٰ� ���� ��Ź���� ���ϴ� '���� ���� ���� ��'�� �������� ���ؼ� �ڽŵ� �����.", -1, chonjangcom, 1024, NULL, NULL);
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
		WideCharToMultiByte(CP_UTF8, 0, L"���, ���� �װ� �ڽ��� �������� ���ڱ���. \n\n�װ� �� ������ �Ӹ�ī���� ���� �͵�,\n\n���� ���� ����� �� ������ �� �͵� �� ������ �־����", -1, chonjangcom, 1024, NULL, NULL);
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
		WideCharToMultiByte(CP_UTF8, 0, L"�׸��� �ΰ��� �װ������¡��� ���� �͵� �쿬�� �ƴ϶�� �����Ѵ�. \n\n�ε� �� �ڽ��� �Ͼ����� ���ڱ���.\n\n�׷��� ������ ������ ������ �����̶� ��ź���� �ʰڴ���", -1, chonjangcom, 1024, NULL, NULL);
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
		WideCharToMultiByte(CP_UTF8, 0, L"��, ����ҰԿ�. ����� ����ó�� �� ��� ���� �쿬�� �ƴ϶��\n\n��Ź�� ���� ��ó�� �̾��ϰԶ� �� ���迡 ������ �� �� ������ ���ڽ��ϴ�.", -1, chonjangcom, 1024, NULL, NULL);
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
		WideCharToMultiByte(CP_UTF8, 0, L"�׷�, �ʶ�� �� �� �����Դ�. ���� ���� ��Ӵϰ� �ʸ� ���� ã�� �� �ϱ���. �� �����Ŷ�.\n\n�ѵ��� �θ�� �� �� �� �״� ���� ��ȭ ������ �� �ٳ���Ŷ�.", -1, chonjangcom, 1024, NULL, NULL);
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
		WideCharToMultiByte(CP_UTF8, 0, L"�ϸ����� �ູ�� �Բ� �ϱ�.", -1, chonjangcom, 1024, NULL, NULL);
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
		WideCharToMultiByte(CP_UTF8, 0, L"�ʵ� �˴ٽ��� �ֱٿ� ���͵��� �����Ͽ� ���� ������ ���ظ� �ְ� �ִܴ�.\n\n�츮 ������ �뺴����� ���� �ƹ������� �����ְ� �ְ�.", -1, parentscom, 1024, NULL, NULL);

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
		WideCharToMultiByte(CP_UTF8, 0, L"�׷��� ���̰� ���ϱ� ��Ź�� ������ �ڷ�\n\n���� �ֺ��� ���͵��� �����Ⱑ �ɻ�ġ �ʴٰ� �ϴ�����", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"��ҿ� ���ƿ��ð� �������ٵ�...\n\n�Դٰ� �� �ذ� �� �ð��̶� �����̱���.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�׷��� ���� �� �ƹ����� ã���� ������ ���ڽ��ϴ�.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"ȥ�ڼ� �ȵȴ�. ������. \n\n�ƹ����� �Բ� ���� �����е鵵 ���� �� ���ƿ����� �ʾ�\n\n���� ������ �ʿ� �Բ� ���� ���� �� �ִ� �е��� ������.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�� �������ϴ�, ��Ӵ�. ������ �����ϴ� ���� ������ ���͸� ����ĥ ���� �ִµ�\n\n���� �ֺ� ���� ���� ȥ�� �ذ����� ���ϸ� �ȵ��ݾƿ�.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�׸��� ��ҿ� �ƹ����� �Բ� ���� ����ϰ� �ٳ����� ȥ�ڼ��� �������ϴ�.\n\n�ð��� ��ü�Ҽ��� �ƹ����� ���� �������� �� ������ �����ּ���.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"...�˾Ҵ�.�Ͽ�ư ������ �����ϱ���.�� ��ó�� ��ü�� �ð��� ������.\n\n��� ������ �� ������ �ٷ� ���ƿ��Ŷ�.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�׸��� ���� ���� �̰� �ްŶ�\n\n�ƹ����� ���� ������ ���� �ν����� ��Ź�� ���� �͵��̴�. �켱 �̰ͺ��� �����غ��Ŷ�.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�� �����̱���. Ȥ�� ����Բ��� ������ �˰� ����� �𸣴� ������ �ʰڴ�?", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�����̱���. Ȥ�� ����Բ��� ������ �˰� ����� �𸣴� ������ �ʰڴ�?", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"���� ��Ȳ�� ���� �ʱ���.\n\n���� �Ա��� �ƹ��͵� ������?", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"��. �׷��� �����Ա��� ���ôµ� �ƹ��� �������ϴ�. ���� ������.\n\nȤ�� ����Բ��� �ƹ������� �����Ű� �����ʴϱ�?", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"...�ƹ����� �� �ҹ��� �Ű澲�̴±���.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�ҹ�...�̿�?", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"�׷�. '�÷����� ��'�� '����� ��ƸԴ� �Ĺ�'�� �ִٴ� �ҹ��� ���� �ִܴ�.\n\n�ֱٺ��� �� ���� �⹦�� �����Ҹ��� �鸰�ٰ� �ϴµ�...\n\n�ƹ����� ������ �� ���� �� �� �ϱ���.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"����� ��ƸԴ� �Ĺ��̿�?", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"������ �Ƹ� '������'�̶�� ������ ���ర�ٰ� �ϴ�����.\n\n������ �� ���͸� ����� �Ŷ�� �ϴ��� �ƹ����� ���� �� �� ������.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"...�����, ��...", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"������ �ʾƵ� �ȴ�. ������ ������. �̰� ���� ����̰� ������ ������.\n\n'�÷����� ��'�� '���� �Ա�'���� ����� ���� �ȴܴ�.\n\n��, �����ϴ� ������ �ٷ� ���ƿ��Ŷ�.", -1, parentscom, 1024, NULL, NULL);
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
			WideCharToMultiByte(CP_UTF8, 0, L"���� '������'�� ����ϰ�, ������ ã�ƺ��Ŷ�.", -1, parentscom, 1024, NULL, NULL);
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


	switch (keyCode) {//Ű �ڵ尪 Ȯ��
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

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW://����
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
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW://������
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
	//�Ʒ��� �±׸� ���� ��������Ʈ�� ������ �� �ִ� ����� �ڵ��Դϴ�.
	//auto player = (Sprite*)this->getChildByTag(TAG_PLAYER_SPRITE);


	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A: {
		break;
	}
	case EventKeyboard::KeyCode::KEY_UP_ARROW: {
		isUpPressed = false;
		//�±׸� ���� �ִϸ��̼��� �����ϱ� ���� ����� �ڵ��Դϴ�.
		//auto action = (Action*)player->getActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
		//player->getActionManager()->removeAction(action);
		break;
	}



	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
		isLeftPressed = false;
		//�ȱ� �ִϸ��̼��� ���� �ڵ��Դϴ�.
		auto action = (Action*)playerSpr->getActionByTag(TAG_SPRITE_PLAYER_ACTION_LEFT);
		playerSpr->getActionManager()->removeAction(action);
		if (isRightPressed == false)
			stopMovingBackground();

		break;
	}

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
		//�ȱ� �ִϸ��̼��� ���� �ڵ��Դϴ�.
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
		return;//void�ε� ��� ������ �Ǵ��� �ǹ�...? ���� ����Ȯ���� ���ִ� �� ����.. �ϳ��� f�� if��������..
			   //   log("start moving");
	this->schedule(schedule_selector(TopLayer::moveBackground));//�����층 ����
}

void TopLayer::stopMovingBackground()
{
	this->unschedule(schedule_selector(TopLayer::moveBackground));
}

void TopLayer::moveBackground(float t)
{

	auto moveStep = 13;

	if (isLeftPressed)//�����̸� -6
	{
		moveStep = -13;

		playerSpr->setFlippedX(true);
		//�¿� ���� �Լ�.
	}
	else//�������̸� 6
	{
		moveStep = 13;

		playerSpr->setFlippedX(false);
		//�¿� ���� �Լ�.
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


