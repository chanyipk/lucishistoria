#include "GameScene2.h"
#include "DtopLayer2.h"
#include "dataSingleton.h"
#include "clearLayer.h"
#include "UserLayer.h"
#include "Jdata.h"

Jdata* pD2;

int yindex2 = 1;
bool up2 = false;
bool down2 = false;
bool notfirst2 = false;
bool notfloor2 = false;

bool DtopLayer2::init() {
	if (!Layer::init()) {
		return false;
	}

	//초기화
	MAtt = 200;
	MDef = 150;
	MHP = 3000;
	y[0] = 280;
	

	isMove = false;
	isLeftPressed = false;
	isRightPressed = false;
	isAttack = 0;
	isAPressed = false;
	jumpYN = false;
	attYN = false;
	att1 = false;
	att2 = false;
	att3 = false;
	att4 = false;
	skillYN = false;

	dataSingleton::getInstance()->bosskill = false; // 보스 죽였는 지 여부 
	dataSingleton::getInstance()->playerDead = false;

	bmon = Sprite::create("mandra1.png");
	bmon->setAnchorPoint(Point(1, 0));
	bmon->setPosition(Point(1920,100));
	bmon->setScale(0.85);
	this->addChild(bmon);

	root = Sprite::create("mandra_atk.png");
	root->setPosition(0, -500);
	this->addChild(root);

	

	setEnemy();

	// 땅 배치
	ground1 = Sprite::create("floor1.png");
	ground1->setAnchorPoint(Point(0, 0));
	ground1->setPosition(Point(0, 0));
	this->addChild(ground1);

	//voidNode설정 
	voidNode = ParallaxNode::create();
	//	voidNode->addChild(ground1, 1, Point(1.0f, 0.0f), Point(0, 0));
	voidNode->setTag(1);
	this->addChild(voidNode, 0);




	//키보드 확인
	/*uk = Sprite::create("Uk.png");
	uk->setPosition(Point(1800, 150));
	uk->setAnchorPoint(Point(0, 0));
	this->addChild(uk);
	lk = Sprite::create("Lk.png");
	lk->setPosition(Point(1800, 300));
	lk->setAnchorPoint(Point(0, 0));
	this->addChild(lk);
	rk = Sprite::create("Rk.png");
	rk->setPosition(Point(1800, 450));
	rk->setAnchorPoint(Point(0, 0));
	this->addChild(rk);
	*/
	//플레이어 설정

	playerSpr = Sprite::create("a1.png");
	playerSpr->setPosition(Point(200, 280));
	playerSpr->setTag(TAG_PLAYER_SPRITE);
	this->addChild(playerSpr);//여기 this는 TopLayer입니다.
	playerStandAction();
							  //키보드 호출
	/*std::string dt2_uname = dataSingleton::getInstance()->user;
	int lev = pD2->jjgetInt("level", dt2_uname);
	std::string lev_lb = std::to_string(lev);
	plyr_lb = Label::createWithTTF("Lv." + lev_lb + " " + dt2_uname, "nanumgo.ttf", 15);
	plyr_lb->enableOutline(Color4B::BLACK, 2);
	plyr_lb->setAnchorPoint(Point(0.5, 0));
	plyr_lb->setPosition(Point(0, 0));
	playerSpr->addChild(plyr_lb);*/

	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(DtopLayer2::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(DtopLayer2::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listner, this);



	this->scheduleUpdate();

	auto UserLayer = UserLayer::create();
	this->addChild(UserLayer);

	return true;
}

//키 눌렀을 때 이벤트
void DtopLayer2::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	std::string dt2_uname1 = dataSingleton::getInstance()->user;
	auto player = (Sprite*)this->getChildByTag(TAG_PLAYER_SPRITE);
	auto pHP = dataSingleton::getInstance()->pHP;
	if (pHP>0) {
		switch (keyCode) {//키 코드값 확인
		case EventKeyboard::KeyCode::KEY_1:
		{
			auto maxPHP = pD2->jjgetInt("maxhp", dt2_uname1);
			auto PHP = pD2->jjgetInt("hp", dt2_uname1);
			if (dataSingleton::getInstance()->redcount > 0 && PHP > 0 && PHP < maxPHP) {
				dataSingleton::getInstance()->redcount -= 1;

				if (PHP + 200 > maxPHP)
					dataSingleton::getInstance()->pHP = maxPHP;
				else
					dataSingleton::getInstance()->pHP = dataSingleton::getInstance()->pHP + 200;

				for (int i = 0; i < 4; i++) {
					auto pid = pD2->jjgetAry("keyid", "userpotion", dt2_uname1, i);
					if (pid == 0) {
						pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->redcount, i);
						break;
					}
				}

				pD2->jjsetInt(dataSingleton::getInstance()->pHP, "hp", dt2_uname1);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_2:
		{
			auto maxPMP = pD2->jjgetInt("maxmp", dt2_uname1);
			auto PMP = pD2->jjgetInt("mp", dt2_uname1);
			if (dataSingleton::getInstance()->bluecount > 0 && PMP > 0 && PMP < maxPMP) {
				dataSingleton::getInstance()->bluecount -= 1;

				if (PMP + 200 > maxPMP)
					dataSingleton::getInstance()->pMP = maxPMP;
				else
					dataSingleton::getInstance()->pMP = dataSingleton::getInstance()->pMP + 200;
				for (int i = 0; i < 4; i++) {
					auto pid = pD2->jjgetAry("keyid", "userpotion", dt2_uname1, i);
					if (pid == 1) {
						pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->bluecount, i);
						break;
					}
				}
				pD2->jjsetInt(dataSingleton::getInstance()->pMP, "mp", dt2_uname1);
			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_X://위
		{

			isUpPressed = true;

		//	uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Ukp.png"));
			if (!jumpYN)
			{
				//startMovingBackground();
				playerSpr->stopAllActions();
				auto action = Sequence::create(JumpBy::create(1.0, Point(0, 0), 350, 1), CallFuncN::create(CC_CALLBACK_0(DtopLayer2::JumpEnd, this)), NULL);
				playerSpr->runAction(action);
				action->setTag(JUMPACT);
				jumpYN = true;
				if (isLeftPressed == false && isRightPressed == false)
				{
					auto animation = Animation::create();
					animation->setDelayPerUnit(0.1);
					animation->addSpriteFrameWithFile("j1.png");
					auto animate = Animate::create(animation);
					auto act = RepeatForever::create(animate);
					playerSpr->runAction(act);
					act->setTag(TAG_SPRITE_PLAYER_ACTION_UP);
				}
				else
				{
					auto animation = Animation::create();
					animation->setDelayPerUnit(0.1);
					animation->addSpriteFrameWithFile("rj1.png");
					auto animate = Animate::create(animation);
					auto act = RepeatForever::create(animate);
					playerSpr->runAction(act);
					act->setTag(TAG_SPRITE_PLAYER_ACTION_UP);
				}

				moveBackground(1.0);

				//break;
			}


			break;

		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW://왼쪽
		{
			isLeftPressed = true;
			isRightPressed = false;


		//	lk->setTexture(Director::getInstance()->getTextureCache()->addImage("Lkp.png"));

			if (isUpPressed == false && attYN == false && skillYN == false) {
				startMovingBackground();
				playerRunAction();
			}
			else if (isUpPressed == false && (attYN == true || skillYN == true)) {

			}
			else
			{
				startMovingBackground();
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
				playerSpr->setTexture(Director::getInstance()->getTextureCache()->addImage("rj1.png"));
				auto animation = Animation::create();
				animation->setDelayPerUnit(0.1);
				animation->addSpriteFrameWithFile("rj1.png");

				auto animate = Animate::create(animation);
				auto act = RepeatForever::create(animate);
				playerSpr->runAction(act);
				act->setTag(TAG_SPRITE_PLAYER_ACTION_LEFT);

			}
			moveBackground(1.0);

			break;
		}

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW://오른쪽
		{

			isLeftPressed = false;
			isRightPressed = true;


			//rk->setTexture(Director::getInstance()->getTextureCache()->addImage("Rkp.png"));

			if (isUpPressed == false && attYN == false && skillYN == false) {
				startMovingBackground();
				playerRunAction();
			}
			else if (isUpPressed == false && (attYN == true || skillYN == true)) {

			}
			else {
				startMovingBackground();
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
				playerSpr->setTexture(Director::getInstance()->getTextureCache()->addImage("rj1.png"));
				auto animation = Animation::create();
				animation->setDelayPerUnit(0.1);
				animation->addSpriteFrameWithFile("rj1.png");

				auto animate = Animate::create(animation);
				auto act = RepeatForever::create(animate);
				playerSpr->runAction(act);
				act->setTag(TAG_SPRITE_PLAYER_ACTION_RIGHT);
			}
			moveBackground(1.0);

			break;
		}
		//스킬쓰기
		case EventKeyboard::KeyCode::KEY_A: {


			//skill레이어를 아예 따로 만들어서 스킬에 대한 정의만 하고
			//정보를 넘겨서 해당 번호에 맞는 스킬을 사용하도록 하는게 코드를 줄일 수 있을듯..?

			
			auto PMP = dataSingleton::getInstance()->pMP;
			skillid = pD2->jjgetInt("skill1", dt2_uname1);
			if (skillid != 999) {
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_ATTACK);
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_STAND);
				auto skillmp = pD2->jjgetAry("skillmp", "skill", "skill", skillid);
				auto skilltime = dataSingleton::getInstance()->skillpressedA;
				if (!skillYN && PMP - skillmp > 0 && !skilltime) {
					skillhit = 0;
					isAPressed = true;
					dataSingleton::getInstance()->skillpressedA = true;
					skillYN = true;
					skillList(this, skillid);
					PMP = PMP - skillmp;
					dataSingleton::getInstance()->pMP = PMP;
					pD2->jjsetInt(PMP, "mp", dt2_uname1);
				}
				else
				{
					// 이미 호출하여 타이머가 있을 경우,불가 메세지 띄움.
					char skillX[40];
					WideCharToMultiByte(CP_UTF8, 0, L"스킬 사용 불가", -1, skillX, 1024, NULL, NULL);
					auto ban = Label::createWithTTF(skillX, "nanumgo.ttf", 30);
					ban->setPosition(Point(Director::getInstance()->
						getWinSize().width / 2, 800));
					ban->enableOutline(Color4B::WHITE);
					ban->setColor(Color3B::RED);
					this->addChild(ban);

					auto e11 = DelayTime::create(1.5);
					auto e22 = FadeOut::create(2.0);
					auto e33 = Sequence::create(e11, e22, NULL);
					ban->runAction(e33);
				}
			}

			break;

		}
		case EventKeyboard::KeyCode::KEY_Z://Z키
		{
			isAttack++;


			if (isUpPressed == true)
			{
				if (isRightPressed == false && isLeftPressed == false && isAttack == 1)//기본 점프에서의 공격
				{
					playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
					auto animation = Animation::create();
					animation->setDelayPerUnit(0.1);
					animation->addSpriteFrameWithFile("ja1.png");
					animation->addSpriteFrameWithFile("ja2.png");
					animation->addSpriteFrameWithFile("ja3.png");
					auto animate = Animate::create(animation);
					auto jaction1 = Sequence::create(CallFuncN::create(CC_CALLBACK_1(DtopLayer2::PattackMcrush, this)), animate, NULL);
					playerSpr->runAction(jaction1);
					animate->setTag(TAG_SPRITE_PLAYER_ACTION_ATTACK);


				}
				else {//이동 중인 상태에서의 점프에서의 공격 ( 총 두 콤보가 들어가게 됨)
					if (isAttack == 1) {

						playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
						auto animation = Animation::create();
						animation->setDelayPerUnit(0.1);
						animation->addSpriteFrameWithFile("rja1.png");
						animation->addSpriteFrameWithFile("rja2.png");
						animation->addSpriteFrameWithFile("rja4.png");
						auto animate = Animate::create(animation);
						auto rjaction1 = Sequence::create(CallFuncN::create(CC_CALLBACK_1(DtopLayer2::PattackMcrush, this)), animate, NULL);
						playerSpr->runAction(rjaction1);
						animate->setTag(TAG_SPRITE_PLAYER_ACTION_ATTACK);

					}//위의 액션이 끝난후 아래 액션이 진행되도록 해야 하며 연속 두 공격 과정 중에는 공중에 멈춰 있을 수 있도록 해야한다.
					 //시퀀스 알아보기 시퀀스에 2가지 액션을 넣어서 해당 액션이 끝나야 진행될 수 있도록 한다
					 //두번 누를 경우와 한 번 누를 경우로 분리해 한 번 누를 경우 하나의 act가 있는 시퀀스가 돌도록/ 두번 눌렀을 때는 두개의act가 있는 시퀀스가 돌도록

				}

			}
			else {//점프 안한 상태에서의 공격
				stopMovingBackground();


				auto animation1 = Animation::create();
				animation1->setDelayPerUnit(0.3);
				animation1->addSpriteFrameWithFile("ca1.png");
				animation1->addSpriteFrameWithFile("ca2.png");
				auto animate1 = Animate::create(animation1);

				auto animation2 = Animation::create();
				animation2->setDelayPerUnit(0.3);
				animation2->addSpriteFrameWithFile("ca3.png");
				animation2->addSpriteFrameWithFile("ca4.png");
				auto animate2 = Animate::create(animation2);


				auto animation3 = Animation::create();
				animation3->setDelayPerUnit(0.3);
				animation3->addSpriteFrameWithFile("ca5.png");
				animation3->addSpriteFrameWithFile("ca6.png");
				auto animate3 = Animate::create(animation3);

				auto animation4 = Animation::create();
				animation4->setDelayPerUnit(0.3);
				animation4->addSpriteFrameWithFile("ca7.png");
				animation4->addSpriteFrameWithFile("ca8.png");
				auto animate4 = Animate::create(animation4);


			//	uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Ukp.png"));
				attYN = true;

				if (isAttack == 1)
				{
					att1 = true;
					DelayTime *dt = DelayTime::create(0.2f);
					DelayTime *dt2 = DelayTime::create(0.05f);
					playerSpr->stopAllActions();
					action1 = Sequence::create(CallFuncN::create(CC_CALLBACK_1(DtopLayer2::PattackMcrush, this)), animate1, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer2::AttackEnd, this)), NULL);//att2==true가 동시다발로 일어나기 때문에 순차적으로 하기위해서 시퀀스가 필요, 저 값에 대한 행동을 할 수 있도록 함수를 만들자
					playerSpr->runAction(action1);



				}
				else if (isAttack == 2)
				{
					att2 = true;
					DelayTime *dt = DelayTime::create(0.2f);
					DelayTime *dt2 = DelayTime::create(0.05f);
					action2 = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(DtopLayer2::PattackMcrush, this)), animate2, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer2::AttackEnd, this)), NULL);
					playerSpr->runAction(action2);


				}
				else if (isAttack == 3)
				{
					att3 = true;
					DelayTime *dt = DelayTime::create(0.4f);
					DelayTime *dt2 = DelayTime::create(0.05f);
					action3 = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(DtopLayer2::PattackMcrush, this)), animate3, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer2::AttackEnd, this)), NULL);
					playerSpr->runAction(action3);

				}
				else if (isAttack == 4)
				{
					DelayTime *dt = DelayTime::create(0.6f);
					DelayTime *dt2 = DelayTime::create(0.05f);
					action4 = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(DtopLayer2::PattackMcrush, this)), animate4, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer2::AttackEnd, this)), NULL);
					playerSpr->runAction(action4);
				}

			}
			//else if{ 좌우방향키 눌러져있을 경우, 안눌러져 있을경우}
			break;
		}

		//아이템 줍기
	/*	case EventKeyboard::KeyCode::KEY_C: {


			auto play_box = playerSpr->getBoundingBox();
			Size windowSize = Director::getInstance()->getWinSize();
			char cruget[15];
			WideCharToMultiByte(CP_UTF8, 0, L" 크루 획득", -1, cruget, 1024, NULL, NULL);
			char potionget[15];
			WideCharToMultiByte(CP_UTF8, 0, L" 획득", -1, potionget, 1024, NULL, NULL);
			char hppotion[30];
			WideCharToMultiByte(CP_UTF8, 0, L" HP포션(소)X", -1, hppotion, 1024, NULL, NULL);
			char mppotion[30];
			WideCharToMultiByte(CP_UTF8, 0, L" MP포션(소)X", -1, mppotion, 1024, NULL, NULL);
			char knife[30];
			WideCharToMultiByte(CP_UTF8, 0, L" 철조각X", -1, knife, 1024, NULL, NULL);

			auto havemoney = pD2->jjgetInt("money", dt2_uname1);

			if (money1->isVisible())
			{
				auto item_box1 = money1->getBoundingBox();

				if (play_box.intersectsRect(item_box1)) {

					money1->setVisible(false);
					int money_r = rand() % 10 + 5;//5~14
					int money_rand = money_r * 100;//500~1400
					havemoney += money_rand;
					pD2->jjsetInt(havemoney, "money", dt2_uname1);



					std::string moneyLabel = std::to_string(money_rand);
					auto label = Label::createWithTTF(moneyLabel + cruget, "nanumgo.ttf", 30);
					label->setAnchorPoint(Point(0, 0));
					label->setPosition(100, 300);
					this->addChild(label);

					auto dtm = DelayTime::create(3.0);
					auto fdm = FadeOut::create(2.0);

					auto seqm = Sequence::create(dtm, fdm, NULL);
					label->runAction(seqm);
				}
			}

			if (money2->isVisible())
			{
				auto item_box2 = money2->getBoundingBox();

				if (play_box.intersectsRect(item_box2)) {


					money2->setVisible(false);
					int money_r = rand() % 10 + 5;
					int money_rand = money_r * 100;
					havemoney += money_rand;
					pD2->jjsetInt(havemoney, "money", dt2_uname1);
					std::string moneyLabel = std::to_string(money_rand);

					auto label = Label::createWithTTF(moneyLabel + cruget, "nanumgo.ttf", 30);
					label->setAnchorPoint(Point(0, 0));
					label->setPosition(100, 300);
					this->addChild(label);

					auto dtm = DelayTime::create(3.0);
					auto fdm = FadeOut::create(2.0);

					auto seqm = Sequence::create(dtm, fdm, NULL);
					label->runAction(seqm);
				}
			}

			if (money3->isVisible())
			{
				auto item_box3 = money3->getBoundingBox();

				if (play_box.intersectsRect(item_box3)) {

					money3->setVisible(false);
					int money_r = rand() % 10 + 5;
					int money_rand = money_r * 100;
					havemoney += money_rand;
					pD2->jjsetInt(havemoney, "money", dt2_uname1);
					std::string moneyLabel = std::to_string(money_rand);

					auto label = Label::createWithTTF(moneyLabel + cruget, "nanumgo.ttf", 30);
					label->setAnchorPoint(Point(0, 0));
					label->setPosition(100, 300);
					this->addChild(label);

					auto dtm = DelayTime::create(3.0);
					auto fdm = FadeOut::create(2.0);

					auto seqm = Sequence::create(dtm, fdm, NULL);
					label->runAction(seqm);
				}
			}

			if (money4->isVisible())
			{
				auto item_box4 = money4->getBoundingBox();

				if (play_box.intersectsRect(item_box4)) {

					money4->setVisible(false);
					int money_r = rand() % 10 + 5;
					int money_rand = money_r * 100;
					havemoney += money_rand;
					pD2->jjsetInt(havemoney, "money", dt2_uname1);
					std::string moneyLabel = std::to_string(money_rand);

					auto label = Label::createWithTTF(moneyLabel + cruget, "nanumgo.ttf", 30);
					label->setAnchorPoint(Point(0, 0));
					label->setPosition(100, 300);
					this->addChild(label);

					auto dtm = DelayTime::create(3.0);
					auto fdm = FadeOut::create(2.0);

					auto seqm = Sequence::create(dtm, fdm, NULL);
					label->runAction(seqm);
				}
			}

			if (money5->isVisible())
			{
				auto item_box5 = money5->getBoundingBox();

				if (play_box.intersectsRect(item_box5)) {

					money5->setVisible(false);
					int money_r = rand() % 10 + 5;
					int money_rand = money_r * 100;
					havemoney += money_rand;
					pD2->jjsetInt(havemoney, "money", dt2_uname1);
					std::string moneyLabel = std::to_string(money_rand);

					auto label = Label::createWithTTF(moneyLabel + cruget, "nanumgo.ttf", 30);
					label->setAnchorPoint(Point(0, 0));
					label->setPosition(100, 300);
					this->addChild(label);

					auto dtm = DelayTime::create(3.0);
					auto fdm = FadeOut::create(2.0);

					auto seqm = Sequence::create(dtm, fdm, NULL);
					label->runAction(seqm);
				}
			}

			if (red1->isVisible()) {

				auto red_box1 = red1->getBoundingBox();
				int rednum = rand() % 3 + 1;
				std::string rednumStr = std::to_string(rednum);
				if (play_box.intersectsRect(red_box1)) {
					dataSingleton::getInstance()->redcount += rednum;
					pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->redcount, 0);
					red1->setVisible(false);

					auto redlabel = Label::createWithTTF(hppotion + rednumStr + potionget, "nanumgo.ttf", 30);
					redlabel->setAnchorPoint(Point(0, 0));
					redlabel->setPosition(100, 250);
					this->addChild(redlabel);

					auto dtr = DelayTime::create(3.0);
					auto fdr = FadeOut::create(2.0);
					auto seqr = Sequence::create(dtr, fdr, NULL);
					redlabel->runAction(seqr);
				}
			}

			if (red2->isVisible()) {
				auto red_box2 = red2->getBoundingBox();
				int rednum = rand() % 3 + 1;
				std::string rednumStr = std::to_string(rednum);
				if (play_box.intersectsRect(red_box2)) {
					dataSingleton::getInstance()->redcount += rednum;
					pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->redcount, 0);
					red2->setVisible(false);

					auto redlabel = Label::createWithTTF(hppotion + rednumStr + potionget, "nanumgo.ttf", 30);
					redlabel->setAnchorPoint(Point(0, 0));
					redlabel->setPosition(100, 250);
					this->addChild(redlabel);
					auto dtr = DelayTime::create(3.0);
					auto fdr = FadeOut::create(2.0);
					auto seqr = Sequence::create(dtr, fdr, NULL);
					redlabel->runAction(seqr);
				}
			}
			if (red3->isVisible()) {
				auto red_box3 = red3->getBoundingBox();
				int rednum = rand() % 3 + 1;
				std::string rednumStr = std::to_string(rednum);
				if (play_box.intersectsRect(red_box3)) {
					dataSingleton::getInstance()->redcount += rednum;
					pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->redcount, 0);
					red3->setVisible(false);

					auto redlabel = Label::createWithTTF(hppotion + rednumStr + potionget, "nanumgo.ttf", 30);
					redlabel->setAnchorPoint(Point(0, 0));
					redlabel->setPosition(100, 250);
					this->addChild(redlabel);

					auto dtr = DelayTime::create(3.0);
					auto fdr = FadeOut::create(2.0);
					auto seqr = Sequence::create(dtr, fdr, NULL);
					redlabel->runAction(seqr);
				}

			}

			

			if (blue1->isVisible()) {

				auto blue_box1 = blue1->getBoundingBox();
				int bluenum = rand() % 3 + 1;
				std::string bluenumStr = std::to_string(bluenum);
				if (play_box.intersectsRect(blue_box1)) {
					dataSingleton::getInstance()->bluecount += bluenum;
					pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->bluecount, 1);
					blue1->setVisible(false);

					auto bluelabel = Label::createWithTTF(mppotion + bluenumStr + potionget, "nanumgo.ttf", 30);
					bluelabel->setAnchorPoint(Point(0, 0));
					bluelabel->setPosition(100, 200);
					this->addChild(bluelabel);

					auto dtb = DelayTime::create(3.0);
					auto fdb = FadeOut::create(2.0);
					auto seqb = Sequence::create(dtb, fdb, NULL);
					bluelabel->runAction(seqb);
				}
			}
			if (blue2->isVisible()) {
				auto blue_box2 = blue2->getBoundingBox();
				int bluenum = rand() % 3 + 1;
				std::string bluenumStr = std::to_string(bluenum);
				if (play_box.intersectsRect(blue_box2)) {
					dataSingleton::getInstance()->bluecount += bluenum;
					pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->bluecount, 1);
					blue2->setVisible(false);

					auto bluelabel = Label::createWithTTF(mppotion + bluenumStr + potionget, "nanumgo.ttf", 30);
					bluelabel->setAnchorPoint(Point(0, 0));
					bluelabel->setPosition(100, 200);
					this->addChild(bluelabel);


					auto dtb = DelayTime::create(3.0);
					auto fdb = FadeOut::create(2.0);
					auto seqb = Sequence::create(dtb, fdb, NULL);
					bluelabel->runAction(seqb);
				}
			}
			if (blue3->isVisible()) {
				auto blue_box3 = blue3->getBoundingBox();
				int bluenum = rand() % 3 + 1;
				std::string bluenumStr = std::to_string(bluenum);
				if (play_box.intersectsRect(blue_box3)) {
					dataSingleton::getInstance()->bluecount += bluenum;
					pD2->jjsetpArray("holding", dt2_uname1, dataSingleton::getInstance()->bluecount, 1);
					blue3->setVisible(false);

					auto bluelabel = Label::createWithTTF(mppotion + bluenumStr + potionget, "nanumgo.ttf", 30);
					bluelabel->setAnchorPoint(Point(0, 0));
					bluelabel->setPosition(100, 200);
					this->addChild(bluelabel);


					auto dtb = DelayTime::create(3.0);
					auto fdb = FadeOut::create(2.0);
					auto seqb = Sequence::create(dtb, fdb, NULL);
					bluelabel->runAction(seqb);
				}

			}


			break;
		}*/
		case EventKeyboard::KeyCode::KEY_I: {

			break;

		}
		default:
			break;
		}
	}
}

