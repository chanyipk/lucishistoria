#include "GameScene.h"
#include "UserLayer.h"
#include "dataSingleton.h"
#include "ElyonScene.h"
#include "Jdata.h"
#include "itemwinLayer.h"
#include "statuswinLayer.h"
#include "skillwinLayer.h"
#include "questLayer.h"


Jdata* pU;




bool UserLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	std::string user_uname1 = dataSingleton::getInstance()->user;
	dataSingleton::getInstance()->risen = false;
	dataSingleton::getInstance()->open = false;
	for (int i = 0; i < 4; i++) {
		auto pid = pU->jjgetAry("keyid", "userpotion", user_uname1, i);
		if (pid == 0) {
			dataSingleton::getInstance()->redcount = pU->jjgetpArray("holding", user_uname1, i); //json을 통해 값을 가져와야 한다.
			break;
		}
		else if (pid == 999)
			dataSingleton::getInstance()->redcount = 0;
	}
	for (int i = 0; i < 4; i++) {
		auto pid = pU->jjgetAry("keyid", "userpotion", user_uname1, i);
		if (pid == 1) {
			dataSingleton::getInstance()->bluecount = pU->jjgetpArray("holding", user_uname1, i); //json을 통해 값을 가져와야 한다.
			break;
		}
		else if (pid == 999)
			dataSingleton::getInstance()->bluecount = 0;
	}
	
	gameovertrue = false;
	playerDead = false;
	dataSingleton::getInstance()->skillpressedA = false;
	dataSingleton::getInstance()->skillpressedS = false;
	skilltime1 = false;
	skilltime2 = false;

	auto bar = Sprite::create("userbar.png");
	bar->setAnchorPoint(Point(0, 0));
	bar->setPosition(Point(0, 20));
	this->addChild(bar);

	//	std::string Lv = "Lv. " ;
	level = pU->jjgetInt("level", user_uname1);
	std::string levelnums = std::to_string(level);
	levelnumsTTF = Label::createWithTTF("Lv." + levelnums, "nanumgo.ttf",25);
	levelnumsTTF->setPosition(Point(58, 78));
	levelnumsTTF->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(levelnumsTTF);


	auto phps = Sprite::create("hpbar.png");
	PHPbar = ProgressTimer::create(phps);
	PHPbar->setType(ProgressTimer::Type::BAR);
	PHPbar->setAnchorPoint(Point(0, 0));
	PHPbar->setPosition(Point(113, 94));
	PHPbar->setMidpoint(Point(0, 0));
	PHPbar->setBarChangeRate(Point(1, 0));
	PHPbar->setPercentage(100);
	this->addChild(PHPbar);

	std::string hpnums = std::to_string(pU->jjgetInt("hp", user_uname1));
	hpnumsTTF = Label::createWithTTF(hpnums, "nanumgo.ttf", 18);
	hpnumsTTF->setPosition(Point(280, 15));
	PHPbar->addChild(hpnumsTTF);

	PHP = pU->jjgetInt("hp", user_uname1);
	dataSingleton::getInstance()->pHP = PHP;


	auto pmps = Sprite::create("mpbar.png");
	PMPbar = ProgressTimer::create(pmps);
	PMPbar->setType(ProgressTimer::Type::BAR);
	PMPbar->setAnchorPoint(Point(0, 0));
	PMPbar->setPosition(Point(113, 61));
	PMPbar->setMidpoint(Point(0, 0));
	PMPbar->setBarChangeRate(Point(1, 0));
	PMPbar->setPercentage(100);
	this->addChild(PMPbar);

	std::string mpnums = std::to_string(pU->jjgetInt("mp", user_uname1));
	mpnumsTTF = Label::createWithTTF(mpnums, "nanumgo.ttf", 18);
	mpnumsTTF->setPosition(Point(280, 15));
	PMPbar->addChild(mpnumsTTF);

	PMP = pU->jjgetInt("mp", user_uname1);
	dataSingleton::getInstance()->pMP = PMP;

	auto PEXPs = Sprite::create("expbar.png");
	PEXPbar = ProgressTimer::create(PEXPs);
	PEXPbar->setType(ProgressTimer::Type::BAR);
	PEXPbar->setAnchorPoint(Point(0, 0));
	PEXPbar->setPosition(Point(113, 29));
	PEXPbar->setMidpoint(Point(0, 0));
	PEXPbar->setBarChangeRate(Point(1, 0));
	PEXPbar->setPercentage(0);
	this->addChild(PEXPbar);

	std::string expnums = std::to_string(pU->jjgetInt("exp", user_uname1));
	expnumsTTF = Label::createWithTTF(expnums, "nanumgo.ttf", 18);
	expnumsTTF->setPosition(Point(280, 15));
	PEXPbar->addChild(expnumsTTF);

	maxPEXP = pU->jjgetInt("maxexp", user_uname1);
	PEXP = pU->jjgetInt("exp", user_uname1);//json으로 부터 가져와야 할듯
	dataSingleton::getInstance()->pEXP = PEXP;

	skillbox1 = Sprite::create("userbox.png");
	skillbox1->setAnchorPoint(Point(0.5, 0.5));
	skillbox1->setPosition(Point(800, 75));
	this->addChild(skillbox1);

	skillbox2 = Sprite::create("userbox.png");
	skillbox2->setAnchorPoint(Point(0.5, 0.5));
	skillbox2->setPosition(Point(914, 75));
	this->addChild(skillbox2);

	skillbox3 = Sprite::create("userbox.png");
	skillbox3->setAnchorPoint(Point(0.5, 0.5));
	skillbox3->setPosition(Point(1028, 75));
	this->addChild(skillbox3);

	skillbox4 = Sprite::create("userbox.png");
	skillbox4->setAnchorPoint(Point(0.5, 0.5));
	skillbox4->setPosition(Point(1142, 75));
	this->addChild(skillbox4);

	auto itembox1 = Sprite::create("userbox.png");
	itembox1->setAnchorPoint(Point(0.5, 0.5));
	itembox1->setPosition(Point(1397, 75));
	this->addChild(itembox1);

	auto itembox2 = Sprite::create("userbox.png");
	itembox2->setAnchorPoint(Point(0.5, 0.5));
	itembox2->setPosition(Point(1511, 75));
	this->addChild(itembox2);

	auto itembox3 = Sprite::create("userbox.png");
	itembox3->setAnchorPoint(Point(0.5, 0.5));
	itembox3->setPosition(Point(1625, 75));
	this->addChild(itembox3);

	auto itembox4 = Sprite::create("userbox.png");
	itembox4->setAnchorPoint(Point(0.5, 0.5));
	itembox4->setPosition(Point(1739, 75));
	this->addChild(itembox4);

	auto itembox5 = Sprite::create("userbox.png");
	itembox5->setAnchorPoint(Point(0.5, 0.5));
	itembox5->setPosition(Point(1853, 75));
	this->addChild(itembox5);

	
	


	auto stat_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(UserLayer::button, this));
	stat_but->setTag(statb);
	auto stat = Menu::create(stat_but, NULL);
	stat->setAnchorPoint(Point(0.5, 0.5));
	stat->setPosition(Point(1200, 630));
	stat->setScale(0.35);
	this->addChild(stat);

	auto item_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(UserLayer::button, this));
	item_but->setTag(itemb);
	auto item = Menu::create(item_but, NULL);
	item->setAnchorPoint(Point(0.5, 0.5));
	item->setPosition(Point(1200, 510));
	item->setScale(0.35);
	this->addChild(item);

	auto skill_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(UserLayer::button, this));
	skill_but->setTag(skillb);
	auto skill = Menu::create(skill_but, NULL);
	skill->setAnchorPoint(Point(0.5, 0.5));
	skill->setPosition(Point(1200, 390));
	skill->setScale(0.35);
	this->addChild(skill);

	auto quest_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(UserLayer::button, this));
	quest_but->setTag(questb);
	auto quest = Menu::create(quest_but, NULL);
	quest->setAnchorPoint(Point(0.5, 0.5));
	quest->setPosition(Point(1200, 270));
	quest->setScale(0.35);
	this->addChild(quest);


	auto back_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(UserLayer::backClicked, this));
	back_but->setTag(backb);
	auto back = Menu::create(back_but, NULL);
	back->alignItemsVertically();
	back->setAnchorPoint(Point(0.5, 0.5));
	back->setPosition(Point(1200, 150));
	back->setVisible(false);
	back->setScale(0.35);
	this->addChild(back);


	auto exit_but = MenuItemImage::create("cirbut.png", "cirbut_push.png", CC_CALLBACK_1(UserLayer::endClicked, this));
	exit_but->setTag(exitb);
	auto exit = Menu::create(exit_but, NULL);
	exit->alignItemsVertically();
	exit->setAnchorPoint(Point(0.5, 0.5));
	exit->setPosition(Point(1200,150));
	exit->setScale(0.35);
	exit->setVisible(false);
	this->addChild(exit);


	if (dataSingleton::getInstance()->elyonScene) {
		exit->setVisible(true);
		back->setVisible(false);
	}
	else{
		exit->setVisible(false);
		back->setVisible(true);
	}
	
	//HP포션
	/*red = Sprite::create("hppotion.png");
	red->setTag(RED);
	red->setPosition(Point(1300, 80));
	red->setVisible(false);
	this->addChild(red);
	*/
	auto redspr = MenuItemImage::create("hppotion.png", "hppotion.png", CC_CALLBACK_1(UserLayer::onSprTouchBegan, this));
	red = Menu::create(redspr, NULL);
	red->setPosition(Point(50, 50));
	red->setVisible(false);
	itembox1->addChild(red);

	//	std::string red_c = std::to_string(pU->jjgetInt("red_count", user_uname1));
	redNUM = Label::createWithTTF("0", "nanumgo.ttf", 18);
	redNUM->setPosition(Point(80, 15));
	redNUM->setVisible(false);
	itembox1->addChild(redNUM);

	auto bluespr = MenuItemImage::create("mppotion.png", "mppotion.png", CC_CALLBACK_1(UserLayer::onSprTouchBegan2, this));
	blue = Menu::create(bluespr, NULL);
	blue->setPosition(Point(50, 50));
	blue->setVisible(false);
	itembox2->addChild(blue);

	blueNUM = Label::createWithTTF("0", "nanumgo.ttf", 18);
	blueNUM->setPosition(Point(80, 15));
	blueNUM->setVisible(false);
	itembox2->addChild(blueNUM);

	skillplace();

	this->scheduleUpdate();

	



	return true;
}

