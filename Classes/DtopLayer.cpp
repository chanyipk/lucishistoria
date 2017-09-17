#include "GameScene.h"
#include "DtopLayer.h"
#include "dataSingleton.h"
#include "Jdata.h"
#include "ElyonScene.h"
#include "UserLayer.h"

Jdata* pD;

int yindex = 1;
bool up = false;
bool down = false;
bool notfirst = false;
bool notfloor = false;

bool DtopLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//초기화

	y[0] = 280;
	MAtt = 140;
	MDef = 80;
	MHP1 = 500;
	MHP2 = 500;
	MHP3 = 500;
	MHP4 = 700;
	MHP5 = 700;
	mhppercent1 = 100;
	mhppercent2 = 100;
	mhppercent3 = 100;
	mhppercent4 = 100;
	mhppercent5 = 100;


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
	Matt1 = false;
	Matt2 = false;
	Matt3 = false;
	Matt4 = false;
	leafcru1 = false;
	leafcru2 = false;
	leafcru3 = false;
	gameovertrue = false;
	dataSingleton::getInstance()->playerDead = false;


	// 땅 배치
	ground1 = Sprite::create("floor1.png");
	ground1->setAnchorPoint(Point(0, 0));
	ground1->setPosition(Point(0, 0));
	this->addChild(ground1);

	ground3 = Sprite::create("floor3.png");
	ground3->setAnchorPoint(Point(0, 0));
	ground3->setPosition(Point(2000, 250));
	this->addChild(ground3);

	groundnext1 = Sprite::create("floor3.png");
	groundnext1->setAnchorPoint(Point(0, 0));
	groundnext1->setPosition(Point(8500, 250));
	this->addChild(groundnext1);

	groundnext2 = Sprite::create("floor3.png");
	groundnext2->setAnchorPoint(Point(0, 0));
	groundnext2->setPosition(Point(8000, 650));
	this->addChild(groundnext2);

	ground2 = Sprite::create("floor2.png");
	ground2->setAnchorPoint(Point(0, 0));
	ground2->setPosition(Point(0, 934));
	this->addChild(ground2);


	//voidNode설정 
	voidNode = ParallaxNode::create();
	//	voidNode->addChild(ground1, 1, Point(1.0f, 0.0f), Point(0, 0));
	voidNode->setTag(1);
	this->addChild(voidNode, 0);



	//몬스터 배치
	//몬스터1
	sm1 = Sprite::create("m1.png");//몬스터 기준점
	sm1->setAnchorPoint(Point(0.5, 0.5));
	sm1->setPosition(Point(1000, 240));
	sm1->setVisible(false);
	this->addChild(sm1);

	sprM1 = Sprite::create("m1.png");
	sprM1->setAnchorPoint(Point(0.5, 0.5));
	sprM1->setPosition(Point(1000, 240));
	this->addChild(sprM1);



	//몬스터2
	sm2 = Sprite::create("m1.png");//몬스터 기준점
	sm2->setAnchorPoint(Point(0.5, 0.5));
	sm2->setPosition(Point(2700, 240));
	sm2->setVisible(false);
	this->addChild(sm2);

	sprM2 = Sprite::create("m1.png");
	sprM2->setAnchorPoint(Point(0.5, 0.5));
	sprM2->setPosition(Point(2700, 240));
	this->addChild(sprM2);

	//몬스터3
	sm3 = Sprite::create("m1.png");//몬스터 기준점
	sm3->setAnchorPoint(Point(0.5, 0.5));
	sm3->setPosition(Point(5000, 240));
	sm3->setVisible(false);
	this->addChild(sm3);

	sprM3 = Sprite::create("m1.png");
	sprM3->setAnchorPoint(Point(0.5, 0.5));
	sprM3->setPosition(Point(5000, 240));
	this->addChild(sprM3);

	//몬스터 나무 배치
	sm4 = Sprite::create("tree.png");
	sm4->setAnchorPoint(Point(0.5, 0.5));
	sm4->setPosition(Point(1900, 240));
	sm4->setVisible(false);
	sm4->setScale(0.8);
	this->addChild(sm4);

	sprM4 = Sprite::create("tree.png");
	sprM4->setAnchorPoint(Point(0.5, 0.5));
	sprM4->setPosition(Point(1900, 240));
	sprM4->setScale(0.8);
	this->addChild(sprM4);

	sm5 = Sprite::create("tree.png");
	sm5->setAnchorPoint(Point(0.5, 0.5));
	sm5->setPosition(Point(4500, 240));
	sm5->setVisible(false);
	sm5->setScale(0.8);
	this->addChild(sm5);

	sprM5 = Sprite::create("tree.png");
	sprM5->setAnchorPoint(Point(0.5, 0.5));
	sprM5->setPosition(Point(4500, 240));
	sprM5->setScale(0.8);
	this->addChild(sprM5);

	//몬스터 설정
	setEnemy();

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
	//포션배치
	red1 = Sprite::create("hppotion.png");
	red1->setTag(REDP);
	red1->setPosition(Point(0, 0));
	red1->setScale(0.8);
	red1->setVisible(false);
	this->addChild(red1);

	red2 = Sprite::create("hppotion.png");
	red2->setTag(REDP);
	red2->setPosition(Point(0, 0));
	red2->setScale(0.8);
	red2->setVisible(false);
	this->addChild(red2);

	red3 = Sprite::create("hppotion.png");
	red3->setTag(REDP);
	red3->setPosition(Point(0, 0));
	red3->setScale(0.8);
	red3->setVisible(false);
	this->addChild(red3);

	steel1 = Sprite::create("steel.png");
	steel1->setTag(STEEL);
	steel1->setPosition(Point(0, 0));
	steel1->setVisible(false);
	this->addChild(steel1);

	steel2 = Sprite::create("steel.png");
	steel2->setTag(STEEL);
	steel2->setPosition(Point(0, 0));
	steel2->setVisible(false);
	this->addChild(steel2);

	blue1 = Sprite::create("mppotion.png");
	blue1->setTag(BLUEP);
	blue1->setPosition(Point(0, 0));
	blue1->setScale(0.8);
	blue1->setVisible(false);
	this->addChild(blue1);

	blue2 = Sprite::create("mppotion.png");
	blue2->setTag(BLUEP);
	blue2->setPosition(Point(0, 0));
	blue2->setScale(0.8);
	blue2->setVisible(false);
	this->addChild(blue2);

	blue3 = Sprite::create("mppotion.png");
	blue3->setTag(BLUEP);
	blue3->setPosition(Point(0, 0));
	blue3->setScale(0.8);
	blue3->setVisible(false);
	this->addChild(blue3);

	//돈배치
	money1 = Sprite::create("money.png");
	money1->setTag(MONEY);
	money1->setPosition(0, 0);
	this->addChild(money1);

	money2 = Sprite::create("money.png");
	money2->setTag(MONEY);
	money2->setPosition(0, 0);
	this->addChild(money2);

	money3 = Sprite::create("money.png");
	money3->setTag(MONEY);
	money3->setPosition(0, 0);
	this->addChild(money3);

	money4 = Sprite::create("money.png");
	money4->setTag(MONEY);
	money4->setPosition(0, 0);
	this->addChild(money4);

	money5 = Sprite::create("money.png");
	money5->setTag(MONEY);
	money5->setPosition(0, 0);
	this->addChild(money5);

	//플레이어 설정

	playerSpr = Sprite::create("a1.png");
	playerSpr->setPosition(Point(200, 280));
	playerSpr->setTag(TAG_PLAYER_SPRITE);
	this->addChild(playerSpr);//여기 this는 TopLayer입니다.
	playerStandAction();

	/*std::string dtop_uname = dataSingleton::getInstance()->user;
	//plyr_lb = Label::create();
	int lev = pD->jjgetInt("level", dtop_uname);
	std::string lev_lb = std::to_string(lev);
	plyr_lb = Label::createWithTTF("Lv." + lev_lb + " " + dtop_uname, "nanumgo.ttf", 15);

	plyr_lb->enableOutline(Color4B::BLACK, 2);
	plyr_lb->setAnchorPoint(Point(0.5, 0));
	plyr_lb->setPosition(Point(0, 0));
	playerSpr->addChild(plyr_lb);
	*/

	auto mL = Label::createWithTTF("잡은 몬스터 : ", "nanumgo.ttf", 40);
	mL->setAnchorPoint(Point(0, 0));
	mL->setPosition(Point(100, 800));
	mL->setColor(Color3B::WHITE);
	this->addChild(mL);

	count = Label::createWithTTF("0 / 5", "nanumgo.ttf", 40);
	count->setAnchorPoint(Point(0, 0));
	count->setPosition(Point(350, 800));
	count->setColor(Color3B::WHITE);
	this->addChild(count);

	//키보드 호출
	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(DtopLayer::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(DtopLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listner, this);


	this->scheduleUpdate();

	auto UserLayer = UserLayer::create();
	this->addChild(UserLayer);


	return true;
}