//키 땠을 때 이벤트
void DtopLayer2::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto pHP = dataSingleton::getInstance()->pHP;
	if (pHP > 0) {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_X: {
			if (isUpPressed == true) {

			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_A: {
			isAPressed = false;
			break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
			//걷기 애니메이션을 위한 코드입니다.
			isLeftPressed = false;
		//	lk->setTexture(Director::getInstance()->getTextureCache()->addImage("Lk.png"));
			auto action = (Action*)playerSpr->getActionByTag(TAG_SPRITE_PLAYER_ACTION_LEFT);
			playerSpr->getActionManager()->removeAction(action);
			if (isRightPressed == false)
				stopMovingBackground();
			break;
		}

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
			//걷기 애니메이션을 위한 코드입니다.
			isRightPressed = false;
			//rk->setTexture(Director::getInstance()->getTextureCache()->addImage("Rk.png"));
			auto action = (Action*)playerSpr->getActionByTag(TAG_SPRITE_PLAYER_ACTION_RIGHT);
			playerSpr->getActionManager()->removeAction(action);
			if (isLeftPressed == false)
				stopMovingBackground();
			break;
		}
		case EventKeyboard::KeyCode::KEY_Z: {

			break;
		}
		default:
			break;
		}

		if (isRightPressed == false && isLeftPressed == false && isUpPressed == false && attYN == false && skillYN == false) { //좌키 우키 상키 둘다 안눌러져 있을 경우 기본 자세로 전환
																															   //점프 두번 시 문제 생기는듯

			playerStandAction();
		}
	}
}