void UserLayer::update(float delta) {
	std::string user_uname2 = dataSingleton::getInstance()->user;
	if (dataSingleton::getInstance()->skillupdate) {
		dataSingleton::getInstance()->skillupdate = false;
		skillplace();
	}
	redpotion();

	PHP = dataSingleton::getInstance()->pHP;
	if (PHP <= 0)
		PHP = 0;
	auto maxhp = pU->jjgetInt("maxhp", user_uname2);
	auto hpcu = (PHP / maxhp) * 100; //1000부분은 변하지 않는 캐릭터 체력 값 변수를 넣어야 함
	PHPbar->setPercentage(hpcu);
	String *hpstr = String::createWithFormat("%.0f", PHP);
	hpnumsTTF->setString(hpstr->getCString());

	PMP = dataSingleton::getInstance()->pMP;
	auto maxmp = pU->jjgetInt("maxmp", user_uname2);
	auto mpcu = (PMP / maxmp) * 100;
	PMPbar->setPercentage(mpcu);
	String *mpstr = String::createWithFormat("%.0f", PMP);
	mpnumsTTF->setString(mpstr->getCString());

	PEXP = dataSingleton::getInstance()->pEXP;

	//levelup
	if (PEXP >= maxPEXP) {
		PEXP = PEXP - maxPEXP;
		dataSingleton::getInstance()->pEXP = PEXP;

		levelupeffect();
		level = level + 1;
		pU->jjsetInt(level, "level", user_uname2);
		String *levelStr = String::createWithFormat("Lv\.%d", level);
		levelnumsTTF->setString(levelStr->getCString());

		auto maxhp = pU->jjgetInt("maxhp", user_uname2);
		maxhp = maxhp + maxhp*0.15;
		pU->jjsetInt(maxhp, "maxhp", user_uname2);
		pU->jjsetInt(maxhp, "hp", user_uname2);
		PHP = maxhp;
		dataSingleton::getInstance()->pHP = PHP;

		auto maxmp = pU->jjgetInt("maxmp", user_uname2);
		maxmp = maxmp + maxmp*0.15;
		pU->jjsetInt(maxmp, "maxmp", user_uname2);
		pU->jjsetInt(maxmp, "mp", user_uname2);
		PMP = maxmp;
		dataSingleton::getInstance()->pMP = PMP;
		auto maxexp = pU->jjgetInt("maxexp", user_uname2);
		maxexp = maxexp + maxexp*0.3;
		pU->jjsetInt(maxexp, "maxexp", user_uname2);
		maxPEXP = maxexp;

		auto wid = pU->jjgetInt("wweapon", user_uname2);
		auto sid = pU->jjgetInt("wshirts", user_uname2);
		auto pid = pU->jjgetInt("wpants", user_uname2);
		auto atk = pU->jjgetInt("atk", user_uname2);
		
		if (wid == 999)
			atk = atk + atk*0.15;
		else {
			auto watk = pU->jjgetAry("effect", "weapon", "weapon", wid);
			atk = atk + (atk - watk)*0.15;
			atk = atk + watk;
		}
		pU->jjsetInt(atk, "atk", user_uname2);

		auto def = pU->jjgetInt("def", user_uname2);
		if (sid == 999 && pid == 999)
			def = def + def*0.08;
		else if (sid != 999 && pid == 999) {
			auto sdef = pU->jjgetAry("effect", "weapon", "weapon", sid);
			def = def + (def - sdef)*0.08;
			def = def + sdef;
		}
		else if (sid == 999 && pid != 999) {
			auto pdef = pU->jjgetAry("effect", "weapon", "weapon", pid);
			def = def + (def - pdef)*0.05;
			def = def + pdef;
		}
		else {
			auto sdef = pU->jjgetAry("effect", "weapon", "weapon", wid);
			auto pdef = pU->jjgetAry("effect", "weapon", "weapon", pid);
			def = def + (def - sdef - pdef)*0.05;
			def = def + sdef + pdef;
		}
		pU->jjsetInt(def, "def", user_uname2);

		int nowstat = pU->jjgetInt("stat", user_uname2);
		pU->jjsetInt(nowstat + 5, "stat", user_uname2);
		//여기에 레벨업을 해야함
	}

	float expcu = (PEXP / maxPEXP) * 100;
	PEXPbar->setPercentage(expcu);
	String *expstr = String::createWithFormat("%.2f%%", expcu);
	expnumsTTF->setString(expstr->getCString());

	if (dataSingleton::getInstance()->skillpressedA && !skilltime1) {//스킬A에 대한 쿨타임
		skilltime1 = true;

		auto skillid = pU->jjgetInt("skill1", user_uname2);
		auto cooltime = pU->jjgetAry("cooltime", "skill", "skill", skillid);
		ProgressTo *to1 = ProgressTo::create(cooltime, 0);
		ProgressTimer* progress1 = ProgressTimer::create(Sprite::create("skilling.png"));

		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Point(47, 48));

		progress1->setPercentage(100);
		skillbox1->addChild(progress1);
		progress1->runAction(RepeatForever::create(to1));

		addLabelTimer1(skillbox1, cooltime+1, Vec2(48, 48));  // 호출안했을 때만 타이머 부를 수 있음
	}
	if (dataSingleton::getInstance()->skillpressedS && !skilltime2) {//스킬A에 대한 쿨타임
		skilltime2 = true;

		auto skillid = pU->jjgetInt("skill2", user_uname2);
		auto cooltime = pU->jjgetAry("cooltime", "skill", "skill", skillid);
		ProgressTo *to2 = ProgressTo::create(cooltime, 0);
		ProgressTimer* progress2 = ProgressTimer::create(Sprite::create("skilling.png"));

		progress2->setType(kCCProgressTimerTypeRadial);
		progress2->setPosition(Point(47, 48));

		progress2->setPercentage(100);
		skillbox2->addChild(progress2);
		progress2->runAction(RepeatForever::create(to2));

		addLabelTimer2(skillbox2, cooltime + 1, Vec2(48, 48));  // 호출안했을 때만 타이머 부를 수 있음
	}

	playerDead = dataSingleton::getInstance()->playerDead;
	
	if (playerDead && !gameovertrue && !dataSingleton::getInstance()->elyonScene)
		gameover();
}