//키 눌렀을 때 이벤트
void DtopLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	std::string dt_uname1 = dataSingleton::getInstance()->user;
	auto player = (Sprite*)this->getChildByTag(TAG_PLAYER_SPRITE);
	auto pHP = dataSingleton::getInstance()->pHP;
	if (pHP>0) {
		switch (keyCode) {//키 코드값 확인
		case EventKeyboard::KeyCode::KEY_1:
		{
			auto maxPHP = pD->jjgetInt("maxhp", dt_uname1);
			auto PHP = pD->jjgetInt("hp", dt_uname1);
			if (dataSingleton::getInstance()->redcount > 0 && PHP > 0 && PHP < maxPHP) {
				dataSingleton::getInstance()->redcount -= 1;

				if (PHP + 200 > maxPHP)
					dataSingleton::getInstance()->pHP = maxPHP;
				else
					dataSingleton::getInstance()->pHP = dataSingleton::getInstance()->pHP + 200;
		
				for (int i = 0; i < 4; i++) {
					auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
					if (pid == 0) {
						pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->redcount,i);
						break;
					}
				}
				
				pD->jjsetInt(dataSingleton::getInstance()->pHP, "hp", dt_uname1);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_2:
		{
			auto maxPMP = pD->jjgetInt("maxmp", dt_uname1);
			auto PMP = pD->jjgetInt("mp", dt_uname1);
			if (dataSingleton::getInstance()->bluecount > 0 && PMP > 0 && PMP < maxPMP) {
				dataSingleton::getInstance()->bluecount -= 1;

				if (PMP + 200 > maxPMP)
					dataSingleton::getInstance()->pMP = maxPMP;
				else
					dataSingleton::getInstance()->pMP = dataSingleton::getInstance()->pMP + 200;
				for (int i = 0; i < 4; i++) {
					auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
					if (pid == 1) {
						pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->bluecount, i);
						break;
					}
				}
				pD->jjsetInt(dataSingleton::getInstance()->pMP, "mp", dt_uname1);
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
				auto action = Sequence::create(JumpBy::create(1.0, Point(0, 0), 350, 1), CallFuncN::create(CC_CALLBACK_0(DtopLayer::JumpEnd, this)), NULL);
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


			auto PMP = dataSingleton::getInstance()->pMP;
			skillid = pD->jjgetInt("skill1", dt_uname1);
			if (skillid != 999) {
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_ATTACK);
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_STAND);
				auto skillmp = pD->jjgetAry("skillmp", "skill", "skill", skillid);
				auto skilltime = dataSingleton::getInstance()->skillpressedA;
				if (!skillYN && PMP - skillmp > 0 && !skilltime) {
					skillhit = 0;
					isAPressed = true;
					dataSingleton::getInstance()->skillpressedA = true;
					skillYN = true;
					skillList(this, skillid);
					PMP = PMP - skillmp;
					dataSingleton::getInstance()->pMP = PMP;
					pD->jjsetInt(PMP, "mp", dt_uname1);
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
		case EventKeyboard::KeyCode::KEY_S: {


			auto PMP = dataSingleton::getInstance()->pMP;
			skillid = pD->jjgetInt("skill2", dt_uname1);
			if (skillid != 999) {
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_ATTACK);
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_UP);
				playerSpr->stopActionByTag(TAG_SPRITE_PLAYER_ACTION_STAND);
				auto skillmp = pD->jjgetAry("skillmp", "skill", "skill", skillid);
				auto skilltime = dataSingleton::getInstance()->skillpressedS;
				if (!skillYN && PMP - skillmp > 0 && !skilltime) {
					skillhit = 0;
					isAPressed = true;
					dataSingleton::getInstance()->skillpressedS = true;
					skillYN = true;
					skillList(this, skillid);
					PMP = PMP - skillmp;
					dataSingleton::getInstance()->pMP = PMP;
					pD->jjsetInt(PMP, "mp", dt_uname1);
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
					auto jaction1 = Sequence::create(CallFuncN::create(CC_CALLBACK_1(DtopLayer::PattackMcrush, this)), animate, NULL);
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
						auto rjaction1 = Sequence::create(CallFuncN::create(CC_CALLBACK_1(DtopLayer::PattackMcrush, this)), animate, NULL);
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
					action1 = Sequence::create(CallFuncN::create(CC_CALLBACK_1(DtopLayer::PattackMcrush, this)), animate1, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer::AttackEnd, this)), NULL);//att2==true가 동시다발로 일어나기 때문에 순차적으로 하기위해서 시퀀스가 필요, 저 값에 대한 행동을 할 수 있도록 함수를 만들자
					playerSpr->runAction(action1);



				}
				else if (isAttack == 2)
				{
					att2 = true;
					DelayTime *dt = DelayTime::create(0.2f);
					DelayTime *dt2 = DelayTime::create(0.05f);
					action2 = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(DtopLayer::PattackMcrush, this)), animate2, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer::AttackEnd, this)), NULL);
					playerSpr->runAction(action2);


				}
				else if (isAttack == 3)
				{
					att3 = true;
					DelayTime *dt = DelayTime::create(0.4f);
					DelayTime *dt2 = DelayTime::create(0.05f);
					action3 = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(DtopLayer::PattackMcrush, this)), animate3, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer::AttackEnd, this)), NULL);
					playerSpr->runAction(action3);

				}
				else if (isAttack == 4)
				{
					DelayTime *dt = DelayTime::create(0.6f);
					DelayTime *dt2 = DelayTime::create(0.05f);
					action4 = Sequence::create(dt, CallFuncN::create(CC_CALLBACK_1(DtopLayer::PattackMcrush, this)), animate4, dt2, CallFuncN::create(CC_CALLBACK_1(DtopLayer::AttackEnd, this)), NULL);
					playerSpr->runAction(action4);
				}

			}
			//else if{ 좌우방향키 눌러져있을 경우, 안눌러져 있을경우}
			break;
		}

		//아이템 줍기
		case EventKeyboard::KeyCode::KEY_C: {


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
			char steel[30];
			WideCharToMultiByte(CP_UTF8, 0, L" 철조각X", -1, steel, 1024, NULL, NULL);

			auto havemoney = pD->jjgetInt("money", dt_uname1);

			if (money1->isVisible())
			{
				auto item_box1 = money1->getBoundingBox();

				if (play_box.intersectsRect(item_box1)) {

					money1->setVisible(false);
					int money_r = rand() % 10 + 5;//5~14
					int money_rand = money_r * 100;//500~1400
					havemoney += money_rand;
					pD->jjsetInt(havemoney, "money", dt_uname1);



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
					pD->jjsetInt(havemoney, "money", dt_uname1);
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
					pD->jjsetInt(havemoney, "money", dt_uname1);
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
					pD->jjsetInt(havemoney, "money", dt_uname1);
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
					pD->jjsetInt(havemoney, "money", dt_uname1);
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
					for (int i = 0; i < 4; i++) {
						auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
						if (pid == 0) {
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->redcount, i);
							break;
						}
						else if (pid == 999) {
							pD->jjsetpArray("keyid", dt_uname1, 0, i);
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->redcount, i);
							break;
						}
					}
				
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
					for (int i = 0; i < 4; i++) {
						auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
						if (pid == 0) {
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->redcount, i);
							break;
						}
						else if (pid == 999) {
							pD->jjsetpArray("keyid", dt_uname1, 0, i);
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->redcount, i);
							break;
						}
					}
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
					for (int i = 0; i < 4; i++) {
						auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
						if (pid == 0) {
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->redcount, i);
							break;
						}
						else if (pid == 999) {
							pD->jjsetpArray("keyid", dt_uname1, 0, i);
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->redcount, i);
							break;
						}
					}
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

			if (steel1->isVisible()) {
				auto steel_box1 = steel1->getBoundingBox();
				int steelnum = rand() % 3 + 1;
				std::string steelnumStr = std::to_string(steelnum);
				if (play_box.intersectsRect(steel_box1)) {
					dataSingleton::getInstance()->steelcount += steelnum;
					for (int i = 0; i < 4;) {
						int itemid = pD->jjgetAry("keyid", "useritem", dt_uname1, i);
						if (itemid == 999) {
							pD->jjsetAry("holding", "useritem", dt_uname1, 1, i);
							pD->jjsetAry("keyid", "useritem", dt_uname1, 0, i);
							break;
						}
						else if (itemid == 0) {//0번은 steel아이템을 의미함
							pD->jjsetAry("holding", "useritem", dt_uname1, dataSingleton::getInstance()->steelcount, i);
							break;
						}
						else i++;
					}
					steel1->setVisible(false);

					auto steellabel = Label::createWithTTF(steel + steelnumStr + potionget, "nanumgo.ttf", 30);
					steellabel->setAnchorPoint(Point(0, 0));
					steellabel->setPosition(100, 250);
					this->addChild(steellabel);

					auto dtr = DelayTime::create(3.0);
					auto fdr = FadeOut::create(2.0);
					auto seqr = Sequence::create(dtr, fdr, NULL);
					steellabel->runAction(seqr);
				}
			}

			if (steel2->isVisible()) {
				auto steel_box2 = steel2->getBoundingBox();
				int steelnum = rand() % 3 + 1;
				std::string steelnumStr = std::to_string(steelnum);
				if (play_box.intersectsRect(steel_box2)) {
					dataSingleton::getInstance()->steelcount += steelnum;
					for (int i = 0; i < 4;) {
						int itemid = pD->jjgetAry("keyid", "useritem", dt_uname1, i);
						if (itemid == 999) {
							pD->jjsetAry("holding", "useritem", dt_uname1, 1, i);
							pD->jjsetAry("keyid", "useritem", dt_uname1, 0, i);
							break;
						}
						else if (itemid == 0) {//0번은 steel아이템을 의미함
							pD->jjsetAry("holding", "useritem", dt_uname1, dataSingleton::getInstance()->steelcount, i);
							break;
						}
						else i++;
					}
					steel2->setVisible(false);

					auto steellabel = Label::createWithTTF(steel + steelnumStr + potionget, "nanumgo.ttf", 30);
					steellabel->setAnchorPoint(Point(0, 0));
					steellabel->setPosition(100, 250);
					this->addChild(steellabel);

					auto dtr = DelayTime::create(3.0);
					auto fdr = FadeOut::create(2.0);
					auto seqr = Sequence::create(dtr, fdr, NULL);
					steellabel->runAction(seqr);
				}
			}


			if (blue1->isVisible()) {

				auto blue_box1 = blue1->getBoundingBox();
				int bluenum = rand() % 3 + 1;
				std::string bluenumStr = std::to_string(bluenum);
				if (play_box.intersectsRect(blue_box1)) {
					dataSingleton::getInstance()->bluecount += bluenum;
					for (int i = 0; i < 4; i++) {
						auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
						if (pid == 1) {
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->bluecount, i);
							break;
						}
						else if (pid == 999) {
							pD->jjsetpArray("keyid", dt_uname1, 1, i);
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->bluecount, i);
							break;
						}
					}
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
					for (int i = 0; i < 4; i++) {
						auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
						if (pid == 1) {
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->bluecount, i);
							break;
						}
						else if (pid == 999) {
							pD->jjsetpArray("keyid", dt_uname1, 1, i);
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->bluecount, i);
							break;
						}
					}
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
					for (int i = 0; i < 4; i++) {
						auto pid = pD->jjgetAry("keyid", "userpotion", dt_uname1, i);
						if (pid == 1) {
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->bluecount, i);
							break;
						}
						else if (pid == 999) {
							pD->jjsetpArray("keyid", dt_uname1, 1, i);
							pD->jjsetpArray("holding", dt_uname1, dataSingleton::getInstance()->bluecount, i);
							break;
						}
					}
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
		}
		case EventKeyboard::KeyCode::KEY_I: {

			break;

		}
		default:
			break;
		}
	}
}

//키 땠을 때 이벤트
void DtopLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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
		//	rk->setTexture(Director::getInstance()->getTextureCache()->addImage("Rk.png"));
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
void DtopLayer::startMovingBackground()
{
	if (isLeftPressed == true && isRightPressed == true)
		return;//void인데 어떻게 리턴이 되는지 의문...? 뭔가 예외확인을 해주는 것 같은.. 하나만 vx면 if빠져나감..

	this->schedule(schedule_selector(DtopLayer::moveBackground));//스케쥴링 시작
}

//배경 멈춤
void DtopLayer::stopMovingBackground()
{
	this->unschedule(schedule_selector(DtopLayer::moveBackground));
}

void DtopLayer::moveBackground(float t)
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
	auto newPos2 = Point(voidNode->getPosition().x, voidNode->getPosition().y);
	float vx = voidNode->getPositionX();
	float vy = voidNode->getPositionY();

	if (floornum == 4 || floornum == 5) {
		if (up) {

			if (newPos.y > 300 && newPos.y < 700)
				newPos2.y -= 10;
		}
		else if (down) {
			if (newPos.y > 300 && newPos.y < 700)
				newPos2.y += 10;
		}

	}

	if (isRightPressed) {
		if (newPos.x > 1900) {
			newPos.x = 1900;
		}
		else if (newPos.x < 960) {
			newPos.x += moveStep; //캐릭터가 움직이는 듯
		}
		else {//배경이 움직임
			if (vx > -7680) {//-7680이라하면 이미지를 4배로 키웠을 경우 마지막 이미지칸에 해당할 때를 제외
				newPos2.x -= moveStep; // 배경이 움직임(왼쪽으로 여기서 vx는 voidnode의 x축값 gx값이 아닐까.
			}
			else {
				newPos.x += moveStep;//나머지는 캐릭터의 이동
			}
		}
	}
	else if (isLeftPressed) {
		if (newPos.x > 960) {
			newPos.x += moveStep;
		}
		else if (newPos.x < 20) {
			newPos.x = 20;
		}
		else {
			if (vx < 0) {
				newPos2.x -= moveStep;
			}
			else {
				newPos.x += moveStep;
			}
		}
	}




	voidNode->setPosition(newPos2);
	dataSingleton::getInstance()->groundx = newPos2.x;
	dataSingleton::getInstance()->groundy = newPos2.y;
	auto gx = dataSingleton::getInstance()->groundx;
	auto gy = dataSingleton::getInstance()->groundy;
	auto mx1 = dataSingleton::getInstance()->mon1x;
	auto mx2 = dataSingleton::getInstance()->mon2x;
	auto mx3 = dataSingleton::getInstance()->mon3x;
	auto mx4 = dataSingleton::getInstance()->mon4x;
	auto mx5 = dataSingleton::getInstance()->mon5x;

	playerSpr->setPosition(newPos);
	sprM1->setPosition(Point(gx + mx1, gy + 240));
	sprM2->setPosition(Point(gx + mx2, gy + 240));
	sprM3->setPosition(Point(gx + mx3, gy + 240));
	sprM4->setPosition(Point(gx + mx4, gy + 240));
	sprM5->setPosition(Point(gx + mx5, gy + 240));
	ground3->setPosition(Point(gx + 2000, gy + 300));
	groundnext1->setPosition(Point(gx + 8500, gy + 300));
	groundnext2->setPosition(Point(gx + 8000, gy + 700));
	ground2->setPosition(Point(gx, gy + 934));
	ground1->setPosition(Point(gx, gy));

	if (Matt1) {
		sprMa1->setPosition(Point(gx + mx1, gy + 240));
	}
	if (Matt2) {
		sprMa2->setPosition(Point(gx + mx2, gy + 240));
	}
	if (Matt3) {
		sprMa3->setPosition(Point(gx + mx3, gy + 240));
	}



	//충돌 박스를 위한 새로운 땅 위치 값들 dataSingleton에 저장
	dataSingleton::getInstance()->floorbox1X = ground3->getPositionX();
	dataSingleton::getInstance()->floorbox1Y = ground3->getPositionY();
	dataSingleton::getInstance()->floorbox2X = groundnext1->getPositionX();
	dataSingleton::getInstance()->floorbox2Y = groundnext1->getPositionY();
	dataSingleton::getInstance()->floorbox3X = groundnext2->getPositionX();
	dataSingleton::getInstance()->floorbox3Y = groundnext2->getPositionY();
	dataSingleton::getInstance()->floorbox4X = ground2->getPositionX();
	dataSingleton::getInstance()->floorbox4Y = ground2->getPositionY();
}