//배경 움직임
void DtopLayer2::startMovingBackground()
{
	if (isLeftPressed == true && isRightPressed == true)
		return;//void인데 어떻게 리턴이 되는지 의문...? 뭔가 예외확인을 해주는 것 같은.. 하나만 vx면 if빠져나감..

	this->schedule(schedule_selector(DtopLayer2::moveBackground));//스케쥴링 시작
}

//배경 멈춤
void DtopLayer2::stopMovingBackground()
{
	this->unschedule(schedule_selector(DtopLayer2::moveBackground));
}

void DtopLayer2::moveBackground(float t)
{

	auto moveStep = 20;
	if (isLeftPressed)//왼쪽이면 -6
	{
		moveStep = -20;
		if (attYN == false && skillYN == false)
			playerSpr->setFlippedX(true);
		//좌우 반전 함수.
	}
	else//오른쪽이면 6
	{
		moveStep = 20;
		if (attYN == false && skillYN == false)
			playerSpr->setFlippedX(false);
		//좌우 반전 함수.
	}
	auto newPos = Point(playerSpr->getPosition().x, playerSpr->getPosition().y);
	//auto newPos2 = Point(voidNode->getPosition().x, voidNode->getPosition().y);
	//float vx = voidNode->getPositionX();
	//float vy = voidNode->getPositionY();


	if (isRightPressed) {
		if (!dataSingleton::getInstance()->bosskill) {
			if (newPos.x > 1250) {
				newPos.x = 1250;
			}
			else if (newPos.x < 1250) {
				newPos.x += moveStep; //캐릭터가 움직이는 듯
			}
		}

		else{
			if (newPos.x > 1900) {
				newPos.x = 1900;
			}
			else if (newPos.x < 1900) {
				newPos.x += moveStep; //캐릭터가 움직이는 듯
			}
		}
	/*	else {//배경이 움직임
			if (vx > -7680) {//-7680이라하면 이미지를 4배로 키웠을 경우 마지막 이미지칸에 해당할 때를 제외
				newPos2.x -= moveStep; // 배경이 움직임(왼쪽으로 여기서 vx는 voidnode의 x축값 gx값이 아닐까.
			}
			else {
				newPos.x += moveStep;//나머지는 캐릭터의 이동
			}
		}*/
	}
	else if (isLeftPressed) {
		if (newPos.x < 20) {
			newPos.x = 20;
		}
		else if (newPos.x >= 20 ) {
			newPos.x += moveStep; //캐릭터가 움직이는 듯
		}
/*		else {
			if (vx < 0) {
				newPos2.x -= moveStep;
			}
			else {
				newPos.x += moveStep;
			}
		}*/
	}



	float xx = playerSpr->getPositionX();
	float yy = playerSpr->getPositionY();
	dataSingleton::getInstance()->x = xx;
	dataSingleton::getInstance()->y = yy;

	

	playerSpr->setPosition(newPos);

	




}