void UserLayer::redpotion() {
	std::string user_uname3 = dataSingleton::getInstance()->user;
	int redcount;
	for (int i = 0; i < 4; i++) {
		auto pid = pU->jjgetAry("keyid", "userpotion", user_uname3, i);
		if (pid == 0) {
			redcount = pU->jjgetpArray("holding", user_uname3, i); //json을 통해 값을 가져와야 한다.
			break;
		}
		else if (pid == 999)
			redcount = 0;
	}
	dataSingleton::getInstance()->redcount = redcount;

	if (redcount == 0) {

		red->setVisible(false);
		redNUM->setVisible(false);

	}
	else if (redcount > 0) {//json을 통해 가져와야함


		redNUM->setVisible(true);
		String *str = String::createWithFormat("%d", redcount);
		redNUM->setString(str->getCString());


		if (!red->isVisible()) {
			red->setVisible(true);
		}

	}
	int bluecount;
	for (int i = 0; i < 4; i++) {
		auto pid = pU->jjgetAry("keyid", "userpotion", user_uname3, i);
		if (pid == 1) {
			bluecount = pU->jjgetpArray("holding", user_uname3, i); //json을 통해 값을 가져와야 한다.
			break;
		}
		else if (pid == 999)
			bluecount = 0;
	}
	dataSingleton::getInstance()->bluecount = bluecount;

	if (bluecount == 0) {

		blue->setVisible(false);
		blueNUM->setVisible(false);

	}
	else if (bluecount > 0) {//json을 통해 가져와야함


		blueNUM->setVisible(true);
		String *str = String::createWithFormat("%d", bluecount);
		blueNUM->setString(str->getCString());


		if (!blue->isVisible()) {
			blue->setVisible(true);
		}

	}

}
//아이템 사용 함수
void UserLayer::onSprTouchBegan(Ref* sender)
{
	std::string user_uname4 = dataSingleton::getInstance()->user;
	auto maxPHP = pU->jjgetInt("maxhp", user_uname4);
	if (dataSingleton::getInstance()->redcount > 0 && PHP>0 && PHP<maxPHP) {
		dataSingleton::getInstance()->redcount -= 1;
	
		if (PHP + 200>maxPHP)
			dataSingleton::getInstance()->pHP = maxPHP;
		else
			dataSingleton::getInstance()->pHP = dataSingleton::getInstance()->pHP + 200;
		for (int i = 0; i < 4; i++) {
			auto pid = pU->jjgetAry("keyid", "userpotion", user_uname4, i);
			if (pid == 0) {
				pU->jjsetpArray("holding", user_uname4, dataSingleton::getInstance()->redcount, i);
				break;
			}
		}
		
		pU->jjsetInt(dataSingleton::getInstance()->pHP, "hp", user_uname4);
	}
}
void UserLayer::onSprTouchBegan2(Ref* sender)
{
	std::string user_uname5 = dataSingleton::getInstance()->user;
	auto maxPMP = pU->jjgetInt("maxmp", user_uname5);
	if (dataSingleton::getInstance()->bluecount > 0 && PMP>0 && PMP<maxPMP) {
		dataSingleton::getInstance()->bluecount -= 1;
		if (PMP + 200>maxPMP)
			dataSingleton::getInstance()->pMP = maxPMP;
		else
			dataSingleton::getInstance()->pMP = dataSingleton::getInstance()->pMP + 200;
		for (int i = 0; i < 4; i++) {
			auto pid = pU->jjgetAry("keyid", "userpotion", user_uname5, i);
			if (pid == 1) {
				pU->jjsetpArray("holding", user_uname5, dataSingleton::getInstance()->bluecount, i);
				break;
			}
		}
		pU->jjsetInt(dataSingleton::getInstance()->pMP, "mp", user_uname5);
	}
}