void DtopLayer::playerRisen()
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
void DtopLayer::update(float delta)
{
	std::string dt_uname2 = dataSingleton::getInstance()->user;
	if (kill == 5)
	{
		/*this->removeChild(count);
		auto clear = LabelTTF::create("CLEAR","nanumgo.ttf",50);
		clear->setPosition(Point(100, 450));
		clear->setAnchorPoint(Point(0, 0));
		this->addChild(clear);*/

		

		/*auto back = LabelTTF::create("던전 클리어. 마을로 이동합니다.", "nanumgo.ttf", 70);
		back->setPosition(Point(650, 850));
		back->setAnchorPoint(Point(0, 0));
		this->addChild(back);

		auto del = DelayTime::create(1.5);
		auto fad = FadeOut::create(1.0);
		auto del2 = DelayTime::create(2.0);
		auto chan = CallFuncN::create(CC_CALLBACK_0(DtopLayer::changeScene, this));
		auto seq = Sequence::create(del, fad, del2, chan, NULL);
		back->runAction(seq);
		*/
		auto del0 = DelayTime::create(5.0);
		auto clearB = CallFuncN::create(CC_CALLBACK_0(DtopLayer::clearBack, this));
		auto del = DelayTime::create(1.5);
		auto clearL = CallFuncN::create(CC_CALLBACK_0(DtopLayer::clearLabel, this));
		auto del2 = DelayTime::create(3.0);
		auto chan = CallFuncN::create(CC_CALLBACK_0(DtopLayer::changeScene, this));
		auto seq = Sequence::create(del0,clearB,del,clearL, del2, chan, NULL);
		this->runAction(seq);

		kill = 0;
	}

	dataSingleton::getInstance()->x = playerSpr->getPositionX();
	dataSingleton::getInstance()->y = playerSpr->getPositionY();
	itemposition();

	dataSingleton::getInstance()->steelcount = pD->jjgetAry("holding", "useritem", dt_uname2, 0);

	if (dataSingleton::getInstance()->risen == true)
	{
		playerRisen();
	}

/*	int lev = pD->jjgetInt("level", dt_uname2);
	std::string lev_lb = std::to_string(lev);
	plyr_lb->setString("Lv." + lev_lb + " " + dt_uname2);
	*/
	auto mPos1 = Point(sm1->getPositionX(), sm1->getPositionY());//현재 몬스터1 위치값
	dataSingleton::getInstance()->mon1x = mPos1.x;//몬스터1의 x값 갱신
	auto mPos2 = Point(sm2->getPositionX(), sm2->getPositionY());
	dataSingleton::getInstance()->mon2x = mPos2.x;
	auto mPos3 = Point(sm3->getPositionX(), sm3->getPositionY());
	dataSingleton::getInstance()->mon3x = mPos3.x;
	auto mPos4 = Point(sm4->getPositionX(), sm4->getPositionY());
	dataSingleton::getInstance()->mon4x = mPos4.x;
	auto mPos5 = Point(sm5->getPositionX(), sm5->getPositionY());
	dataSingleton::getInstance()->mon5x = mPos5.x;


	auto mx1 = sprM1->getPositionX();
	auto my1 = sprM1->getPositionY();
	mRect1 = Rect(mx1 - 200, my1, 200, 217);//몬스터 충돌 박스

	auto mx2 = sprM2->getPositionX();
	auto my2 = sprM2->getPositionY();
	mRect2 = Rect(mx2 - 200, my2, 200, 217);//몬스터 충돌 박스

	auto mx3 = sprM3->getPositionX();
	auto my3 = sprM3->getPositionY();
	mRect3 = Rect(mx3 - 200, my3, 200, 217);//몬스터 충돌 박스

	auto mx4 = sprM4->getPositionX();
	auto my4 = sprM4->getPositionY();
	mRect4 = Rect(mx4, my4, 600, 217);//몬스터 충돌 박스

	auto mx5 = sprM5->getPositionX();
	auto my5 = sprM5->getPositionY();
	mRect5 = Rect(mx5, my5, 600, 217);//몬스터 충돌 박스

	playertrue = playerSpr->isVisible();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();
	pRect = Rect(px - 600, py, 900, 300);//플레이어 충돌박스
	pgRect = Rect(px - 40, py, 440, 10);
	pdropRect = Rect(px - 40, py, 440, 10);

	//박스 위치들을 dataSingleton으로 해서 movebackground에서 가져와야 할듯
	auto gx1 = ground1->getPositionX();
	auto gy1 = ground1->getPositionY();
	ground1box = Rect(gx1, gy1, 9680, 300);

	auto gx3 = dataSingleton::getInstance()->floorbox1X;
	auto gy3 = dataSingleton::getInstance()->floorbox1Y;
	ground3box = Rect(gx3 + 400, gy3 + 270, 520, 50);
	//	ground3jumpbox = Rect(gx3+400, gy3+300, 500, 450);

	auto gx2 = dataSingleton::getInstance()->floorbox4X;
	auto gy2 = dataSingleton::getInstance()->floorbox4Y;
	ground2box = Rect(gx2 + 400, gy2 + 270, 8000, 50);
	//	ground2jumpbox = Rect(gx2 + 400, gy2 + 300, 8000, 450);

	auto gnextx1 = dataSingleton::getInstance()->floorbox2X;
	auto gnexty1 = dataSingleton::getInstance()->floorbox2Y;
	groundnext1box = Rect(gnextx1 + 400, gnexty1 + 270, 500, 50);
	//	groundnext1jumpbox = Rect(gnextx1 + 400, gnexty1 + 300, 500,450);

	auto gnextx2 = dataSingleton::getInstance()->floorbox3X;
	auto gnexty2 = dataSingleton::getInstance()->floorbox3Y;
	groundnext2box = Rect(gnextx2 + 400, gnexty2 + 270, 500, 50);
	//	groundnext2jumpbox = Rect(gnextx2+400 , gnexty2 + 300, 500, 450);

	if (skill_eff) {
		skillCrush();

	}

	floornumCheck();//캐릭터 위치 파악
	playerDrop();//추락판정
	PlayerMonCruch();//캐릭터 몬스터 충돌


	playertrue = playerSpr->isVisible();

	sprM1true = sprM1->isVisible();
	sprM2true = sprM2->isVisible();
	sprM3true = sprM3->isVisible();
	//sprM4true = sprM4->isVisible();
	if (sprMa1)
		sprMa1true = sprMa1->isVisible();
	if (sprMa2)
		sprMa2true = sprMa2->isVisible();
	if (sprMa3)
		sprMa3true = sprMa3->isVisible();


	//플레이어 정보
	PHP = dataSingleton::getInstance()->pHP;
	PEXP = dataSingleton::getInstance()->pEXP;

	//몬스터1 플레이어 공격 들어감
	if (leafatk1) {
		leafx1 = leafatk1->getPositionX();
		leafy1 = leafatk1->getPositionY();
		//	dataSingleton::getInstance()->Mleafx1 = leafx1;
		auto px = playerSpr->getPositionX();
		auto py = playerSpr->getPositionY();
		auto playerRect = Rect(px, 200, 90, 290);
		leafRect1 = Rect(leafx1, leafy1, 54, 44);

		auto def = pD->jjgetInt("def", dt_uname2);
		auto defst = pD->jjgetInt("defst", dt_uname2);
		PDef = (rand() % (defst + 1)) + def;//def 100 defst30 100~130
		if (PDef<MAtt)
			damage = MAtt - PDef;
		else
			damage = 0;

		bool leaftrue1 = leafatk1->isVisible();
		if (leafRect1.intersectsRect(playerRect) && leaftrue1) {

			leafatk1->setVisible(false);
			mparticle1 = ParticleSystemQuad::create("matteffect.plist");
			mparticle1->setDuration(0.2);
			mparticle1->setPosition(Point(leafx1, 200));
			this->addChild(mparticle1);


			if (PHP > 0 && !skillYN) {
				playerSpr->setVisible(true);
				PHP = PHP - damage; //몬스터 공격 들어가서 체력 깎임
				damageeffect();
				dataSingleton::getInstance()->pHP = PHP;
			


			}

		}
	}

	// 트리몬과 캐릭터 충돌 시 캐릭터 체력 감소
	if (sprM4->isVisible())
	{
		auto px = playerSpr->getPositionX();
		auto py = playerSpr->getPositionY();
		auto playerRect = Rect(px - 100, 200, 200, 290);
		if (playerRect.intersectsRect(mRect4) && PHP > 0) {  // delay변수로 중간에 시간텀을 안주면 빠르게 update되는 시스템상, 
															 // 캐릭터 체력이 너무 금방 담.

			delay = delay - 1;

			if (delay == 0)
			{
				damage = 100;
				PHP = PHP - damage; //몬스터 공격 들어가서 체력 깎임				
				dataSingleton::getInstance()->pHP = PHP;
				damageeffect();
				delay = 50;
			}

		}
	}

	if (sprM5->isVisible())
	{
		auto px = playerSpr->getPositionX();
		auto py = playerSpr->getPositionY();
		auto playerRect = Rect(px - 100, 200, 200, 290);
		if (playerRect.intersectsRect(mRect5) && PHP > 0) {  // delay변수로 중간에 시간텀을 안주면 빠르게 update되는 시스템상, 
															 // 캐릭터 체력이 너무 금방 담.

			delay2 = delay2 - 1;

			if (delay2 == 0)
			{
				damage = 100;
				PHP = PHP - damage;//몬스터 공격 들어가서 체력 깎임				
				dataSingleton::getInstance()->pHP = PHP;
				damageeffect();
				delay2 = 50;
			}

		}
	}


	//몬스터2 플레이어 공격 들어감
	if (leafatk2) {
		leafx2 = leafatk2->getPositionX();
		leafy2 = leafatk2->getPositionY();
		//	dataSingleton::getInstance()->Mleafx2 = leafx2;
		auto px = playerSpr->getPositionX();
		auto py = playerSpr->getPositionY();
		auto playerRect = Rect(px, 200, 90, 290);
		leafRect2 = Rect(leafx2, leafy2, 54, 44);

		bool leaftrue2 = leafatk2->isVisible();
		if (leafRect2.intersectsRect(playerRect) && leaftrue2) {

			leafatk2->setVisible(false);
			mparticle2 = ParticleSystemQuad::create("matteffect.plist");
			mparticle2->setDuration(0.2);
			mparticle2->setPosition(Point(leafx2, 200));
			this->addChild(mparticle2);


			if (PHP > 0 && !skillYN) {
				playerSpr->setVisible(true);
				PHP = PHP - damage; //몬스터 공격 들어가서 체력 깎임
				damageeffect();
				dataSingleton::getInstance()->pHP = PHP;

			}

		}
	}

	//몬스터3 플레이어 공격 들어감
	if (leafatk3) {
		leafx3 = leafatk3->getPositionX();
		leafy3 = leafatk3->getPositionY();
		//	dataSingleton::getInstance()->Mleafx3 = leafx3;
		auto px = playerSpr->getPositionX();
		auto py = playerSpr->getPositionY();
		auto playerRect = Rect(px, 200, 90, 290);
		leafRect3 = Rect(leafx3, leafy3, 54, 44);

		bool leaftrue3 = leafatk3->isVisible();
		if (leafRect3.intersectsRect(playerRect) && leaftrue3) {

			leafatk3->setVisible(false);
			mparticle3 = ParticleSystemQuad::create("matteffect.plist");
			mparticle3->setDuration(0.2);
			mparticle3->setPosition(Point(leafx3, 200));
			this->addChild(mparticle3);


			if (PHP > 0 && !skillYN) {
				playerSpr->setVisible(true);
				PHP = PHP - damage; //몬스터 공격 들어가서 체력 깎임
				damageeffect();
				dataSingleton::getInstance()->pHP = PHP;


			}

		}
	}


	if (dataSingleton::getInstance()->pHP <= 0 && !gameovertrue) {
		auto action = Sequence::create(CallFuncN::create(CC_CALLBACK_0(DtopLayer::playerDis, this)), NULL);
		this->runAction(action);
		gameovertrue = true;
	}

	//점프할 때 착지를 위한 y축 검사
	if (jumpYN) {
		up = false;
		down = false;
		auto py = playerSpr->getPositionY();
		a[0] = py;
		a[yindex++] = playerSpr->getPositionY();
		if (a[yindex - 2] > a[yindex - 1])//떨어질때 인식
		{
			down = true;
			auto px = playerSpr->getPositionX();
			auto py = playerSpr->getPositionY();

			pjRect = Rect(px, py, 420, 10);

			//ground3에 올라가기
			if (pjRect.intersectsRect(ground3box) || pjRect.intersectsRect(ground2box) || pjRect.intersectsRect(groundnext1box) || pjRect.intersectsRect(groundnext2box)) {
				notfirst = true;
				JumpEnd();
			}

		}
		else {
			down = false;
			up = true;
		}
	}
	else {
		up = false;
		down = false;
	}
	//캐릭터가 1층이 아닌 곳에서 점프를 시도할 때
	/*	if (jumpYN&&(pdropRect.intersectsRect(ground3jumpbox) || pdropRect.intersectsRect(ground2jumpbox) || pdropRect.intersectsRect(groundnext1jumpbox) || pdropRect.intersectsRect(groundnext2jumpbox)))
	jumpcu = true;
	else
	jumpcu = false;
	*/
	//부유하고 있는 땅에서 벗어났는지 벗어나지 않았는지 확인
	if (pgRect.intersectsRect(ground3box) || pgRect.intersectsRect(ground2box) || pgRect.intersectsRect(groundnext1box) || pgRect.intersectsRect(groundnext2box)) {
		notfloor = false;

	}
	else
		notfloor = true;



}
/*플레이어 함수*/
//캐릭터 공격 끝
void DtopLayer::AttackEnd(Ref* sender)
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
	//uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Uk.png"));

}