void DtopLayer2::playerRisen()
{
	playerStandAction();
	playerSpr->setOpacity(255);

	Prisen = ParticleSystemQuad::create("riseneffect.plist");
	Prisen->setDuration(1.0);
	Prisen->setPosition(Point(playerSpr->getPositionX(), playerSpr->getPositionY() - 150));
	this->addChild(Prisen);

	dataSingleton::getInstance()->risen = false;
	gameovertrue = false;
}


//실시간 변경
void DtopLayer2::update(float delta)
{
	dataSingleton::getInstance()->x = playerSpr->getPositionX();
	dataSingleton::getInstance()->y= playerSpr->getPositionY();
	std::string dt2_uname1 = dataSingleton::getInstance()->user;
	if (dataSingleton::getInstance()->risen == true)
	{
		playerRisen();
	}
	if (dataSingleton::getInstance()->bosskill&& !dunclear) {
		dunclear = true;
		auto enddt = DelayTime::create(8.0);
		auto callclear = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::callClear, this));
		auto endse = Sequence::create(enddt, callclear, NULL);
		this->runAction(endse);

	}
	if (isgas && gascu) {

		gascu = false;
		auto callgascu = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::callgascu, this));
		auto gascudt = DelayTime::create(0.2);
		auto gascuse = Sequence::create(gascudt, callgascu, NULL);
		this->runAction(gascuse);
	}
	/*int lev = pD2->jjgetInt("level", dt2_uname1);
	std::string lev_lb = std::to_string(lev);
	plyr_lb->setString("Lv." + lev_lb + " " + dt2_uname1);
	*/
	playertrue = playerSpr->isVisible();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();
	pRect = Rect(px - 600, py, 900, 300);//플레이어 충돌박스
	pgRect = Rect(px - 40, py, 440, 10);
	pdropRect = Rect(px - 40, py, 440, 10);

	if (skill_eff) {
		skillCrush();

	}
	
	setMAttack();


	playertrue = playerSpr->isVisible();


	//플레이어 정보
	PHP = dataSingleton::getInstance()->pHP;
	PEXP = dataSingleton::getInstance()->pEXP;


	if (dataSingleton::getInstance()->pHP <= 0 && !gameovertrue) {
		auto action = Sequence::create(CallFuncN::create(CC_CALLBACK_0(DtopLayer2::playerDis, this)), NULL);
		this->runAction(action);
		gameovertrue = true;
	}

	//점프할 때 착지를 위한 y축 검사
	if (jumpYN) {
		up2 = false;
		down2 = false;
		auto py = playerSpr->getPositionY();
		a[0] = py;
		a[yindex2++] = playerSpr->getPositionY();
		if (a[yindex2 - 2] > a[yindex2 - 1])//떨어질때 인식
		{
			down2 = true;
			auto px = playerSpr->getPositionX();
			auto py = playerSpr->getPositionY();

			pjRect = Rect(px, py, 420, 10);

			//ground3에 올라가기
			if (pjRect.intersectsRect(ground3box) || pjRect.intersectsRect(ground2box) || pjRect.intersectsRect(groundnext1box) || pjRect.intersectsRect(groundnext2box)) {
				notfirst2 = true;
				JumpEnd();
			}

		}
		else {
			down2 = false;
			up2 = true;
		}
	}
	else {
		up2 = false;
		down2 = false;
	}
	//캐릭터가 1층이 아닌 곳에서 점프를 시도할 때
	/*	if (jumpYN&&(pD2ropRect.intersectsRect(ground3jumpbox) || pD2ropRect.intersectsRect(ground2jumpbox) || pD2ropRect.intersectsRect(groundnext1jumpbox) || pD2ropRect.intersectsRect(groundnext2jumpbox)))
	jumpcu = true;
	else
	jumpcu = false;
	*/
	//부유하고 있는 땅에서 벗어났는지 벗어나지 않았는지 확인


}
/*플레이어 함수*/
//캐릭터 공격 끝
void DtopLayer2::AttackEnd(Ref* sender)
{
	if (att1 == true) {//공격한번하고 종료
		att1 = false;
		if (att2 == false) {
			isAttack = 0;
			AttackEndAction();
		}
	}
	else if (att2 == true) {
		att2 = false;
		if (att3 == false) {
			isAttack = 0;
			AttackEndAction();
		}
	}
	else if (att3 == true) {
		att3 = false;
		if (att4 == false) {
			isAttack = 0;
			AttackEndAction();
		}
	}
	else if (att4 == true) {
		isAttack = 0;
		att4 = false;
		AttackEndAction();
	}
//	uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Uk.png"));

}
void DtopLayer2::setMAttack() {
	auto time = dataSingleton::getInstance()->time;

	if (MHP>0)
	{ 
		if (time % 10 == 0 && !mSkilltrue) {
			mSkilltrue = true;
			bmon->stopActionByTag(MonsterStandMotion);
			int num = (rand() % 3) + 0;
			switch (num) {
			case 0: {
				//찌르기
				bmon->setTexture(Director::getInstance()->getTextureCache()->addImage("mandra_a10.png"));

				break;
			}
			case 1: {
				//나무발사
				bmon->setTexture(Director::getInstance()->getTextureCache()->addImage("mandra_a2.png"));
				auto px = playerSpr->getPositionX();

				root->setPosition(px, -500);
				beforepx = px;

				break;
			}
			case 2: {
				bmon->setTexture(Director::getInstance()->getTextureCache()->addImage("mandra_a3.png"));
				//독가스
				break;
			}
			}
			auto sdt1 = DelayTime::create(1.5);
			auto sdt2 = DelayTime::create(1.0);
			auto sf = CallFuncN::create(CC_CALLBACK_1(DtopLayer2::MskillList, this, num));
			auto se = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::monSkillend, this));
			auto seq = Sequence::create(sdt1, sf, sdt2, se, NULL);
			bmon->runAction(seq);
		}
	}
}
void DtopLayer2::playerStandAction() {
	playerSpr->stopAllActions();
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2);
	animation->addSpriteFrameWithFile("a1.png");
	animation->addSpriteFrameWithFile("a2.png");
	animation->addSpriteFrameWithFile("a3.png");
	animation->addSpriteFrameWithFile("a2.png");
	auto animate = Animate::create(animation);
	auto act = RepeatForever::create(animate);
	act->setTag(TAG_SPRITE_PLAYER_ACTION_STAND);
	playerSpr->runAction(act);
}
void DtopLayer2::playerRunAction() {
	playerSpr->stopAllActions();
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1);
	animation->addSpriteFrameWithFile("r1.png");
	animation->addSpriteFrameWithFile("r2.png");
	animation->addSpriteFrameWithFile("r3.png");
	animation->addSpriteFrameWithFile("r4.png");
	animation->addSpriteFrameWithFile("r5.png");
	animation->addSpriteFrameWithFile("r6.png");
	animation->addSpriteFrameWithFile("r7.png");
	animation->addSpriteFrameWithFile("r8.png");
	auto animate = Animate::create(animation);
	auto act = RepeatForever::create(animate);
	playerSpr->runAction(act);
}
//캐릭터 공격 끝난 후 액션
void DtopLayer2::AttackEndAction() {

	attYN = false;
	isLeftPressed = false;
	isRightPressed = false;
	playerSpr->stopAllActions();
	skillYN = false;
	playerStandAction();


}
//스킬 끝
void DtopLayer2::skillEnd() {
	if (!jumpYN) {
		attYN = false;
		skillYN = false;
		playerStandAction();
	}
}