void UserLayer::gameover() {

	gameovertrue = true;
	auto background = Sprite::create("gameover_back.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	background->setTag(BACK);
	this->addChild(background);


	auto magic1 = Sprite::create("magicside.png");
	magic1->setAnchorPoint(Point(0.5, 0.5));
	magic1->setPosition(Point(960, 530));
	magic1->setTag(MAGIC1);
	this->addChild(magic1);
	auto rotate1 = RotateBy::create(20.0f, 360.0f);
	auto repeat1 = RepeatForever::create(rotate1);
	magic1->runAction(repeat1);

	auto magic2 = Sprite::create("magiccenter.png");
	magic2->setAnchorPoint(Point(0.5, 0.5));
	magic2->setPosition(Point(960, 530));
	magic2->setTag(MAGIC2);
	this->addChild(magic2);
	auto rotate2 = RotateBy::create(20.0f, -360.0f);
	auto repeat2 = RepeatForever::create(rotate2);
	magic2->runAction(repeat2);

	auto risenwin = Sprite::create("risen.png");
	risenwin->setAnchorPoint(Point(0.5, 0.5));
	risenwin->setPosition(Point(960, 700));
	risenwin->setTag(RISE_WIN);
	this->addChild(risenwin);

	auto risenbut = MenuItemImage::create("risenbut.png", "risenbut_push.png", CC_CALLBACK_1(UserLayer::risenpush, this));
	auto shiftbut = MenuItemImage::create("shiftbut.png", "shiftbut_push.png", CC_CALLBACK_1(UserLayer::shiftpush, this));

	risenbut->setTag(RISEN);
	shiftbut->setTag(SHIFT);
	auto but_1 = Menu::create(risenbut, NULL);
	but_1->alignItemsVertically();
	but_1->setAnchorPoint(Point(0, 0));
	but_1->setPosition(Point(750, 450));
	but_1->setTag(BUT_1);
	this->addChild(but_1);

	auto but_2 = Menu::create(shiftbut, NULL);
	but_2->alignItemsVertically();
	but_2->setAnchorPoint(Point(0, 0));
	but_2->setPosition(Point(1200, 450));
	but_2->setTag(BUT_2);
	this->addChild(but_2);

}
void UserLayer::button(Ref *sender) {
	auto buttag = (MenuItem*)sender;

	if (!dataSingleton::getInstance()->open) {

		if (buttag->getTag() == statb) {
			auto statusLayer = statuswinLayer::create();
			this->addChild(statusLayer);
		}
		else if (buttag->getTag() == itemb) {
			auto itemLayer = itemwinLayer::create();
			this->addChild(itemLayer);
		}
		else if (buttag->getTag() == skillb) {
			auto skillLayer = skillwinLayer::create();
			this->addChild(skillLayer);
		}
		else if (buttag->getTag() == questb) {
			auto questLayer = questLayer::create();
			this->addChild(questLayer);
		}
	}
	
}



void UserLayer::levelupeffect() {
	auto px = dataSingleton::getInstance()->x;
	auto py = dataSingleton::getInstance()->y;
	auto levelupPa = ParticleSystemQuad::create("levelup.plist");
	levelupPa->setDuration(0.5);
	levelupPa->setScale(0.7);
	levelupPa->setPosition(Point(px, py));
	this->addChild(levelupPa);

	auto leveluplabel = Label::createWithTTF("LEVEL UP", "drfont.ttf", 40);
	leveluplabel->setPosition(Point(px, py + 300));
	leveluplabel->enableGlow(Color4B::YELLOW);
	leveluplabel->setColor(Color3B(255, 255, 198));
	this->addChild(leveluplabel);

	auto fade = FadeOut::create(1.0f);
	auto move = MoveBy::create(2, Point(0, 50));
	auto spaw = Spawn::create(fade, move, NULL);
	auto dt = DelayTime::create(1.0);
	auto seq = Sequence::create(dt, spaw, NULL);
	leveluplabel->runAction(seq);

}

void UserLayer::shiftpush(Ref* sender) {

	auto background = (Sprite*)this->getChildByTag(BACK);
	background->setOpacity(50);

	auto magic1 = (Sprite*)this->getChildByTag(MAGIC1);
	magic1->setOpacity(50);

	auto magic2 = (Sprite*)this->getChildByTag(MAGIC2);
	magic2->setOpacity(50);

	auto risenwin = (Sprite*)this->getChildByTag(RISE_WIN);
	risenwin->setOpacity(50);

	auto but_1 = (Menu*)this->getChildByTag(BUT_1);
	but_1->setOpacity(50);

	auto but_2 = (Menu*)this->getChildByTag(BUT_2);
	but_2->setOpacity(50);

	auto msg = Sprite::create("message2.png");
	msg->setScale(0.7);
	msg->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 + 100));
	msg->setTag(MSG);
	this->addChild(msg);

	auto cancel = MenuItemImage::create("cancel.png", "cancel_push.png", CC_CALLBACK_1(UserLayer::shiftokay, this));
	cancel->setTag(CA);
	auto cc = Menu::create(cancel, NULL);
	cc->alignItemsVertically();
	cc->setAnchorPoint(Point(0, 0));
	cc->setTag(CA1);
	cc->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 + 225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(cc);

	auto okay = MenuItemImage::create("check.png", "check_push.png", CC_CALLBACK_1(UserLayer::shiftokay, this));
	okay->setTag(OK);
	auto oa = Menu::create(okay, NULL);
	oa->alignItemsVertically();
	oa->setAnchorPoint(Point(0, 0));
	oa->setTag(OK1);
	oa->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 - 225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(oa);


}
// 스킬 타이머 함수
void UserLayer::addLabelTimer1(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos)
{
	auto pLabelTime = Label::create(StringUtils::toString(nTime), "Arial", 40);
	pLabelTime->setUserData((int*)nTime);
	pParent->addChild(pLabelTime);
	pLabelTime->setPosition(pos);
	
	auto scheduleAction = CallFuncN::create(CC_CALLBACK_0(UserLayer::updateLabel1, this, pLabelTime));
	auto repeatF = RepeatForever::create(Sequence::create(scheduleAction, DelayTime::create(1.0f), nullptr));
	pLabelTime->runAction(repeatF);

}
void UserLayer::addLabelTimer2(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos)
{
	auto pLabelTime = Label::create(StringUtils::toString(nTime), "Arial", 40);
	pLabelTime->setUserData((int*)nTime);
	pParent->addChild(pLabelTime);
	pLabelTime->setPosition(pos);

	auto scheduleAction = CallFuncN::create(CC_CALLBACK_0(UserLayer::updateLabel2, this, pLabelTime));
	auto repeatF = RepeatForever::create(Sequence::create(scheduleAction, DelayTime::create(1.0f), nullptr));
	pLabelTime->runAction(repeatF);

}