//캐릭터 공격 끝난 후 액션
void DtopLayer::AttackEndAction() {

	attYN = false;
	isLeftPressed = false;
	isRightPressed = false;
	playerSpr->stopAllActions();
	playerStandAction();


}
//스킬 끝
void DtopLayer::skillEnd() {

	if (!jumpYN) {
		attYN = false;
		skillYN = false;
		playerStandAction();
	}
}

//캐릭터 점프 끝
void DtopLayer::JumpEnd()
{
	isUpPressed = false;
	isAttack = 0;

	jumpYN = false;
	attYN = false;
	skillYN = false;
	yindex = 1;

	//uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Uk.png"));

	if (!isLeftPressed && !isRightPressed)
		playerStandAction();
	else
		playerRunAction();


}
void DtopLayer::DropEnd()
{
	isUpPressed = false;
	isAttack = 0;
	jumpYN = false;
	down = false;
	yindex = 1;
	if(!isLeftPressed && !isRightPressed)
		playerStandAction();

//	uk->setTexture(Director::getInstance()->getTextureCache()->addImage("Uk.png"));



}



//플레이어 공격 몬스터 충돌
void DtopLayer::PattackMcrush(Ref* sender) {
	std::string dt_uname3 = dataSingleton::getInstance()->user;
	//몬스터 충돌 박스
	monsternum = 0;
	auto mx1 = sprM1->getPositionX();
	auto maRect1 = Rect(mx1, 240, 91, 217);
	auto mx2 = sprM2->getPositionX();
	auto maRect2 = Rect(mx2, 240, 91, 217);
	auto mx3 = sprM3->getPositionX();
	auto maRect3 = Rect(mx3, 240, 91, 217);
	auto mx4 = sprM4->getPositionX();
	auto maRect4 = Rect(mx4, 240, 91, 217);
	auto mx5 = sprM5->getPositionX();
	auto maRect5 = Rect(mx5, 240, 91, 217);
	Rect paRect;

	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();
	if (!playerSpr->isFlippedX())
		paRect = Rect(px, py, 300, 200);
	else
		paRect = Rect(px - 200, py, 300, 200);

	auto atk = pD->jjgetInt("atk", dt_uname3);
	auto atkst = pD->jjgetInt("atkst", dt_uname3);
	PAtt = (rand() % (atkst + 1)) + atk;//atk+공격력 증가스텟을 넣는 것으로 생각한다.//atk=100,atkst=10 100~130

										//데미지 계산
	if (PAtt > MDef) {
		int cri = pD->jjgetInt("cri", dt_uname3);//10
		int cridam = pD->jjgetInt("cridam", dt_uname3);//150
		int num = (rand() % 100) + 1;//1~100

		if (num <= cri) {
			mdamage = (PAtt*cridam) / 100 - MDef;//100*150/100-50 = 100


		}
		else
			mdamage = PAtt - MDef;//100-50 = 50;
	}
	else
		mdamage = 0;

	//몬스터1 플레이어 공격 들어감
	if (paRect.intersectsRect(maRect1) && MHP1>0) {
		monsternum = 1;

		auto particle1 = ParticleSystemQuad::create("patteffect.plist");
		particle1->setDuration(0.2);
		particle1->setPosition(Point(mx1, py + 45));

		this->addChild(particle1);
		MHP1 = MHP1 - mdamage;
		mdamageeffect();

		if (sprMa1) {
			//MHPS1->setPercentage(mhppercent1);
			float cu1 = MHPS1->getPercentage();
			cu1 = (MHP1 / 500) * 100;

			MHPS1->setPercentage(cu1);
			String *str = String::createWithFormat("%.0f", MHP1);
			numsTTF1->setString(str->getCString());
		}
		if (MHP1 <= 0) {
			if (sprMa1true) {
				kill++;
				count->setString(std::to_string(kill) + " / 5");
				auto fade = FadeOut::create(2.0);
				auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
				auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
				auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon1, this));
				auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
				auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
				auto s = Sequence::create(fade, sp, NULL);
				sprMa1->runAction(s);
			}
		}


	}
	//몬스터2 플레이어 공격 들어감
	if (paRect.intersectsRect(maRect2) && MHP2>0) {
		monsternum = 2;

		auto particle2 = ParticleSystemQuad::create("patteffect.plist");
		particle2->setDuration(0.2);
		particle2->setPosition(Point(mx2, py + 45));

		this->addChild(particle2);
		MHP2 = MHP2 - mdamage;
		mdamageeffect();

		if (sprMa2) {
			//MHPS2->setPercentage(mhppercent2);
			float cu2 = MHPS2->getPercentage();
			cu2 = (MHP2 / 500) * 100;

			MHPS2->setPercentage(cu2);
			String *str = String::createWithFormat("%.0f", MHP2);
			numsTTF2->setString(str->getCString());
		}
		if (MHP2 <= 0) {
			if (sprMa2true) {
				kill++;
				count->setString(std::to_string(kill) + " / 5");
				auto fade = FadeOut::create(2.0);
				auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
				auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
				auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon2, this));
				auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
				auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
				auto s = Sequence::create(fade, sp, NULL);
				sprMa2->runAction(s);
			}
		}
	}

	//몬스터3 플레이어 공격 들어감
	if (paRect.intersectsRect(maRect3) && MHP3>0) {
		monsternum = 3;


		auto particle3 = ParticleSystemQuad::create("patteffect.plist");
		particle3->setDuration(0.2);
		particle3->setPosition(Point(mx3, py + 45));
		mdamageeffect();


		this->addChild(particle3);
		MHP3 = MHP3 - mdamage;

		if (sprMa3) {
			//MHPS3->setPercentage(mhppercent3);
			float cu3 = MHPS3->getPercentage();
			cu3 = (MHP3 / 500) * 100;

			MHPS3->setPercentage(cu3);
			String *str = String::createWithFormat("%.0f", MHP3);
			numsTTF3->setString(str->getCString());
		}
		if (MHP3 <= 0) {
			if (sprMa3true) {
				kill++;
				count->setString(std::to_string(kill) + " / 5");
				auto fade = FadeOut::create(2.0);
				auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
				auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
				auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon3, this));
				auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
				auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
				auto s = Sequence::create(fade, sp, NULL);
				sprMa3->runAction(s);
			}
		}
	}

	// 몬스터 4
	if (paRect.intersectsRect(maRect4) && MHP4>0) {
		monsternum = 4;

		auto particle4 = ParticleSystemQuad::create("patteffect.plist");
		particle4->setDuration(0.2);
		particle4->setPosition(Point(mx4, py + 45));

		this->addChild(particle4);
		MHP4 = MHP4 - mdamage;
		mdamageeffect();


		//MHPS1->setPercentage(mhppercent1);
		float cu4 = MHPS4->getPercentage();
		cu4 = (MHP4 / 700) * 100;

		MHPS4->setPercentage(cu4);
		String *str = String::createWithFormat("%.0f", MHP4);
		numsTTF4->setString(str->getCString());

		if (MHP4 <= 0) {
			kill++;
			count->setString(std::to_string(kill) + " / 5");
			auto fade = FadeOut::create(2.0);
			auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
			auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
			auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon4, this));
			auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
			auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
			//auto s = Sequence::create(fade, sp, NULL);
			sprM4->runAction(fade);
			sprM4->runAction(sp);

		}


	}

	if (paRect.intersectsRect(maRect5) && MHP5>0) {
		monsternum = 5;

		auto particle5 = ParticleSystemQuad::create("patteffect.plist");
		particle5->setDuration(0.2);
		particle5->setPosition(Point(mx5, py + 45));

		this->addChild(particle5);
		MHP5 = MHP5 - mdamage;
		mdamageeffect();


		//MHPS1->setPercentage(mhppercent1);
		float cu5 = MHPS5->getPercentage();
		cu5 = (MHP5 / 700) * 100;

		MHPS5->setPercentage(cu5);
		String *str = String::createWithFormat("%.0f", MHP5);
		numsTTF5->setString(str->getCString());

		if (MHP5 <= 0) {
			kill++;
			count->setString(std::to_string(kill) + " / 5");
			auto fade = FadeOut::create(2.0);
			auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
			auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
			auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon5, this));
			auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
			auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
			auto s = Sequence::create(fade, sp, NULL);
			sprM5->runAction(s);

		}


	}
}

//플레이어 사라지는 모션
void DtopLayer::playerDis() {

	playerSpr->stopAllActions();
	auto ani = Animation::create();
	ani->setDelayPerUnit(0.2);
	ani->addSpriteFrameWithFile("pd1.png");
	ani->addSpriteFrameWithFile("pd2.png");
	ani->addSpriteFrameWithFile("pd3.png");
	ani->addSpriteFrameWithFile("pd4.png");
	ani->addSpriteFrameWithFile("pd5.png");
	ani->addSpriteFrameWithFile("pd6.png");
	auto animate = Animate::create(ani);
	auto fade = FadeOut::create(2.0);
	//auto over = CallFuncN::create(CC_CALLBACK_0(UserLayer::gameover, this));
	auto dis = CallFuncN::create(CC_CALLBACK_0(DtopLayer::playerDead, this));
	auto action = Sequence::create(animate, fade, dis, NULL);
	playerSpr->runAction(action);
}

//플레이어 여부 판독
void DtopLayer::playerDead() {
	dataSingleton::getInstance()->playerDead = true;
}

//추락판정
void DtopLayer::playerDrop() {
	//추락판정
	if (notfirst)
		if (notfloor && !jumpYN) {
			Vec2 currentPosition = playerSpr->getPosition();
			Vec2 gravityValue = Vec2(0, 13);
			playerSpr->setPosition(currentPosition - gravityValue);
			down = true;
			if (pgRect.intersectsRect(ground1box)) {//추락하다가 바닥을 만나면
				DropEnd();
				notfirst = false;
			}
		}

}



/*몬스터(+플레이어) 함수*/