//캐릭터 점프 끝
void DtopLayer2::JumpEnd()
{
	isUpPressed = false;
	isAttack = 0;
	jumpYN = false;
	skillYN = false;
	yindex2 = 1;
	if (!isLeftPressed && !isRightPressed)
		playerStandAction();
	else
		playerRunAction();
	//uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Uk.png"));



}
void DtopLayer2::DropEnd()
{
	isUpPressed = false;
	isAttack = 0;
	jumpYN = false;
	attYN = false;
	down2 = false;
	yindex2 = 1;
	if(!isLeftPressed&&!isRightPressed)
		playerStandAction();
	//uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Uk.png"));

}


//플레이어 공격 몬스터 충돌
void DtopLayer2::PattackMcrush(Ref* sender) {

	std::string dt2_uname2 = dataSingleton::getInstance()->user;
	Rect paRect;
	mRect = Rect(1500, 100, 300, 913);
	auto mx = bmon->getPositionX();
	auto my = bmon->getPositionY();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();
	if (!playerSpr->isFlippedX())
		paRect = Rect(px, py, 300, 200);
	else
		paRect = Rect(px - 200, py, 300, 200);

	auto atk = pD2->jjgetInt("atk", dt2_uname2);
	auto atkst = pD2->jjgetInt("atkst", dt2_uname2);
	PAtt = (rand() % (atkst + 1)) + atk;//atk+공격력 증가스텟을 넣는 것으로 생각한다.//atk=100,atkst=10 100~130
	if (PAtt > MDef) {
		int cri = pD2->jjgetInt("cri", dt2_uname2);//10
		int cridam = pD2->jjgetInt("cridam", dt2_uname2);//150
		int num = (rand() % 100) + 1;//1~100

		if (num <= cri) {
			mdamage = (PAtt*cridam) / 100 - MDef;//100*150/100-50 = 100


		}
		else
			mdamage = PAtt - MDef;//100-50 = 50;
	}
	else
		mdamage = 0;

	if (paRect.intersectsRect(mRect) && MHP > 0) {

		auto particle1 = ParticleSystemQuad::create("patteffect.plist");
		particle1->setDuration(0.2);
		particle1->setPosition(Point(mx-300, py + 45));

		this->addChild(particle1);
		if (MHP > mdamage)
		{
			MHP = MHP - mdamage;
		}
		else if (MHP <= mdamage)
		{
			MHP = 0;
		}
		mdamageeffect();


		//MHPS1->setPercentage(mhppercent1);
		float cu1 = MHPS->getPercentage();
		cu1 = (MHP / 3000) * 100;

		MHPS->setPercentage(cu1);
		String *str = String::createWithFormat("%.0f", MHP);
		MHPnum->setString(str->getCString());

		if (MHP <= 0) {
			
			auto fade = FadeOut::create(2.0);
			auto item = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::item, this));
			auto pill = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::pill, this));
			auto dis = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::DeleteMon, this));
			auto giveexp = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::giveexp, this));
			auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
			auto s = Sequence::create(fade, sp, NULL);
			bmon->runAction(s);
		}
	}


}