void UserLayer::updateLabel1(cocos2d::Label* pLabel)
{
	if (pLabel)
	{
		int userTime = (int)(pLabel->getUserData());
		userTime -= 1;
		pLabel->setString(StringUtils::toString(userTime));


		if (userTime <= 0)
		{
			//이 구간에는, 시간이 0이 되었을때의 동작내용을 구현합니다.

			pLabel->stopAllActions();
			skillbox1->removeChild(pLabel,1);
			skilltime1 = false;
			dataSingleton::getInstance()->skillpressedA = false;

			

			return;
		}


		pLabel->setUserData((int*)userTime);
	}

}
void UserLayer::updateLabel2(cocos2d::Label* pLabel)
{
	if (pLabel)
	{
		int userTime = (int)(pLabel->getUserData());
		userTime -= 1;
		pLabel->setString(StringUtils::toString(userTime));


		if (userTime <= 0)
		{
			//이 구간에는, 시간이 0이 되었을때의 동작내용을 구현합니다.

			pLabel->stopAllActions();
			skillbox2->removeChild(pLabel, 1);
			skilltime2 = false;
			dataSingleton::getInstance()->skillpressedS = false;



			return;
		}


		pLabel->setUserData((int*)userTime);
	}

}
void UserLayer::risenpush(Ref* sender) {

	auto background = (Sprite*)this->getChildByTag(BACK);
	background->setOpacity(50);

	auto magic1 = (Sprite*)this->getChildByTag(MAGIC1);
	magic1->setOpacity(50);

	auto magic2 = (Sprite*)this->getChildByTag(MAGIC2);
	magic2->setOpacity(50);

	auto risenwin = (Sprite*)this->getChildByTag(RISE_WIN);
	risenwin->setOpacity(50);

	auto but_1 = (Menu*)this->getChildByTag(BUT_1);
	but_1->setOpacity(50);

	auto but_2 = (Menu*)this->getChildByTag(BUT_2);
	but_2->setOpacity(50);

	auto msg = Sprite::create("message.png");
	msg->setScale(0.7);
	msg->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 + 100));
	msg->setTag(MSG);
	this->addChild(msg);

	auto cancel = MenuItemImage::create("cancel.png", "cancel_push.png", CC_CALLBACK_1(UserLayer::risenokay, this));
	cancel->setTag(CA);
	auto cc = Menu::create(cancel, NULL);
	cc->alignItemsVertically();
	cc->setAnchorPoint(Point(0, 0));
	cc->setTag(CA1);
	cc->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 +225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(cc);

	auto okay = MenuItemImage::create("check.png", "check_push.png", CC_CALLBACK_1(UserLayer::risenokay, this));
	okay->setTag(OK);
	auto oa = Menu::create(okay, NULL);
	oa->alignItemsVertically();
	oa->setAnchorPoint(Point(0, 0));
	oa->setTag(OK1);
	oa->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 - 225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(oa);


}
void UserLayer::shiftokay(Ref* sender) {
	std::string user_uname6 = dataSingleton::getInstance()->user;
	auto q = (MenuItem*)sender;
	switch (q->getTag()) {

	case OK: {  


			auto background = (Sprite*)this->getChildByTag(BACK);
			this->removeChild(background);

			auto magic1 = (Sprite*)this->getChildByTag(MAGIC1);
			this->removeChild(magic1);

			auto magic2 = (Sprite*)this->getChildByTag(MAGIC2);
			this->removeChild(magic2);

			auto risenwin = (Sprite*)this->getChildByTag(RISE_WIN);
			this->removeChild(risenwin);


			auto but_1 = (Menu*)this->getChildByTag(BUT_1);
			this->removeChild(but_1);

			auto but_2 = (Menu*)this->getChildByTag(BUT_2);
			this->removeChild(but_2);

			auto msg = (Sprite*)this->getChildByTag(MSG);
			this->removeChild(msg);

			auto oa = (Menu*)this->getChildByTag(OK1);
			this->removeChild(oa);

			auto cc = (Menu*)this->getChildByTag(CA1);
			this->removeChild(cc);

			dataSingleton::getInstance()->playerDead = false;
			gameovertrue = false;
			auto maxhp = pU->jjgetInt("maxhp", user_uname6);
			auto maxmp = pU->jjgetInt("maxmp", user_uname6);
			auto penlhp = maxhp*0.1;
			auto penlmp = maxmp*0.1;
			pU->jjsetInt(penlhp, "hp", user_uname6);
			pU->jjsetInt(penlmp, "mp", user_uname6);
			Director::getInstance()->replaceScene(ElyonScene::createScene());

			break;
		}
	case CA: {

		auto background = (Sprite*)this->getChildByTag(BACK);
		background->setOpacity(255);

		auto magic1 = (Sprite*)this->getChildByTag(MAGIC1);
		magic1->setOpacity(255);

		auto magic2 = (Sprite*)this->getChildByTag(MAGIC2);
		magic2->setOpacity(255);

		auto risenwin = (Sprite*)this->getChildByTag(RISE_WIN);
		risenwin->setOpacity(255);

		auto but_1 = (Menu*)this->getChildByTag(BUT_1);
		but_1->setOpacity(255);

		auto but_2 = (Menu*)this->getChildByTag(BUT_2);
		but_2->setOpacity(255);

		auto msg = (Sprite*)this->getChildByTag(MSG);
		this->removeChild(msg);

		auto oa = (Menu*)this->getChildByTag(OK1);
		this->removeChild(oa);

		auto cc = (Menu*)this->getChildByTag(CA1);
		this->removeChild(cc);

		break;
	}
	default: {
		break;
	}
	}


}
void UserLayer::risenokay(Ref* sender) {
	std::string user_uname7 = dataSingleton::getInstance()->user;
	auto q = (MenuItem*)sender;
	switch (q->getTag()) {

	case OK: {  //돈 내고 부활하는 거 수락,   부활하는 마법진그림과 부활하기 마을이동 등 뒤에 이미지들 다 삭제


		int havemoney = pU->jjgetInt("money", user_uname7);
		if (havemoney >= 3000)
		{
			auto background = (Sprite*)this->getChildByTag(BACK);
			this->removeChild(background);

			auto magic1 = (Sprite*)this->getChildByTag(MAGIC1);
			this->removeChild(magic1);

			auto magic2 = (Sprite*)this->getChildByTag(MAGIC2);
			this->removeChild(magic2);

			auto risenwin = (Sprite*)this->getChildByTag(RISE_WIN);
			this->removeChild(risenwin);


			auto but_1 = (Menu*)this->getChildByTag(BUT_1);
			this->removeChild(but_1);

			auto but_2 = (Menu*)this->getChildByTag(BUT_2);
			this->removeChild(but_2);

			auto msg = (Sprite*)this->getChildByTag(MSG);
			this->removeChild(msg);

			auto oa = (Menu*)this->getChildByTag(OK1);
			this->removeChild(oa);

			auto cc = (Menu*)this->getChildByTag(CA1);
			this->removeChild(cc);

			havemoney = havemoney - 3000;
			pU->jjsetInt(havemoney, "money", user_uname7);

			PHP = pU->jjgetInt("maxhp", user_uname7);
			dataSingleton::getInstance()->pHP = PHP;
			pU->jjsetInt(PHP, "hp", user_uname7);

			PMP = pU->jjgetInt("maxmp", user_uname7);
			dataSingleton::getInstance()->pMP = PMP;
			pU->jjsetInt(PMP, "mp", user_uname7);

			dataSingleton::getInstance()->risen = true;
			dataSingleton::getInstance()->playerDead = false;
			gameovertrue = false;
		}
		else if (havemoney < 3000)
		{
			auto lack = Label ::createWithTTF("보유 금액이 부족합니다", "nanumgo.ttf", 30);
			lack->setPosition(Point(1000, 900));
			auto act1 = DelayTime::create(2.0);
			auto act2 = FadeOut::create(1.5);
			auto act3 = Sequence::create(act1, act2, NULL);
			lack->runAction(act3);
			this->addChild(lack);
		}


		break;
	}
	case CA: {

		auto background = (Sprite*)this->getChildByTag(BACK);
		background->setOpacity(255);

		auto magic1 = (Sprite*)this->getChildByTag(MAGIC1);
		magic1->setOpacity(255);

		auto magic2 = (Sprite*)this->getChildByTag(MAGIC2);
		magic2->setOpacity(255);

		auto risenwin = (Sprite*)this->getChildByTag(RISE_WIN);
		risenwin->setOpacity(255);

		auto but_1 = (Menu*)this->getChildByTag(BUT_1);
		but_1->setOpacity(255);

		auto but_2 = (Menu*)this->getChildByTag(BUT_2);
		but_2->setOpacity(255);

		auto msg = (Sprite*)this->getChildByTag(MSG);
		this->removeChild(msg);

		auto oa = (Menu*)this->getChildByTag(OK1);
		this->removeChild(oa);

		auto cc = (Menu*)this->getChildByTag(CA1);
		this->removeChild(cc);

		break;
	}
	default: {
		break;
	}
	}

}