//몬스터 기본 설정
void DtopLayer::setEnemy()
{


	//몬스터 1
	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.1);
	animation1->addSpriteFrameWithFile("s1.png");
	animation1->addSpriteFrameWithFile("s2.png");
	animation1->addSpriteFrameWithFile("s3.png");
	animation1->addSpriteFrameWithFile("s2.png");
	auto animate1 = Animate::create(animation1);
	auto act1 = RepeatForever::create(animate1);
	act1->setTag(MonsterWalkMotion);
	sprM1->runAction(act1);

	auto moveaction1_1 = MoveBy::create(5, Point(500, 0));
	auto rotateaction1_1 = RotateBy::create(0, Vec3(0, 180, 0));
	auto moveaction2_1 = MoveBy::create(5, Point(-500, 0));
	auto rotateaction2_1 = RotateBy::create(0, Vec3(0, 180, 0));

	auto totalaction1 = Sequence::create(moveaction1_1, rotateaction1_1, moveaction2_1, rotateaction2_1, NULL);
	auto repeatAct1 = RepeatForever::create(totalaction1);
	repeatAct1->setTag(MonsterShiftMotion);
	sprM1->runAction(repeatAct1);

	auto sm1_moveaction1 = MoveBy::create(5, Point(500, 0));
	auto sm1_rotateaction1 = RotateBy::create(0, Vec3(0, 180, 0));
	auto sm1_moveaction2 = MoveBy::create(5, Point(-500, 0));
	auto sm1_rotateaction2 = RotateBy::create(0, Vec3(0, 180, 0));
	auto sm1_totalaction = Sequence::create(sm1_moveaction1, sm1_rotateaction1, sm1_moveaction2, sm1_rotateaction2, NULL);
	auto sm1_repeatAct = RepeatForever::create(sm1_totalaction);
	sm1_repeatAct->setTag(MonsterShiftMotion);
	sm1->runAction(sm1_repeatAct);

	//몬스터 체력 창
	mhps_back1 = Sprite::create("hpbar_back.png");
	mhps_back1->setAnchorPoint(Point(0.5, 0.5));
	mhps_back1->setPosition(Point(960, 1000));
	mhps_back1->setVisible(false);
	this->addChild(mhps_back1);

	auto mhps1 = Sprite::create("hpbar.png");
	MHPS1 = ProgressTimer::create(mhps1);
	MHPS1->setType(ProgressTimer::Type::BAR);
	MHPS1->setAnchorPoint(Point(0.5, 0.5));
	MHPS1->setPosition(Point(960, 1000));
	MHPS1->setVisible(false);
	MHPS1->setMidpoint(Point(0, 0));
	MHPS1->setBarChangeRate(Point(1, 0));
	MHPS1->setPercentage(100);
	this->addChild(MHPS1);

	numsTTF1 = Label::createWithTTF("500", "nanumgo.ttf", 18);
	numsTTF1->setPosition(Point(280, 15));
	MHPS1->addChild(numsTTF1);

	monname1 = Label::createWithTTF("Lv.1 리프람", "nanumgo.ttf", 20);
	monname1->setPosition(Point(280, 50));
	MHPS1->addChild(monname1);


	//몬스터 2
	auto animation2 = Animation::create();
	animation2->setDelayPerUnit(0.1);
	animation2->addSpriteFrameWithFile("s1.png");
	animation2->addSpriteFrameWithFile("s2.png");
	animation2->addSpriteFrameWithFile("s3.png");
	animation2->addSpriteFrameWithFile("s2.png");
	auto animate2 = Animate::create(animation2);
	auto act2 = RepeatForever::create(animate2);
	act2->setTag(MonsterWalkMotion);
	sprM2->runAction(act2);

	auto moveaction1_2 = MoveBy::create(5, Point(500, 0));
	auto rotateaction1_2 = RotateBy::create(0, Vec3(0, 180, 0));
	auto moveaction2_2 = MoveBy::create(5, Point(-500, 0));
	auto rotateaction2_2 = RotateBy::create(0, Vec3(0, 180, 0));

	auto totalaction2 = Sequence::create(moveaction1_2, rotateaction1_2, moveaction2_2, rotateaction2_2, NULL);
	auto repeatAct2 = RepeatForever::create(totalaction2);
	repeatAct2->setTag(MonsterShiftMotion);
	sprM2->runAction(repeatAct2);

	auto sm2_moveaction1 = MoveBy::create(5, Point(500, 0));
	auto sm2_rotateaction1 = RotateBy::create(0, Vec3(0, 180, 0));
	auto sm2_moveaction2 = MoveBy::create(5, Point(-500, 0));
	auto sm2_rotateaction2 = RotateBy::create(0, Vec3(0, 180, 0));
	auto sm2_totalaction = Sequence::create(sm2_moveaction1, sm2_rotateaction1, sm2_moveaction2, sm2_rotateaction2, NULL);
	auto sm2_repeatAct = RepeatForever::create(sm2_totalaction);
	sm2_repeatAct->setTag(MonsterShiftMotion);
	sm2->runAction(sm2_repeatAct);

	//몬스터2
	mhps_back2 = Sprite::create("hpbar_back.png");
	mhps_back2->setAnchorPoint(Point(0.5, 0.5));
	mhps_back2->setPosition(Point(960, 1000));
	mhps_back2->setVisible(false);
	this->addChild(mhps_back2);

	auto mhps2 = Sprite::create("hpbar.png");
	MHPS2 = ProgressTimer::create(mhps2);
	MHPS2->setType(ProgressTimer::Type::BAR);
	MHPS2->setAnchorPoint(Point(0.5, 0.5));
	MHPS2->setPosition(Point(960, 1000));
	MHPS2->setVisible(false);
	MHPS2->setMidpoint(Point(0, 0));
	MHPS2->setBarChangeRate(Point(1, 0));
	MHPS2->setPercentage(100);
	this->addChild(MHPS2);

	numsTTF2 = Label::createWithTTF("500", "nanumgo.ttf", 18);
	numsTTF2->setPosition(Point(280, 15));
	MHPS2->addChild(numsTTF2);

	monname2 = Label::createWithTTF("Lv.1 리프람", "nanumgo.ttf", 20);
	monname2->setPosition(Point(280, 50));
	MHPS2->addChild(monname2);

	//몬스터 3
	auto animation3 = Animation::create();
	animation3->setDelayPerUnit(0.1);
	animation3->addSpriteFrameWithFile("s1.png");
	animation3->addSpriteFrameWithFile("s2.png");
	animation3->addSpriteFrameWithFile("s3.png");
	animation3->addSpriteFrameWithFile("s2.png");
	auto animate3 = Animate::create(animation3);
	auto act3 = RepeatForever::create(animate3);
	act3->setTag(MonsterWalkMotion);
	sprM3->runAction(act3);

	auto moveaction1_3 = MoveBy::create(5, Point(500, 0));
	auto rotateaction1_3 = RotateBy::create(0, Vec3(0, 180, 0));
	auto moveaction2_3 = MoveBy::create(5, Point(-500, 0));
	auto rotateaction2_3 = RotateBy::create(0, Vec3(0, 180, 0));

	auto totalaction3 = Sequence::create(moveaction1_3, rotateaction1_3, moveaction2_3, rotateaction2_3, NULL);
	auto repeatAct3 = RepeatForever::create(totalaction3);
	//	repeatAct3 = setTag(MonsterShiftMotion);
	sprM3->runAction(repeatAct3);

	auto sm3_moveaction1 = MoveBy::create(5, Point(500, 0));
	auto sm3_rotateaction1 = RotateBy::create(0, Vec3(0, 180, 0));
	auto sm3_moveaction2 = MoveBy::create(5, Point(-500, 0));
	auto sm3_rotateaction2 = RotateBy::create(0, Vec3(0, 180, 0));
	auto sm3_totalaction = Sequence::create(sm3_moveaction1, sm3_rotateaction1, sm3_moveaction2, sm3_rotateaction2, NULL);
	auto sm3_repeatAct = RepeatForever::create(sm3_totalaction);
	sm3_repeatAct->setTag(MonsterShiftMotion);
	sm3->runAction(sm3_repeatAct);

	//몬스터3
	mhps_back3 = Sprite::create("hpbar_back.png");
	mhps_back3->setAnchorPoint(Point(0.5, 0.5));
	mhps_back3->setPosition(Point(960, 1000));
	mhps_back3->setVisible(false);
	this->addChild(mhps_back3);

	auto mhps3 = Sprite::create("hpbar.png");
	MHPS3 = ProgressTimer::create(mhps3);
	MHPS3->setType(ProgressTimer::Type::BAR);
	MHPS3->setAnchorPoint(Point(0.5, 0.5));
	MHPS3->setPosition(Point(960, 1000));
	MHPS3->setVisible(false);
	MHPS3->setMidpoint(Point(0, 0));
	MHPS3->setBarChangeRate(Point(1, 0));
	MHPS3->setPercentage(100);
	this->addChild(MHPS3);

	numsTTF3 = Label::createWithTTF("500", "nanumgo.ttf", 18);
	numsTTF3->setPosition(Point(280, 15));
	MHPS3->addChild(numsTTF3);

	monname3 = Label::createWithTTF("Lv.1 리프람", "nanumgo.ttf", 20);
	monname3->setPosition(Point(280, 50));
	MHPS3->addChild(monname3);

	//몬스터 4

	mhps_back4 = Sprite::create("hpbar_back.png");
	mhps_back4->setAnchorPoint(Point(0.5, 0.5));
	mhps_back4->setPosition(Point(960, 1000));
	mhps_back4->setVisible(false);
	this->addChild(mhps_back4);

	auto mhps4 = Sprite::create("hpbar.png");
	MHPS4 = ProgressTimer::create(mhps4);
	MHPS4->setType(ProgressTimer::Type::BAR);
	MHPS4->setAnchorPoint(Point(0.5, 0.5));
	MHPS4->setPosition(Point(960, 1000));
	MHPS4->setVisible(false);
	MHPS4->setMidpoint(Point(0, 0));
	MHPS4->setBarChangeRate(Point(1, 0));
	MHPS4->setPercentage(100);
	this->addChild(MHPS4);

	numsTTF4 = Label::createWithTTF("700", "nanumgo.ttf", 18);
	numsTTF4->setPosition(Point(280, 15));
	MHPS4->addChild(numsTTF4);

	monname4 = Label::createWithTTF("Lv.2 트리몬", "nanumgo.ttf", 20);
	monname4->setPosition(Point(280, 50));
	MHPS4->addChild(monname4);

	//몬스터5
	mhps_back5 = Sprite::create("hpbar_back.png");
	mhps_back5->setAnchorPoint(Point(0.5, 0.5));
	mhps_back5->setPosition(Point(960, 1000));
	mhps_back5->setVisible(false);
	this->addChild(mhps_back5);

	auto mhps5 = Sprite::create("hpbar.png");
	MHPS5 = ProgressTimer::create(mhps5);
	MHPS5->setType(ProgressTimer::Type::BAR);
	MHPS5->setAnchorPoint(Point(0.5, 0.5));
	MHPS5->setPosition(Point(960, 1000));
	MHPS5->setVisible(false);
	MHPS5->setMidpoint(Point(0, 0));
	MHPS5->setBarChangeRate(Point(1, 0));
	MHPS5->setPercentage(100);
	this->addChild(MHPS5);

	numsTTF5 = Label::createWithTTF("700", "nanumgo.ttf", 18);
	numsTTF5->setPosition(Point(280, 15));
	MHPS5->addChild(numsTTF5);

	monname5 = Label::createWithTTF("Lv.2 트리몬", "nanumgo.ttf", 20);
	monname5->setPosition(Point(280, 50));
	MHPS5->addChild(monname5);

}

//몬스터 공격 시작
void DtopLayer::MonAttstart1() {
	setLeaf1();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();
	auto mx1 = sprM1->getPositionX();

	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.1);
	animation1->addSpriteFrameWithFile("ma3.png");
	animation1->addSpriteFrameWithFile("ma4.png");
	animation1->addSpriteFrameWithFile("ma1.png");
	animation1->addSpriteFrameWithFile("ma2.png");
	DelayTime *dt = DelayTime::create(0.2f);
	auto animate1 = Animate::create(animation1);
	auto addanimate1 = Sequence::create(animate1, dt, NULL);
	auto act1 = RepeatForever::create(addanimate1);
	//몬스터 동작구현
	sprM1->setVisible(false);
	Matt1 = true;
	sprMa1 = Sprite::create("ma1.png");
	auto mPos1 = Point(sprM1->getPosition().x, sprM1->getPosition().y);
	sprMa1->setAnchorPoint(Point(0.5, 0.5));
	sprMa1->setPosition(mPos1);
	this->addChild(sprMa1);
	sprMa1->runAction(act1);

	if (px - mx1<0)
		sprMa1->setFlippedX(true);


}
void DtopLayer::MonAttstart2() {
	setLeaf2();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();

	auto mx2 = sprM2->getPositionX();


	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.1);
	animation1->addSpriteFrameWithFile("ma3.png");
	animation1->addSpriteFrameWithFile("ma4.png");
	animation1->addSpriteFrameWithFile("ma1.png");
	animation1->addSpriteFrameWithFile("ma2.png");
	DelayTime *dt = DelayTime::create(0.2f);
	auto animate1 = Animate::create(animation1);
	auto addanimate1 = Sequence::create(animate1, dt, NULL);
	auto act1 = RepeatForever::create(addanimate1);
	//몬스터 동작구현


	sprM2->setVisible(false);
	Matt2 = true;
	sprMa2 = Sprite::create("ma1.png");
	auto mPos2 = Point(sprM2->getPosition().x, sprM2->getPosition().y);
	sprMa2->setAnchorPoint(Point(0.5, 0.5));
	sprMa2->setPosition(mPos2);
	this->addChild(sprMa2);
	sprMa2->runAction(act1);
	if (px - mx2<0)
		sprMa2->setFlippedX(true);


}