//플레이어 사라지는 모션
void DtopLayer2::playerDis() {

	playerSpr->stopAllActions();
	auto ani = Animation::create();
	ani->setDelayPerUnit(0.2);
	ani->addSpriteFrameWithFile("pD1.png");
	ani->addSpriteFrameWithFile("pD2.png");
	ani->addSpriteFrameWithFile("pD3.png");
	ani->addSpriteFrameWithFile("pD4.png");
	ani->addSpriteFrameWithFile("pD5.png");
	ani->addSpriteFrameWithFile("pD6.png");
	auto animate = Animate::create(ani);
	auto fade = FadeOut::create(2.0);
	//auto over = CallFuncN::create(CC_CALLBACK_0(UserLayer::gameover, this));
	auto dis = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::playerDead, this));
	auto action = Sequence::create(animate, fade, dis, NULL);
	playerSpr->runAction(action);
}

//플레이어 여부 판독
void DtopLayer2::playerDead() {
	dataSingleton::getInstance()->playerDead = true;
}




/*몬스터(+플레이어) 함수*/

//몬스터 기본 설정


void DtopLayer2::giveexp() {
	std::string dt2_uname3 = dataSingleton::getInstance()->user;
	PEXP = PEXP + 500;
	dataSingleton::getInstance()->pEXP = PEXP;
	pD2->jjsetInt(PEXP, "exp", dt2_uname3);
}