void UserLayer::skillplace() {
	std::string user_uname8 = dataSingleton::getInstance()->user;
	skillbox1->removeAllChildren();
	skillbox2->removeAllChildren();
	skillbox3->removeAllChildren();
	skillbox4->removeAllChildren();
	auto sid1 = pU->jjgetInt("skill1", user_uname8);
	auto sid2 = pU->jjgetInt("skill2", user_uname8);
	auto sid3 = pU->jjgetInt("skill3", user_uname8);
	auto sid4 = pU->jjgetInt("skill4", user_uname8);
	if (sid1 != 999) {
		auto skillfile = pU->jjgetSAry("png", "skill", "skill", sid1);
		auto skill1_img = Sprite::create(skillfile);
		skill1_img->setAnchorPoint(Point(0.5, 0.5));
		skill1_img->setPosition(Point(47, 48));
		skillbox1->addChild(skill1_img);
	}

	else if (sid2 != 999) {
		auto skillfile2 = pU->jjgetSAry("png", "skill", "skill", sid2);
		auto skill2_img = Sprite::create(skillfile2);
		skill2_img->setAnchorPoint(Point(0.5, 0.5));
		skill2_img->setPosition(Point(47, 48));
		skillbox2->addChild(skill2_img);
	}
	else if (sid3 != 999) {
		auto skillfile3 = pU->jjgetSAry("png", "skill", "skill", sid3);
		auto skill3_img = Sprite::create(skillfile3);
		skill3_img->setAnchorPoint(Point(0.5, 0.5));
		skill3_img->setPosition(Point(47, 48));
		skillbox3->addChild(skill3_img);
	}
	else if (sid4 != 999) {
		auto skillfile4 = pU->jjgetSAry("png", "skill", "skill", sid4);
		auto skill4_img = Sprite::create(skillfile4);
		skill4_img->setAnchorPoint(Point(0.5, 0.5));
		skill4_img->setPosition(Point(47, 48));
		skillbox4->addChild(skill4_img);
	}

	auto skillLabel1 = Label::createWithTTF("A", "nanumgo.ttf", 18);
	skillLabel1->setPosition(Point(80, 15));
	skillbox1->addChild(skillLabel1);


	auto skillLabel2 = Label::createWithTTF("S", "nanumgo.ttf", 18);
	skillLabel2->setPosition(Point(80, 15));
	skillbox2->addChild(skillLabel2);

	auto skillLabel3 = Label::createWithTTF("D", "nanumgo.ttf", 18);
	skillLabel3->setPosition(Point(80, 15));
	skillbox3->addChild(skillLabel3);

	auto skillLabel4 = Label::createWithTTF("F", "nanumgo.ttf", 18);
	skillLabel4->setPosition(Point(80, 15));
	skillbox4->addChild(skillLabel4);
}