void DtopLayer::MonAttstart3() {
	setLeaf3();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();

	auto mx3 = sprM3->getPositionX();

	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.1);
	animation1->addSpriteFrameWithFile("ma3.png");
	animation1->addSpriteFrameWithFile("ma4.png");
	animation1->addSpriteFrameWithFile("ma1.png");
	animation1->addSpriteFrameWithFile("ma2.png");
	DelayTime *dt = DelayTime::create(0.2f);
	auto animate1 = Animate::create(animation1);
	auto addanimate1 = Sequence::create(animate1, dt, NULL);
	auto act1 = RepeatForever::create(addanimate1);
	//몬스터 동작구현

	//몬스터3 동작구현
	sprM3->setVisible(false);
	Matt3 = true;
	sprMa3 = Sprite::create("ma1.png");
	auto mPos3 = Point(sprM3->getPosition().x, sprM3->getPosition().y);
	sprMa3->setAnchorPoint(Point(0.5, 0.5));
	sprMa3->setPosition(mPos3);
	this->addChild(sprMa3);
	sprMa3->runAction(act1);
	if (px - mx3 < 0)
		sprMa3->setFlippedX(true);



}


//몬스터 공격 끝
void DtopLayer::MonAttend1() {
	//몬스터 공격 멈추는데 문제가 있음
	leafatk1->stopActionByTag(LEAFATK1);
	if (MHP1 > 0)
		sprM1->setVisible(true);
	sprMa1->setVisible(false);
	leafatk1->setVisible(false);
	Matt1 = false;


}
void DtopLayer::MonAttend2() {
	//몬스터 공격 멈추는데 문제가 있음
	leafatk2->stopActionByTag(LEAFATK2);
	if (MHP2 > 0)
		sprM2->setVisible(true);
	sprMa2->setVisible(false);
	leafatk2->setVisible(false);
	Matt2 = false;
}
void DtopLayer::MonAttend3() {
	//몬스터 공격 멈추는데 문제가 있음
	leafatk3->stopActionByTag(LEAFATK3);
	if (MHP3 > 0)
		sprM3->setVisible(true);
	sprMa3->setVisible(false);
	leafatk3->setVisible(false);
	Matt3 = false;
}

//몬스터 공격 설정
void DtopLayer::setLeaf1() {

	auto mx1 = sprM1->getPositionX();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();


	leafatk1 = Sprite::create("leafatk.png");
	this->addChild(leafatk1);
	if (px < mx1) {

		leafatk1->setPosition(Point(mx1 - 20, 200));
		DelayTime *mdt = DelayTime::create(3.0f);
		auto leafmove = MoveBy::create(0.6, Point(-400, 0));
		auto totalaction1 = Sequence::create(leafmove, CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteLeaf1, this)), CallFuncN::create(CC_CALLBACK_0(DtopLayer::setLeaf1, this)), NULL);
		auto repeatAct1 = RepeatForever::create(totalaction1);
		repeatAct1->setTag(LEAFATK1);
		leafatk1->runAction(repeatAct1);
	}
	else {
		leafatk1->setPosition(Point(mx1 + 20, 200));
		auto leafmove = MoveBy::create(0.6, Point(400, 0));

		auto totalaction1 = Sequence::create(leafmove, CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteLeaf1, this)), CallFuncN::create(CC_CALLBACK_0(DtopLayer::setLeaf1, this)), NULL);
		auto repeatAct1 = RepeatForever::create(totalaction1);
		repeatAct1->setTag(LEAFATK1);
		leafatk1->runAction(repeatAct1);
	}




}
void DtopLayer::setLeaf2() {

	auto mx2 = sprM2->getPositionX();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();


	leafatk2 = Sprite::create("leafatk.png");
	this->addChild(leafatk2);
	if (px < mx2) {

		leafatk2->setPosition(Point(mx2 - 20, 200));
		DelayTime *mdt = DelayTime::create(3.0f);
		auto leafmove = MoveBy::create(0.6, Point(-400, 0));
		auto totalaction2 = Sequence::create(leafmove, CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteLeaf2, this)), CallFuncN::create(CC_CALLBACK_0(DtopLayer::setLeaf2, this)), NULL);
		auto repeatAct2 = RepeatForever::create(totalaction2);
		repeatAct2->setTag(LEAFATK2);
		leafatk2->runAction(repeatAct2);
	}
	else {
		leafatk2->setPosition(Point(mx2 + 20, 200));
		auto leafmove = MoveBy::create(0.6, Point(400, 0));

		auto totalaction2 = Sequence::create(leafmove, CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteLeaf2, this)), CallFuncN::create(CC_CALLBACK_0(DtopLayer::setLeaf2, this)), NULL);
		auto repeatAct2 = RepeatForever::create(totalaction2);
		repeatAct2->setTag(LEAFATK2);
		leafatk2->runAction(repeatAct2);
	}



}
void DtopLayer::setLeaf3() {

	auto mx3 = sprM3->getPositionX();
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();

	leafatk3 = Sprite::create("leafatk.png");
	this->addChild(leafatk3);
	if (px < mx3) {

		leafatk3->setPosition(Point(mx3 - 20, 200));
		DelayTime *mdt = DelayTime::create(3.0f);
		auto leafmove = MoveBy::create(0.6, Point(-400, 0));
		auto totalaction3 = Sequence::create(leafmove, CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteLeaf3, this)), CallFuncN::create(CC_CALLBACK_0(DtopLayer::setLeaf3, this)), NULL);
		auto repeatAct3 = RepeatForever::create(totalaction3);
		repeatAct3->setTag(LEAFATK3);
		leafatk3->runAction(repeatAct3);
	}
	else {
		leafatk3->setPosition(Point(mx3 + 20, 200));
		auto leafmove = MoveBy::create(0.6, Point(400, 0));

		auto totalaction3 = Sequence::create(leafmove, CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteLeaf3, this)), CallFuncN::create(CC_CALLBACK_0(DtopLayer::setLeaf3, this)), NULL);
		auto repeatAct3 = RepeatForever::create(totalaction3);
		repeatAct3->setTag(LEAFATK3);
		leafatk3->runAction(repeatAct3);
	}

}

//플레이어 이동 몬스터 충돌
void DtopLayer::PlayerMonCruch() {

	auto mx1 = sprM1->getPositionX();
	auto my1 = sprM1->getPositionY();
	mRect1 = Rect(mx1 - 200, my1, 200, 217);//몬스터 충돌 박스
	auto mx2 = sprM2->getPositionX();
	auto my2 = sprM2->getPositionY();
	mRect2 = Rect(mx2 - 200, my2, 200, 217);//몬스터 충돌 박스
	auto mx3 = sprM3->getPositionX();
	auto my3 = sprM3->getPositionY();
	mRect3 = Rect(mx3 - 200, my3, 200, 217);//몬스터 충돌 박스
	auto mx4 = sprM4->getPositionX();
	auto my4 = sprM4->getPositionY();
	mRect4 = Rect(mx4 - 100, my4, 100, 217);//몬스터 충돌 박스
	auto mx5 = sprM5->getPositionX();
	auto my5 = sprM5->getPositionY();
	mRect5 = Rect(mx5 - 100, my5, 100, 217);//몬스터 충돌 박스

	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();

	//몬스터 플레이어 충돌

	if (MHP1 > 0) {
		if (pRect.intersectsRect(mRect1) && PHP>0) {
			MHPS1->setVisible(true);
			mhps_back1->setVisible(true);
			sm1->pause();
			sprM1->pause();
			if (px - mx1 < 0 && sprMa1)
				sprMa1->setFlippedX(true);
			else if (px - mx1 > 0 && sprMa1)
				sprMa1->setFlippedX(false);
			if (!Matt1 && MHP1 > 0)
				MonAttstart1();
		}
		else {

			MHPS1->setVisible(false);
			mhps_back1->setVisible(false);
			sm1->resume();
			sprM1->resume();
			if (Matt1)
				MonAttend1();
		}
	}
	else if (MHP1 <= 0) {
		sprM1->setVisible(false);
		MHPS1->setVisible(false);
		mhps_back1->setVisible(false);
		numsTTF1->setVisible(false);
		leafatk1->setVisible(false);
		//	MHP1 = 1;

	}
	//몬스터2
	if (MHP2 > 0) {
		if (pRect.intersectsRect(mRect2) && PHP>0) {

			MHPS2->setVisible(true);
			mhps_back2->setVisible(true);
			sm2->pause();
			sprM2->pause();
			if (px - mx2 < 0 && sprMa2)
				sprMa2->setFlippedX(true);
			else if (px - mx2 > 0 && sprMa2)
				sprMa2->setFlippedX(false);
			if (!Matt2 && MHP2 > 0)
				MonAttstart2();
		}
		else {

			MHPS2->setVisible(false);
			mhps_back2->setVisible(false);
			sm2->resume();
			sprM2->resume();
			if (Matt2)
				MonAttend2();
		}
	}
	else if (MHP2 <= 0) {

		sprM2->setVisible(false);
		MHPS2->setVisible(false);
		mhps_back2->setVisible(false);
		numsTTF2->setVisible(false);
		leafatk2->setVisible(false);
		//	MHP2 = 2;

	}
	if (MHP3 > 0) {
		if (pRect.intersectsRect(mRect3) && PHP>0) {

			MHPS3->setVisible(true);
			mhps_back3->setVisible(true);
			sm3->pause();
			sprM3->pause();
			if (px - mx3 < 0 && sprMa3)
				sprMa3->setFlippedX(true);
			else if (px - mx3 > 0 && sprMa3)
				sprMa3->setFlippedX(false);
			if (!Matt3 && MHP3 > 0)
				MonAttstart3();

		}
		else {

			MHPS3->setVisible(false);
			mhps_back3->setVisible(false);
			sm3->resume();
			sprM3->resume();
			if (Matt3)
				MonAttend3();
		}
	}
	else if (MHP3 <= 0) {

		sprM3->setVisible(false);
		MHPS3->setVisible(false);
		mhps_back3->setVisible(false);
		numsTTF3->setVisible(false);
		leafatk3->setVisible(false);
		//	MHP3 = 3;

	}

	if (MHP4 > 0) {
		if (pRect.intersectsRect(mRect4) && PHP>0) {
			MHPS4->setVisible(true);
			mhps_back4->setVisible(true);

		}
		else {

			MHPS4->setVisible(false);
			mhps_back4->setVisible(false);
		}
	}
	else if (MHP4 <= 0) {
	
		MHPS4->setVisible(false);
		mhps_back4->setVisible(false);
		numsTTF4->setVisible(false);

	}

	if (MHP5 > 0) {
		if (pRect.intersectsRect(mRect5) && PHP>0) {
			MHPS5->setVisible(true);
			mhps_back5->setVisible(true);

		}
		else {

			MHPS5->setVisible(false);
			mhps_back5->setVisible(false);
		}
	}
	else if (MHP5 <= 0) {
	
		MHPS5->setVisible(false);
		mhps_back5->setVisible(false);
		numsTTF5->setVisible(false);

	}

}