void DtopLayer2::itemposition() {
	float vx = voidNode->getPositionX();
	float vy = voidNode->getPositionY();

}


void DtopLayer2::skillList(Ref* sender, int n) {

	switch (n) {
	case 0: {
		auto skillanimation1 = Animation::create();
		skillanimation1->setDelayPerUnit(0.3);
		skillanimation1->addSpriteFrameWithFile("ca1.png");
		skillanimation1->addSpriteFrameWithFile("ca2.png");
		auto skillanimate1 = Animate::create(skillanimation1);
		skillanimate1->setTag(TAG_SPRITE_PLAYER_ACTION_SKILL);
		playerSpr->runAction(skillanimate1);

		auto px = playerSpr->getPositionX();
		auto py = playerSpr->getPositionY();

		DelayTime *dt3 = DelayTime::create(0.05f);


		skill_eff = Sprite::create("skill1_eff.png");
		skill_eff->setPosition(Point(px + 100, py + 30));
		this->addChild(skill_eff);
		DelayTime *dt4 = DelayTime::create(0.2f);
		MoveBy *moveaction1_1;
		if (playerSpr->isFlippedX()) {
			moveaction1_1 = MoveBy::create(0.5, Point(-400, 0));
			skill_eff->setFlippedX(true);
		}
		else {
			moveaction1_1 = MoveBy::create(0.5, Point(400, 0));
			skill_eff->setFlippedX(false);
		}
		//	auto spaweff = Spawn::create(moveaction1_1, CallFuncN::create(CC_CALLBACK_0(DtopLayer2::skillCrush, this)), NULL);
		auto seqeff = Sequence::create(moveaction1_1, CallFuncN::create(CC_CALLBACK_0(DtopLayer2::skill_effEnd, this)), NULL);
		skill_eff->runAction(seqeff);
		skill1 = Sequence::create(skillanimate1, dt3, CallFuncN::create(CC_CALLBACK_0(DtopLayer2::skillEnd, this)), NULL);
		playerSpr->runAction(skill1);


	}
	}
}

void DtopLayer2::skill_effEnd() {
	skill_eff->setVisible(false);

}
void DtopLayer2::setEnemy() {
	
	mhps_back = Sprite::create("bmhpbar.png");
	mhps_back->setAnchorPoint(Point(0.5, 0.5));
	mhps_back->setPosition(Point(960, 950));
	mhps_back->setScale(0.8);
	this->addChild(mhps_back);

	auto mhps1 = Sprite::create("bmhps.png");
	MHPS = ProgressTimer::create(mhps1);
	MHPS->setType(ProgressTimer::Type::BAR);
	MHPS->setAnchorPoint(Point(0.5, 0.5));
	MHPS->setPosition(Point(960, 950));
	MHPS->setMidpoint(Point(0, 0));
	MHPS->setBarChangeRate(Point(1, 0));
	MHPS->setPercentage(100);
	MHPS->setScale(0.8);
	this->addChild(MHPS);

	MHPnum = Label::createWithTTF("3000", "nanumgo.ttf", 30);
	MHPnum->setPosition(Point(872, 62));
	MHPS->addChild(MHPnum);

	Mname = Label::createWithTTF("Lv.5 만드라곤", "nanumgo.ttf", 30);
	Mname->setPosition(Point(872,150));
	MHPS->addChild(Mname);


	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.5);
	animation1->addSpriteFrameWithFile("mandra1.png");
	animation1->addSpriteFrameWithFile("mandra2.png");
	animation1->addSpriteFrameWithFile("mandra3.png");
	auto animate1 = Animate::create(animation1);
	auto act1 = RepeatForever::create(animate1);
	act1->setTag(MonsterStandMotion);
	bmon->runAction(act1);
}
void DtopLayer2::damageeffect() {
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();

	std::string damageStr;
	if (damage == 0)
		damageStr = "MISS";
	else
		damageStr = std::to_string(damage);

	auto damagelabel = Label::createWithTTF(damageStr, "drfont.ttf", 50);
	damagelabel->setPosition(Point(px , py+100));
	damagelabel->enableOutline(Color4B::BLACK, 1);

	if (damage > 0)//일반공격
	{
		damagelabel->setColor(Color3B(170, 18, 18));//검빨간색(크리티컬)
	}
	else if (damage == 0)//miss
		damagelabel->setColor(Color3B(255, 187, 0));//노란색

	this->addChild(damagelabel);

	auto fade = FadeOut::create(2.0f);
	auto move = MoveBy::create(2, Point(0, 150));
	auto spaw = Spawn::create(fade, move, NULL);
	damagelabel->runAction(spaw);
}
void DtopLayer2::mdamageeffect() {
	auto mx = bmon->getPositionX();
	auto my = bmon->getPositionY();

	std::string mdamageStr;
	if (mdamage == 0)
		mdamageStr = "MISS";
	else
		mdamageStr = std::to_string(mdamage);

	auto mdamagelabel = Label::createWithTTF(mdamageStr, "drfont.ttf", 50);
	mdamagelabel->setPosition(Point(mx -300, my + 700));
	mdamagelabel->enableOutline(Color4B::BLACK, 1);

	if (mdamage == PAtt - MDef && mdamage != 0)//일반공격
		mdamagelabel->setColor(Color3B(255, 255, 255));
	else if (mdamage>PAtt - MDef && MDef< PAtt) {
		mdamagelabel->setColor(Color3B(170, 18, 18));//검빨간색(크리티컬)
	}
	else if (mdamage == 0)//miss
		mdamagelabel->setColor(Color3B(255, 187, 0));//노란색

	this->addChild(mdamagelabel);

	auto fade = FadeOut::create(2.0f);
	auto move = MoveBy::create(2, Point(0, 150));
	auto spaw = Spawn::create(fade, move, NULL);
	mdamagelabel->runAction(spaw);
}
void DtopLayer2::DeleteMon() {
	std::string dt2_uname6 = dataSingleton::getInstance()->user;
	if (pD2->jjgetArray("read", dt2_uname6, 4) && pD2->jjgetQint("condition", dt2_uname6, 4) != pD2->jjgetQint("nowing", dt2_uname6, 4)) {
		auto nowing1 = pD2->jjgetQint("nowing", dt2_uname6, 4) + 1;
		std::string nowingStr1 = std::to_string(nowing1);
		auto condition1 = pD2->jjgetQint("condition", dt2_uname6, 4);
		std::string conditionStr1 = std::to_string(condition1);
		pD2->jjsetQint("nowing", dt2_uname6, nowing1, 4);
		char questing1[40];
		WideCharToMultiByte(CP_UTF8, 0, L"아버지의 단서 ( ", -1, questing1, 1024, NULL, NULL);
		auto questlabel1 = Label::createWithTTF(questing1 + nowingStr1 + " / " + conditionStr1 + " )", "nanumgo.ttf", 40);
		questlabel1->setAnchorPoint(Point(0.5, 0.5));
		questlabel1->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, 800));
		this->addChild(questlabel1);

		auto fade1 = FadeOut::create(5.0f);
		auto move1 = MoveBy::create(5, Point(0, 50));
		auto spaw1 = Spawn::create(move1, fade1, NULL);

		questlabel1->runAction(spaw1);

	}
	bmon->stopActionByTag(MonsterAttackMotion);
	bmon->stopActionByTag(MonsterStandMotion);
	dataSingleton::getInstance()->bosskill = true;
	//this->removeChild(bmon);
	this->removeChild(MHPS);
	this->removeChild(mhps_back);
}
void DtopLayer2::item()
{}
void DtopLayer2::pill()
{}