void UserLayer::backClicked(Ref* sender) {

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	background->setTag(BACK);
	this->addChild(background);


	auto msg = Sprite::create("message2.png");
	msg->setScale(0.7);
	msg->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 + 100));
	msg->setTag(MSG);
	this->addChild(msg);

	auto cancel = MenuItemImage::create("cancel.png", "cancel_push.png", CC_CALLBACK_1(UserLayer::backokayclicked, this));
	cancel->setTag(CA);
	auto cc = Menu::create(cancel, NULL);
	cc->alignItemsVertically();
	cc->setAnchorPoint(Point(0, 0));
	cc->setTag(CA1);
	cc->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 + 225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(cc);

	auto okay = MenuItemImage::create("check.png", "check_push.png", CC_CALLBACK_1(UserLayer::backokayclicked, this));
	okay->setTag(OK);
	auto oa = Menu::create(okay, NULL);
	oa->alignItemsVertically();
	oa->setAnchorPoint(Point(0, 0));
	oa->setTag(OK1);
	oa->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 - 225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(oa);


}

void UserLayer::backokayclicked(Ref* sender) {
	std::string user_uname9 = dataSingleton::getInstance()->user;
	auto q = (MenuItem*)sender;
	switch (q->getTag()) {

	case OK: {


		auto background = (Sprite*)this->getChildByTag(BACK);
		this->removeChild(background);


		auto msg = (Sprite*)this->getChildByTag(MSG);
		this->removeChild(msg);

		auto oa = (Menu*)this->getChildByTag(OK1);
		this->removeChild(oa);

		auto cc = (Menu*)this->getChildByTag(CA1);
		this->removeChild(cc);


		auto maxhp = pU->jjgetInt("maxhp", user_uname9);
		auto maxmp = pU->jjgetInt("maxmp", user_uname9);
		auto penlhp = maxhp*0.1;
		auto penlmp = maxmp*0.1;
		pU->jjsetInt(penlhp, "hp", user_uname9);
		pU->jjsetInt(penlmp, "mp", user_uname9);
		Director::getInstance()->replaceScene(ElyonScene::createScene());

		break;
	}
	case CA: {

		auto background = (Sprite*)this->getChildByTag(BACK);
		this->removeChild(background);



		auto msg = (Sprite*)this->getChildByTag(MSG);
		this->removeChild(msg);

		auto oa = (Menu*)this->getChildByTag(OK1);
		this->removeChild(oa);

		auto cc = (Menu*)this->getChildByTag(CA1);
		this->removeChild(cc);

		break;
	}
	default: {
		break;
	}
	}

}