//몬스터 삭제
void DtopLayer::DeleteMon1(Ref* sender)
{
	std::string dt_uname4 = dataSingleton::getInstance()->user;
	if (pD->jjgetArray("read", dt_uname4, 2) && pD->jjgetQint("condition", dt_uname4, 2) != pD->jjgetQint("nowing", dt_uname4, 2)) {
		auto nowing1 = pD->jjgetQint("nowing", dt_uname4, 2) + 1;
		std::string nowingStr1 = std::to_string(nowing1);
		auto condition1 = pD->jjgetQint("condition", dt_uname4, 2);
		std::string conditionStr1 = std::to_string(condition1);
		pD->jjsetQint("nowing", dt_uname4, nowing1, 2);
		char questing1[40];
		WideCharToMultiByte(CP_UTF8, 0, L"몬스터 사냥 ( ", -1, questing1, 1024, NULL, NULL);
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
	sprMa1->setVisible(false);

}
void DtopLayer::DeleteMon2(Ref* sender)
{
	std::string dt_uname5 = dataSingleton::getInstance()->user;
	if (pD->jjgetArray("read", dt_uname5, 2) && pD->jjgetQint("condition", dt_uname5, 2) != pD->jjgetQint("nowing", dt_uname5, 2)) {
		auto nowing2 = pD->jjgetQint("nowing", dt_uname5, 2) + 1;
		std::string nowingStr2 = std::to_string(nowing2);
		auto condition2 = pD->jjgetQint("condition", dt_uname5, 2);
		std::string conditionStr2 = std::to_string(condition2);

		pD->jjsetQint("nowing", dt_uname5, nowing2, 2);
		char questing2[40];
		WideCharToMultiByte(CP_UTF8, 0, L"몬스터 사냥 ( ", -1, questing2, 1024, NULL, NULL);
		auto questlabel2 = Label::createWithTTF(questing2 + nowingStr2 + " / " + conditionStr2 + " )", "nanumgo.ttf", 40);
		questlabel2->setAnchorPoint(Point(0.5, 0.5));
		questlabel2->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, 800));
		this->addChild(questlabel2);

		auto fade2 = FadeOut::create(5.0f);
		auto move2 = MoveBy::create(5, Point(0, 50));
		auto spaw2 = Spawn::create(move2, fade2, NULL);

		questlabel2->runAction(spaw2);

	}
	sprMa2->setVisible(false);
}
void DtopLayer::DeleteMon3(Ref* sender)
{
	std::string dt_uname6 = dataSingleton::getInstance()->user;
	if (pD->jjgetArray("read", dt_uname6, 2) && pD->jjgetQint("condition", dt_uname6, 2) != pD->jjgetQint("nowing", dt_uname6, 2)) {
		auto nowing3 = pD->jjgetQint("nowing", dt_uname6, 2) + 1;
		std::string nowingStr3 = std::to_string(nowing3);
		auto condition3 = pD->jjgetQint("condition", dt_uname6, 2);
		std::string conditionStr3 = std::to_string(condition3);
		pD->jjsetQint("nowing", dt_uname6, nowing3, 2);
		char questing3[40];
		WideCharToMultiByte(CP_UTF8, 0, L"몬스터 사냥 ( ", -1, questing3, 1024, NULL, NULL);
		auto questlabel3 = Label::createWithTTF(questing3 + nowingStr3 + " / " + conditionStr3 + " )", "nanumgo.ttf", 40);
		questlabel3->setAnchorPoint(Point(0.5, 0.5));
		questlabel3->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, 800));
		this->addChild(questlabel3);

		auto fade3 = FadeOut::create(5.0f);
		auto move3 = MoveBy::create(5, Point(0, 50));
		auto spaw3 = Spawn::create(move3, fade3, NULL);

		questlabel3->runAction(spaw3);

	}
	sprMa3->setVisible(false);

}

void DtopLayer::DeleteMon4(Ref* sender)
{

	std::string dt_uname9 = dataSingleton::getInstance()->user;
	if (pD->jjgetArray("read", dt_uname9, 2) && pD->jjgetQint("condition", dt_uname9, 2) != pD->jjgetQint("nowing", dt_uname9, 2)) {
		auto nowing4 = pD->jjgetQint("nowing", dt_uname9, 2) + 1;
		std::string nowingStr4 = std::to_string(nowing4);
		auto condition4 = pD->jjgetQint("condition", dt_uname9, 2);
		std::string conditionStr4 = std::to_string(condition4);
		pD->jjsetQint("nowing", dt_uname9, nowing4, 2);
		char questing4[40];
		WideCharToMultiByte(CP_UTF8, 0, L"몬스터 사냥 ( ", -1, questing4, 1024, NULL, NULL);
		auto questlabel4 = Label::createWithTTF(questing4 + nowingStr4 + " / " + conditionStr4 + " )", "nanumgo.ttf", 40);
		questlabel4->setAnchorPoint(Point(0.5, 0.5));
		questlabel4->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, 800));
		this->addChild(questlabel4);

		auto fade4 = FadeOut::create(5.0f);
		auto move4 = MoveBy::create(5, Point(0, 50));
		auto spaw4 = Spawn::create(move4, fade4, NULL);

		questlabel4->runAction(spaw4);

	}
	sprM4->setVisible(false);

}

void DtopLayer::DeleteMon5(Ref* sender)
{
	std::string dt_uname10 = dataSingleton::getInstance()->user;
	if (pD->jjgetArray("read", dt_uname10, 2) && pD->jjgetQint("condition", dt_uname10, 2) != pD->jjgetQint("nowing", dt_uname10, 2)) {
		auto nowing5 = pD->jjgetQint("nowing", dt_uname10, 2) + 1;
		std::string nowingStr5 = std::to_string(nowing5);
		auto condition5 = pD->jjgetQint("condition", dt_uname10, 2);
		std::string conditionStr5 = std::to_string(condition5);
		pD->jjsetQint("nowing", dt_uname10, nowing5, 2);
		char questing5[50];
		WideCharToMultiByte(CP_UTF8, 0, L"몬스터 사냥 ( ", -1, questing5, 1024, NULL, NULL);
		auto questlabel5 = Label::createWithTTF(questing5 + nowingStr5 + " / " + conditionStr5 + " )", "nanumgo.ttf", 50);
		questlabel5->setAnchorPoint(Point(0.5, 0.5));
		questlabel5->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, 800));
		this->addChild(questlabel5);

		auto fade5 = FadeOut::create(5.0f);
		auto move5 = MoveBy::create(5, Point(0, 50));
		auto spaw5 = Spawn::create(move5, fade5, NULL);

		questlabel5->runAction(spaw5);

	}
	sprM5->setVisible(false);

}

//몬스터 공격 삭제
void DtopLayer::DeleteLeaf1(Ref* sender) {

	this->removeChild(leafatk1);

}
void DtopLayer::DeleteLeaf2(Ref* sender) {

	this->removeChild(leafatk2);

}
void DtopLayer::DeleteLeaf3(Ref* sender) {

	this->removeChild(leafatk3);

}


/*기타함수*/

//zzz플레이어가 놓이 지면 확인
void DtopLayer::floornumCheck() {
	if (pgRect.intersectsRect(ground1box))
		floornum = 1;
	else if (pgRect.intersectsRect(ground2box))
		floornum = 2;
	else if (pgRect.intersectsRect(ground3box))
		floornum = 3;
	else if (pgRect.intersectsRect(groundnext1box))
		floornum = 4;
	else if (pgRect.intersectsRect(groundnext2box))
		floornum = 5;
	log("floornum : %d", floornum);
}

//포션생산
void DtopLayer::pill(Ref* sender, int n)
{
	int rednum = rand() % 10 + 1;//1~10
	int bluenum = rand() % 10 + 1;//1~10

	float pillvx = voidNode->getPositionX();
	float p;
	float q;
	float a;
	float b;

	if (rednum <= 7) {
		if (n == 1) {

			p = sprMa1->getPositionX() - 80;
			q = sprMa1->getPositionY() - 70;
			redx1 = p;
			redgx1 = pillvx;
			red1->setPosition(p, q);
			red1->setVisible(true);

		}
		else if (n == 2) {

			p = sprMa2->getPositionX() - 80;
			q = sprMa2->getPositionY() - 70;
			redx2 = p;
			redgx2 = pillvx;
			red2->setPosition(p, q);
			red2->setVisible(true);
		}
		else if (n == 3) {

			p = sprMa3->getPositionX() - 80;
			q = sprMa3->getPositionY() - 70;
			redx3 = p;
			redgx3 = pillvx;
			red3->setPosition(p, q);
			red3->setVisible(true);
		}

		else if (n == 4) {

			p = sprM4->getPositionX() - 80;
			q = sprM4->getPositionY() - 85;
			redx4 = p;
			redgx4 = pillvx;
			steel1->setPosition(p, q);
			steel1->setVisible(true);
		}
		else if (n == 5) {

			p = sprM5->getPositionX() - 80;
			q = sprM5->getPositionY() - 85;
			redx5 = p;
			redgx5 = pillvx;
			steel2->setPosition(p, q);
			steel2->setVisible(true);
		}
	}


	if (bluenum <= 7) {
		if (n == 1) {
			a = sprMa1->getPositionX() - 120;
			b = sprMa1->getPositionY() - 70;
			bluex1 = a;
			bluegx1 = pillvx;
			blue1->setPosition(a, b);
			blue1->setVisible(true);
		}
		else if (n == 2) {
			a = sprMa2->getPositionX() - 120;
			b = sprMa2->getPositionY() - 70;
			bluex2 = a;
			bluegx2 = pillvx;
			blue2->setPosition(a, b);
			blue2->setVisible(true);
		}
		else if (n == 3) {
			a = sprMa3->getPositionX() - 120;
			b = sprMa3->getPositionY() - 70;
			bluex3 = a;
			bluegx3 = pillvx;
			blue3->setPosition(a, b);
			blue3->setVisible(true);
		}

	}
}
//아이템 생성
void DtopLayer::item(Ref* sender, int n)
{

	float vx = voidNode->getPositionX();
	float x;
	float y;

	if (n == 1) {
		x = sprMa1->getPositionX();
		y = sprMa1->getPositionY() - 70;
		moneygx1 = vx;
		moneyx1 = x;
		money1->setPosition(x, y);
		money1->setVisible(true);
	}
	else if (n == 2) {
		x = sprMa2->getPositionX();
		y = sprMa2->getPositionY() - 70;
		moneygx2 = vx;
		moneyx2 = x;
		money2->setPosition(x, y);
		money2->setVisible(true);
	}
	else if (n == 3) {
		x = sprMa3->getPositionX();
		y = sprMa3->getPositionY() - 70;
		moneygx3 = vx;
		moneyx3 = x;
		money3->setPosition(x, y);
		money3->setVisible(true);
	}
	else if (n == 4) {
		x = sprM4->getPositionX();
		y = sprM4->getPositionY() - 70;
		moneygx4 = vx;
		moneyx4 = x;
		money4->setPosition(x, y);
		money4->setVisible(true);
	}
	else if (n == 5) {
		x = sprM5->getPositionX();
		y = sprM5->getPositionY() - 70;
		moneygx5 = vx;
		moneyx5 = x;
		money5->setPosition(x, y);
		money5->setVisible(true);
	}

}

void DtopLayer::giveexp(Ref* sender) {
	std::string dt_uname7 = dataSingleton::getInstance()->user;
	PEXP = PEXP + 140;
	dataSingleton::getInstance()->pEXP = PEXP;
	pD->jjsetInt(PEXP, "exp", dt_uname7);
}

void DtopLayer::mdamageeffect() {

	float mx, my;
	if (monsternum == 1) {
		mx = sprM1->getPositionX();
		my = sprM1->getPositionY();
	}
	else if (monsternum == 2)
	{
		mx = sprMa2->getPositionX();
		my = sprMa2->getPositionY();
	}
	else if (monsternum == 3)
	{
		mx = sprMa3->getPositionX();
		my = sprMa3->getPositionY();
	}
	else if (monsternum == 4)
	{
		mx = sprM4->getPositionX();
		my = sprM4->getPositionY();
	}
	else if (monsternum == 5)
	{
		mx = sprM5->getPositionX();
		my = sprM5->getPositionY();
	}

	std::string mdamageStr;
	if (mdamage == 0)
		mdamageStr = "MISS";
	else
		mdamageStr = std::to_string(mdamage);

	auto mdamagelabel = Label::createWithTTF(mdamageStr, "drfont.ttf", 50);
	mdamagelabel->setPosition(Point(mx + 20, my + 100));
	mdamagelabel->enableOutline(Color4B::BLACK, 1);

	if (mdamage == PAtt - MDef && mdamage != 0)
		mdamagelabel->setColor(Color3B(255, 255, 255));
	else if (mdamage>PAtt - MDef && MDef< PAtt) {
		mdamagelabel->setColor(Color3B(170, 18, 18));
	}
	else if (mdamage == 0)
		mdamagelabel->setColor(Color3B(255, 187, 0));

	this->addChild(mdamagelabel);

	auto fade = FadeOut::create(2.0f);
	auto move = MoveBy::create(2, Point(0, 150));
	auto spaw = Spawn::create(fade, move, NULL);
	mdamagelabel->runAction(spaw);


}