void DtopLayer2::skillCrush() {
	std::string dt2_uname4 = dataSingleton::getInstance()->user;
	if (skill_eff->isVisible() && bmon->isVisible()) {
		
		auto skillx = skill_eff->getPositionX();
		auto skilly = skill_eff->getPositionY();
		auto mx = bmon->getPositionX();
		
		auto atk = pD2->jjgetInt("atk", dt2_uname4);
		//스킬이 몬스터에게 들어감
		switch (skillid) {
		case 0: {


			auto skillRect = Rect(skillx, skilly, 1000, 162);
			auto skillmod = skillhit % 5;

			skillhit++;
			auto skillefftrue = skill_eff->isVisible();
			auto maxhit = 6;//json에서 가져와야한다. 지금 보니까 스킬에 관한 함수를 아예 따로 만들어서
							//키아이디로 해당 스킬에 관련된 정보만을 함수에서 가져오는 형태로 연구해야 할듯하다.
			if (MHP > 0) {
				if (skillRect.intersectsRect(mRect) && skillefftrue && skillhit <= maxhit * 5 && skillmod == 0 && MHP > 0) {

					auto particle = ParticleSystemQuad::create("skillmonatk.plist");
					particle->setDuration(0.05);
					particle->setPosition(Point(mx - 300, 200));
					this->addChild(particle);
					auto skilleff = pD2->jjgetAry("effect", "skill", "skill", skillid);

					mdamage = (atk*skilleff) / 100 - MDef;
					if (mdamage <= 0) {
						mdamage = 0;
					}

					if (MHP > mdamage)
					{
						MHP = MHP - mdamage;
					}
					else if (MHP <= mdamage)
					{
						MHP = 0;
					}
					mdamageeffect();


					//MHPS1->setPercentage(mhppercent1);
					float cu1 = MHPS->getPercentage();
					cu1 = (MHP / 3000) * 100;

					MHPS->setPercentage(cu1);
					String *str = String::createWithFormat("%.0f", MHP);
					MHPnum->setString(str->getCString());

					if (MHP <= 0) {

						auto fade = FadeOut::create(2.0);
						auto item = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::item, this));
						auto pill = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::pill, this));
						auto dis = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::DeleteMon, this));
						auto giveexp = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::giveexp, this));
						auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
						auto s = Sequence::create(fade, sp, NULL);
						bmon->runAction(s);
					}
				}
			}
		}
		default: break;
		}

	}
}
void DtopLayer2::MskillList(Ref* sender, int n) {
	std::string dt2_uname5 = dataSingleton::getInstance()->user;
	int num = n;
	auto def = pD2->jjgetInt("def", dt2_uname5);
	auto defst = pD2->jjgetInt("defst", dt2_uname5);
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();
	
	PDef = (rand() % (defst + 1)) + def;//def 100 defst30 100~130
	auto mhit = 0;

	switch (num) {
	case 0: {
		
		//찌르기
		auto sanimation0 = Animation::create();
		sanimation0->setDelayPerUnit(0.2);
		sanimation0->addSpriteFrameWithFile("mandra_a11.png");
		sanimation0->addSpriteFrameWithFile("mandra_a12.png");
		auto sanimate0 = Animate::create(sanimation0);
		sanimate0->setTag(MonsterAttackMotion);
		bmon->runAction(sanimate0);

		auto a1Rect = Rect(1100, 100, 500, 913);
		if (pRect.intersectsRect(a1Rect) && PHP>0) {
			auto particleblood = ParticleSystemQuad::create("blood.plist");
			particleblood->setDuration(0.2);
			particleblood->setPosition(Point(px, py + 45));
			this->addChild(particleblood);
			if (PDef<MAtt*2)
				damage = MAtt*1.8 - PDef;
			else
				damage = 0;
			PHP = PHP - damage;
			dataSingleton::getInstance()->pHP = PHP;
			damageeffect();
		}

		break;
	}
	case 1: {
		//나무발사
		
		auto moveactionup= MoveBy::create(0.05, Point(0, 800));
		auto moveactiondown = MoveBy::create(0.05, Point(0, -800));
		auto movedt = DelayTime::create(0.5);
		auto moveseq = Sequence::create(moveactionup, movedt, moveactiondown, NULL);
		root->runAction(moveseq);

		auto rootRect = Rect(beforepx, 280, 211, 584);
		if (pRect.intersectsRect(rootRect) && PHP>0) {
			auto particleblood = ParticleSystemQuad::create("blood.plist");
			particleblood->setDuration(0.2);
			particleblood->setPosition(Point(px, py + 45));
			this->addChild(particleblood);
			if (PDef<MAtt)
				damage = MAtt - PDef;
			else
				damage = 0;
			PHP = PHP - damage;
			damageeffect();
			dataSingleton::getInstance()->pHP = PHP;
		}
		break;
	}
	case 2: {
		auto gas = ParticleSystemQuad::create("gas.plist");
		gas->setDuration(5.0);
		gas->setPosition(Point(1200, 320));
		this->addChild(gas);
		isgas = true;
		gascu = true;
		auto callisgas = CallFuncN::create(CC_CALLBACK_0(DtopLayer2::callisgas, this));
		auto gasdt = DelayTime::create(5.0);
		auto gasse = Sequence::create(gasdt, callisgas,NULL);
		this->runAction(gasse);
		break;
	}
	}

}
void DtopLayer2::monSkillend() {
	bmon->stopActionByTag(MonsterAttackMotion);
	mSkilltrue = false;
	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.5);
	animation1->addSpriteFrameWithFile("mandra1.png");
	animation1->addSpriteFrameWithFile("mandra2.png");
	animation1->addSpriteFrameWithFile("mandra3.png");
	auto animate1 = Animate::create(animation1);
	auto act1 = RepeatForever::create(animate1);
	act1->setTag(MonsterStandMotion);
	bmon->runAction(act1);
}

void DtopLayer2::callClear() {
	auto clearLayer =clearLayer::create();
	this->addChild(clearLayer);

}

void DtopLayer2::callisgas() {
	isgas = false;
}

void DtopLayer2::callgascu() {
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();
	auto gasRect = Rect(1200, 320, 450, 150);

	//독가스.
	if (pRect.intersectsRect(gasRect) && PHP>0) {
		damage = 5;
		PHP = PHP - damage;
		damageeffect();
		dataSingleton::getInstance()->pHP = PHP;

	}
	gascu = true;
}