void UserLayer::endClicked(Ref* sender) {

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	background->setTag(BACK);
	this->addChild(background);


	auto msg = Sprite::create("gameend.png");
	msg->setScale(0.7);
	msg->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2 + 100));
	msg->setTag(MSG);
	this->addChild(msg);

	auto cancel = MenuItemImage::create("cancel.png", "cancel_push.png", CC_CALLBACK_1(UserLayer::endokayclicked, this));
	cancel->setTag(CA);
	auto cc = Menu::create(cancel, NULL);
	cc->alignItemsVertically();
	cc->setAnchorPoint(Point(0, 0));
	cc->setTag(CA1);
	cc->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 + 225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(cc);

	auto okay = MenuItemImage::create("check.png", "check_push.png", CC_CALLBACK_1(UserLayer::endokayclicked, this));
	okay->setTag(OK);
	auto oa = Menu::create(okay, NULL);
	oa->alignItemsVertically();
	oa->setAnchorPoint(Point(0, 0));
	oa->setTag(OK1);
	oa->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 - 225, Director::getInstance()->
		getWinSize().height / 2 - 100));
	this->addChild(oa);


}

void UserLayer::endokayclicked(Ref* sender) {
	auto q = (MenuItem*)sender;
	switch (q->getTag()) {

	case OK: {


		Director::getInstance()->end();




		break;
	}
	case CA: {

		auto background = (Sprite*)this->getChildByTag(BACK);
		this->removeChild(background);



		auto msg = (Sprite*)this->getChildByTag(MSG);
		this->removeChild(msg);

		auto oa = (Menu*)this->getChildByTag(OK1);
		this->removeChild(oa);

		auto cc = (Menu*)this->getChildByTag(CA1);
		this->removeChild(cc);

		break;
	}
	default: {
		break;
	}
	}

}