void DtopLayer::damageeffect() {
	auto px = playerSpr->getPositionX();
	auto py = playerSpr->getPositionY();

	std::string damageStr;
	if (damage == 0)
		damageStr = "MISS";
	else
		damageStr = std::to_string(damage);

	auto damagelabel = Label::createWithTTF(damageStr, "drfont.ttf", 50);
	damagelabel->setPosition(Point(px, py + 100));
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
void DtopLayer::itemposition() {
	float vx = voidNode->getPositionX();
	float vy = voidNode->getPositionY();


	//돈
	if (money1->isVisible()) {
		float moneyy1 = money1->getPositionY();
		money1->setPosition(Point(vx - moneygx1 + moneyx1, vy + moneyy1));
	}
	if (money2->isVisible()) {
		float moneyy2 = money2->getPositionY();
		money2->setPosition(Point(vx - moneygx2 + moneyx2, vy + moneyy2));
	}
	if (money3->isVisible()) {
		float moneyy3 = money3->getPositionY();
		money3->setPosition(Point(vx - moneygx3 + moneyx3, vy + moneyy3));
	}
	if (money4->isVisible()) {
		float moneyy4 = money4->getPositionY();
		money4->setPosition(Point(vx - moneygx4 + moneyx4, vy + moneyy4));
	}
	if (money5->isVisible()) {
		float moneyy5 = money5->getPositionY();
		money5->setPosition(Point(vx - moneygx5 + moneyx5, vy + moneyy5));
	}

	//포션
	if (red1->isVisible()) {

		float redy1 = red1->getPositionY();
		red1->setPosition(Point(vx - redgx1 + redx1, redy1));
	}
	if (red2->isVisible()) {

		float redy2 = red2->getPositionY();
		red2->setPosition(Point(vx - redgx2 + redx2, vy + redy2));
	}
	if (red3->isVisible()) {

		float redy3 = red3->getPositionY();
		red3->setPosition(Point(vx - redgx3 + redx3, vy + redy3));

	}
	if (steel1->isVisible()) {

		float redy4 = steel1->getPositionY();
		steel1->setPosition(Point(vx - redgx4 + redx4, vy + redy4));

	}
	if (steel2->isVisible()) {

		float redy5 = steel2->getPositionY();
		steel2->setPosition(Point(vx - redgx5 + redx5, vy + redy5));

	}

	if (blue1->isVisible()) {

		float bluey1 = blue1->getPositionY();
		blue1->setPosition(Point(vx - bluegx1 + bluex1, bluey1));

	}
	if (blue2->isVisible()) {
		float bluey2 = blue2->getPositionY();
		blue2->setPosition(Point(vx - bluegx2 + bluex2, vy + bluey2));
	}
	if (blue3->isVisible()) {
		float bluey3 = blue3->getPositionY();
		blue3->setPosition(Point(vx - bluegx3 + bluex3, vy + bluey3));
	}


}


void DtopLayer::skillList(Ref* sender, int n) {

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
		//	auto spaweff = Spawn::create(moveaction1_1, CallFuncN::create(CC_CALLBACK_0(DtopLayer::skillCrush, this)), NULL);
		auto seqeff = Sequence::create(moveaction1_1, CallFuncN::create(CC_CALLBACK_0(DtopLayer::skill_effEnd, this)), NULL);
		skill_eff->runAction(seqeff);
		skill1 = Sequence::create(skillanimate1, dt3, CallFuncN::create(CC_CALLBACK_0(DtopLayer::skillEnd, this)), NULL);
		playerSpr->runAction(skill1);


	}
	}
}

void DtopLayer::skillCrush() {
	std::string dt_uname8 = dataSingleton::getInstance()->user;
	if (skill_eff->isVisible()) {
		monsternum = 0;
		auto skillx = skill_eff->getPositionX();
		auto skilly = skill_eff->getPositionY();
		auto mx1 = sprM1->getPositionX();
		auto mx2 = sprM2->getPositionX();
		auto mx3 = sprM3->getPositionX();
		auto mx4 = sprM4->getPositionX();
		auto mx5 = sprM5->getPositionX();
		auto atk = pD->jjgetInt("atk", dt_uname8);
		//스킬이 몬스터에게 들어감
		switch (skillid) {
		case 0: {

			log("skillcrush");
			//	dataSingleton::getInstance()->Mleafx3 = leafx3;

			auto skillRect = Rect(skillx - 300, skilly, 500, 162);
			auto skillmod = skillhit % 5;

			skillhit++;
			auto skillefftrue = skill_eff->isVisible();
			auto maxhit = 6;//json에서 가져와야한다. 지금 보니까 스킬에 관한 함수를 아예 따로 만들어서
							//키아이디로 해당 스킬에 관련된 정보만을 함수에서 가져오는 형태로 연구해야 할듯하다.
			if (MHP1 > 0) {
				if (skillRect.intersectsRect(mRect1) && skillefftrue && skillhit <= maxhit * 5 && skillmod == 0) {
					monsternum = 1;


					auto particle = ParticleSystemQuad::create("skillmonatk.plist");
					particle->setDuration(0.05);
					particle->setPosition(Point(mx1, 200));
					this->addChild(particle);
					auto skilleff = pD->jjgetAry("effect", "skill", "skill", skillid);

					mdamage = (atk*skilleff) / 100 - MDef;
					mdamageeffect();
					MHP1 = MHP1 - mdamage;

					if (sprM1->isVisible() || sprMa1->isVisible()) {
						//MHPS1->setPercentage(mhppercent1);
						float cu1 = MHPS1->getPercentage();
						cu1 = (MHP1 / 500) * 100;

						MHPS1->setPercentage(cu1);
						String *str = String::createWithFormat("%.0f", MHP1);
						numsTTF1->setString(str->getCString());

						if (MHP1 <= 0) {


							auto fade = FadeOut::create(2.0);
							auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
							auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
							auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon1, this));
							auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
							auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
							auto s = Sequence::create(fade, sp, NULL);
							sprMa1->runAction(s);

						}
					}

				}
			}
			if (MHP2 > 0) {
				if (skillRect.intersectsRect(mRect2) && skillefftrue && skillhit <= maxhit * 5 && skillmod == 0) {
					monsternum = 2;


					auto particle2 = ParticleSystemQuad::create("skillmonatk.plist");
					particle2->setDuration(0.05);
					particle2->setPosition(Point(mx2, 200));
					this->addChild(particle2);
					auto skilleff2 = pD->jjgetAry("effect", "skill", "skill", skillid);

					mdamage = (atk*skilleff2) / 100 - MDef;
					mdamageeffect();
					MHP2 = MHP2 - mdamage;

					if (sprM2->isVisible() || sprMa2->isVisible()) {
						//MHPS1->setPercentage(mhppercent1);
						float cu2 = MHPS2->getPercentage();
						cu2 = (MHP2 / 500) * 100;

						MHPS2->setPercentage(cu2);
						String *str = String::createWithFormat("%.0f", MHP2);
						numsTTF2->setString(str->getCString());

						if (MHP2 <= 0) {


							auto fade = FadeOut::create(2.0);
							auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
							auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
							auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon2, this));
							auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
							auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
							auto s = Sequence::create(fade, sp, NULL);
							sprMa1->runAction(s);

						}
					}

				}
			}
			if (MHP3 > 0) {
				if (skillRect.intersectsRect(mRect3) && skillefftrue && skillhit <= maxhit * 5 && skillmod == 0) {
					monsternum = 3;


					auto particle3 = ParticleSystemQuad::create("skillmonatk.plist");
					particle3->setDuration(0.05);
					particle3->setPosition(Point(mx3, 200));
					this->addChild(particle3);
					auto skilleff3 = pD->jjgetAry("effect", "skill", "skill", skillid);

					mdamage = (atk*skilleff3) / 100 - MDef;
					mdamageeffect();
					MHP3 = MHP3 - mdamage;

					if (sprM3->isVisible() || sprMa3->isVisible()) {
						//MHPS1->setPercentage(mhppercent1);
						float cu3 = MHPS3->getPercentage();
						cu3 = (MHP3 / 500) * 100;

						MHPS3->setPercentage(cu3);
						String *str = String::createWithFormat("%.0f", MHP3);
						numsTTF3->setString(str->getCString());

						if (MHP3 <= 0) {


							auto fade = FadeOut::create(2.0);
							auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
							auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
							auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon3, this));
							auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
							auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
							auto s = Sequence::create(fade, sp, NULL);
							sprMa3->runAction(s);

						}
					}

				}
			}
			if (MHP4 > 0) {
				if (skillRect.intersectsRect(mRect4) && skillefftrue && skillhit <= maxhit * 5 && skillmod == 0) {
					monsternum = 4;


					auto particle4 = ParticleSystemQuad::create("skillmonatk.plist");
					particle4->setDuration(0.05);
					particle4->setPosition(Point(mx4, 200));
					this->addChild(particle4);
					auto skilleff4 = pD->jjgetAry("effect", "skill", "skill", skillid);

					mdamage = (atk*skilleff4) / 100 - MDef;
					mdamageeffect();
					MHP4 = MHP4 - mdamage;

					if (sprM4->isVisible()) {
						//MHPS1->setPercentage(mhppercent1);
						float cu4 = MHPS4->getPercentage();
						cu4 = (MHP4 / 500) * 100;

						MHPS4->setPercentage(cu4);
						String *str = String::createWithFormat("%.0f", MHP4);
						numsTTF4->setString(str->getCString());

						if (MHP4 <= 0) {


							auto fade = FadeOut::create(2.0);
							auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
							auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
							auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon4, this));
							auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
							auto sp = Spawn::create(item, pill, giveexp, NULL);
							auto s = Sequence::create(fade, sp, NULL);
							sprM4->runAction(s);

						}
					}

				}
			}
			if (MHP5 > 0) {
				if (skillRect.intersectsRect(mRect5) && skillefftrue && skillhit <= maxhit * 5 && skillmod == 0) {
					monsternum = 5;


					auto particle5 = ParticleSystemQuad::create("skillmonatk.plist");
					particle5->setDuration(0.05);
					particle5->setPosition(Point(mx5, 200));
					this->addChild(particle5);
					auto skilleff5 = pD->jjgetAry("effect", "skill", "skill", skillid);

					mdamage = (atk*skilleff5) / 100 - MDef;
					mdamageeffect();
					MHP5 = MHP5 - mdamage;

					if (sprM5->isVisible()) {
						//MHPS1->setPercentage(mhppercent1);
						float cu5 = MHPS5->getPercentage();
						cu5 = (MHP5 / 500) * 100;

						MHPS5->setPercentage(cu5);
						String *str = String::createWithFormat("%.0f", MHP5);
						numsTTF5->setString(str->getCString());

						if (MHP5 <= 0) {


							auto fade = FadeOut::create(2.0);
							auto item = CallFuncN::create(CC_CALLBACK_1(DtopLayer::item, this, monsternum));
							auto pill = CallFuncN::create(CC_CALLBACK_1(DtopLayer::pill, this, monsternum));
							auto dis = CallFuncN::create(CC_CALLBACK_1(DtopLayer::DeleteMon5, this));
							auto giveexp = CallFuncN::create(CC_CALLBACK_1(DtopLayer::giveexp, this));
							auto sp = Spawn::create(item, pill, dis, giveexp, NULL);
							auto s = Sequence::create(fade, sp, NULL);
							sprM5->runAction(s);

						}
					}

				}

			}
		}

		default: break;
		}

	}
}

void DtopLayer::skill_effEnd() {
	skill_eff->setVisible(false);

}


void DtopLayer::playerStandAction() {
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
void DtopLayer::playerRunAction() {
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

void DtopLayer::changeScene()
{
	Director::getInstance()->replaceScene(ElyonScene::createScene());
}

void DtopLayer::clearLabel() {

	auto clear = Sprite::create("dclear.png");
	clear->setAnchorPoint(Point(0, 0));
	clear->setPosition(Point(0, 0));
	this->addChild(clear);

}
void DtopLayer::clearBack() {
	auto back = Sprite::create("dclearb.png");
	back->setAnchorPoint(Point(0, 0));
	back->setPosition(Point(0, 0));
	this->addChild(back);
}