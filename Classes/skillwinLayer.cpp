#include "skillwinLayer.h"
#include "Jdata.h"
#include "dataSingleton.h"

Jdata* pSk;


Scene* skillwinLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = skillwinLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool skillwinLayer::init() {

	dataSingleton::getInstance()->open = true;

	if (!Layer::init()) {
		return false;
	}
	


	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background);

	skill_win1 = Sprite::create("skillwin1.png");
	skill_win1->setAnchorPoint(Point(1, 0.5));
	skill_win1->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 - 10, Director::getInstance()->
		getWinSize().height / 2));
	skill_win1->setTag(SKILLW1);
	this->addChild(skill_win1);

	skill_win2 = Sprite::create("skillwin2.png");
	skill_win2->setAnchorPoint(Point(0, 0.5));
	skill_win2->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 + 10, Director::getInstance()->
		getWinSize().height / 2));
	skill_win2->setTag(SKILLW2);
	this->addChild(skill_win2);

	auto exit = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(skillwinLayer::closebut, this));
	auto exit_b = Menu::create(exit, NULL);
	exit_b->setTag(EXIT);
	exit_b->setPosition(Point(1665, 1002));
	this->addChild(exit_b);


	//itemwin2에 대한 요소

	//auto sbox1 = MenuItemImage::create("box.png", "box.png");
	//skillbox1 = Menu::create(sbox1, NULL);
	//sbox1->setTag(SBOX1);
	skillbox1=Sprite::create("box.png");
//	skillbox1->setTag(SBOX1);
	skillbox1->setAnchorPoint(Point(0.5, 0.5));
	skillbox1->setPosition(Point(120, 150));
	skill_win2->addChild(skillbox1);

	//auto sbox2 = MenuItemImage::create("box.png", "box.png");
	//skillbox2 = Menu::create(sbox2, NULL);
	//sbox2->setTag(SBOX2);
	skillbox2 = Sprite::create("box.png");
//	skillbox2->setTag(SBOX2);
	skillbox2->setAnchorPoint(Point(0.5, 0.5));
	skillbox2->setPosition(Point(270, 150));
	skill_win2->addChild(skillbox2);

	//auto sbox3 = MenuItemImage::create("box.png", "box.png");
	//skillbox3 = Menu::create(sbox3, NULL);
	//sbox3->setTag(SBOX3);
	skillbox3 = Sprite::create("box.png");
//	skillbox3->setTag(SBOX3);
	skillbox3->setAnchorPoint(Point(0.5, 0.5));
	skillbox3->setPosition(Point(420, 150));
	skill_win2->addChild(skillbox3);

	//auto sbox4 = MenuItemImage::create("box.png", "box.png");
	//skillbox4 = Menu::create(sbox1, NULL);
	//skillbox4->setTag(SBOX4);
	skillbox4 = Sprite::create("box.png");
//	skillbox4->setTag(SBOX4);
	skillbox4->setAnchorPoint(Point(0.5, 0.5));
	skillbox4->setPosition(Point(570, 150));
	skill_win2->addChild(skillbox4);

	
	showW1();//스킬 
	showW2();//스킬 정보 
	
	return true;
}

void skillwinLayer::clickedbox(Ref* sender,int n) {
	std::string sk_uname1 = dataSingleton::getInstance()->user;
	dataSingleton::getInstance()->skillupdate = true;
	if (isupload) {
		if (n == pSk->jjgetInt("skill1", sk_uname1)) {
			pSk->jjsetInt(999, "skill1", sk_uname1);
		}
		else if (n == pSk->jjgetInt("skill2", sk_uname1)) {
			pSk->jjsetInt(999, "skill2", sk_uname1);
		}
		else if (n == pSk->jjgetInt("skill3", sk_uname1)) {
			pSk->jjsetInt(999, "skill3", sk_uname1);
		}
		else if (n == pSk->jjgetInt("skill4", sk_uname1)) {
			pSk->jjsetInt(999, "skill4", sk_uname1);
		}

		auto boxtag = (MenuItem*)sender;
		switch (boxtag->getTag()) {

		case SBOXM1: {
			pSk->jjsetInt(n, "skill1",sk_uname1);
			break;
		}
		case SBOXM2: {
			pSk->jjsetInt(n, "skill2", sk_uname1);
			break;
		}
		case SBOXM3: {
			pSk->jjsetInt(n, "skill3", sk_uname1);
			break;

		}
		case SBOXM4: {
			pSk->jjsetInt(n, "skill4", sk_uname1);
			break;
		}
		default: break;
		}
		cancelupload();
		showW2();
	}
	
}
void skillwinLayer::closebut(Ref *sender) {
	dataSingleton::getInstance()->open = false;
	this->removeAllChildren();
}

void skillwinLayer::infoopen(Ref *sender, int n, int b) {

	auto sknum = n;
	if (!isupload) {
		if (b == 0) {
			auto upload = MenuItemImage::create("upload.png", "upload_push.png", CC_CALLBACK_1(skillwinLayer::uploadskill, this, n));
			auto upload_b = Menu::create(upload, NULL);
			upload_b->setPosition(Point(320, 420));
			upload_b->setScale(0.8);
			skill_win2->addChild(upload_b);
		}
		else if (b == 1) {
			auto solve = MenuItemImage::create("solve.png", "solve_push.png", CC_CALLBACK_1(skillwinLayer::solveskill, this, n));
			auto solve_b = Menu::create(solve, NULL);
			solve_b->setPosition(Point(320, 420));
			solve_b->setScale(0.8);
			skill_win2->addChild(solve_b);
		}

		Sprite* skillinfo;

		switch (n) {


		case 0: {
			skillinfo = Sprite::create("skill1_info.png");
			skillinfo->setPosition(337, 800);
			skill_win2->addChild(skillinfo);


			break;
		}
		default: break;
		}
	}

}

void skillwinLayer::showW1() {
	std::string sk_uname2 = dataSingleton::getInstance()->user;
	MenuItemImage *skill1_img2;
	auto lv = pSk->jjgetInt("level", sk_uname2);
	if(lv < 2)
		skill1_img2 = MenuItemImage::create("skill1_img2_no.png", "skill1_img2_no.png", CC_CALLBACK_1(skillwinLayer::infoopen, this,0,2));
	else
		skill1_img2 = MenuItemImage::create("skill1_img2.png", "skill1_img2.png", CC_CALLBACK_1(skillwinLayer::infoopen, this,0,0));


	auto skill1 = Menu::create(skill1_img2, NULL);
	skill1->setPosition(420, 850);
	skill_win1->addChild(skill1);
}
void skillwinLayer::showW2() {
	std::string sk_uname3 = dataSingleton::getInstance()->user;
	skill_win2->removeChildByTag(SK1);
	skill_win2->removeChildByTag(SK2);
	skill_win2->removeChildByTag(SK3);
	skill_win2->removeChildByTag(SK4);
	
	auto id1 = pSk->jjgetInt("skill1", sk_uname3);//유저의 장비배열에서 가져옴
	if (id1 != 999) {//999는 아이템이 없다는 것

		auto skillfile1 = pSk->jjgetSAry("png", "skill", "skill", id1);
		auto skill1 = MenuItemImage::create(skillfile1, skillfile1, CC_CALLBACK_1(skillwinLayer::infoopen, this,id1,1));
		auto skill1b = Menu::create(skill1, NULL);
		skill1b->setTag(SK1);
		skill1b->setPosition(120,150);
		skill_win2->addChild(skill1b);

		
	}


	auto id2 = pSk->jjgetInt("skill2", sk_uname3);
	if (id2 != 999) {//999는 아이템이 없다는 것

		auto skillfile2 = pSk->jjgetSAry("png", "skill", "skill", id2);
		auto skill2 = MenuItemImage::create(skillfile2, skillfile2, CC_CALLBACK_1(skillwinLayer::infoopen, this,id2,1));
		auto skill2b = Menu::create(skill2, NULL);
		skill2b->setTag(SK2);
		skill2b->setPosition(270, 150);
		skill_win2->addChild(skill2b);

	}

	auto id3 = pSk->jjgetInt("skill3", sk_uname3);//유저의 장비배열에서 가져옴
	if (id3 != 999) {//999는 아이템이 없다는 것

		auto skillfile3 = pSk->jjgetSAry("png", "skill", "skill", id3);
		auto skill3 = MenuItemImage::create(skillfile3, skillfile3, CC_CALLBACK_1(skillwinLayer::infoopen, this,id3,1));
		auto skill3b = Menu::create(skill3, NULL);
		skill3b->setTag(SK3);
		skill3b->setPosition(420, 150);
		skill_win2->addChild(skill3b);

	}
	auto id4 = pSk->jjgetInt("skill4", sk_uname3);//유저의 장비배열에서 가져옴
	if (id4 != 999) {//999는 아이템이 없다는 것

		auto skillfile4 = pSk->jjgetSAry("png", "skill", "skill", id4);
		auto skill4 = MenuItemImage::create(skillfile4, skillfile4, CC_CALLBACK_1(skillwinLayer::infoopen, this,id4,1));
		auto skill4b = Menu::create(skill4, NULL);
		skill4b->setTag(SK4);
		skill4b->setPosition(570, 150);
		skill_win2->addChild(skill4b);

	}
	
}


void skillwinLayer::uploadskill(Ref* sender,int n){
	
	if (!isupload) {
		isupload = true;
		auto cancel = MenuItemImage::create("cancel.png", "cancel_push.png", CC_CALLBACK_0(skillwinLayer::cancelupload, this));
		auto cancel_b = Menu::create(cancel, NULL);
		cancel_b->setTag(CANCEL);
		cancel_b->setPosition(Point(320, 420));
		cancel_b->setScale(0.8);
		skill_win2->addChild(cancel_b);

		setskillbox(n);
		showW2();

		auto arrow1 = Sprite::create("Darrow.png");
		auto arrow2 = Sprite::create("Darrow.png");
		auto arrow3 = Sprite::create("Darrow.png");
		auto arrow4 = Sprite::create("Darrow.png");

		arrow1->setPosition(120, 250);
		arrow2->setPosition(270, 250);
		arrow3->setPosition(420, 250);
		arrow4->setPosition(570, 250);
		/*
		arrow1->setPosition(57, 200);
		arrow2->setPosition(57, 200);
		arrow3->setPosition(57, 200);
		arrow4->setPosition(57, 200);
		*/
		arrow1->setTag(DAW);
		arrow2->setTag(DAW);
		arrow3->setTag(DAW);
		arrow4->setTag(DAW);


		auto downmov1 = MoveBy::create(1.0, Point(0, -30));
		auto upmov1 = MoveBy::create(0, Point(0, 30));
		auto seqmov1 = Sequence::create(downmov1, upmov1, NULL);
		auto repdownmov1 = RepeatForever::create(seqmov1);
		arrow1->runAction(repdownmov1);
		auto downmov2 = MoveBy::create(1.0, Point(0, -30));
		auto upmov2 = MoveBy::create(0, Point(0, 30));
		auto seqmov2 = Sequence::create(downmov2, upmov2, NULL);
		auto repdownmov2 = RepeatForever::create(seqmov2);
		arrow2->runAction(repdownmov2);
		auto downmov3 = MoveBy::create(1.0, Point(0, -30));
		auto upmov3 = MoveBy::create(0, Point(0, 30));
		auto seqmov3 = Sequence::create(downmov3, upmov3, NULL);
		auto repdownmov3 = RepeatForever::create(seqmov3);
		arrow3->runAction(repdownmov3);
		auto downmov4 = MoveBy::create(1.0, Point(0, -30));
		auto upmov4 = MoveBy::create(0, Point(0, 30));
		auto seqmov4 = Sequence::create(downmov4, upmov4, NULL);
		auto repdownmov4 = RepeatForever::create(seqmov4);
		arrow4->runAction(repdownmov4);

		skillbox1->setVisible(false);
		skillbox2->setVisible(false);
		skillbox3->setVisible(false);
		skillbox4->setVisible(false);

		skill_win2->addChild(arrow1);
		skill_win2->addChild(arrow2);
		skill_win2->addChild(arrow3);
		skill_win2->addChild(arrow4);

		
		
	}

}
void skillwinLayer::solveskill(Ref* sender,int n){
	std::string sk_uname4 = dataSingleton::getInstance()->user;
	dataSingleton::getInstance()->skillupdate = true;
	auto skill1 = pSk->jjgetInt("skill1", sk_uname4);
	auto skill2 = pSk->jjgetInt("skill2", sk_uname4);
	auto skill3 = pSk->jjgetInt("skill3", sk_uname4);
	auto skill4 = pSk->jjgetInt("skill4", sk_uname4);
	if(skill1 == n){
		pSk->jjsetInt(999, "skill1", sk_uname4);
	}
	else if(skill2 == n){
		pSk->jjsetInt(999, "skill2", sk_uname4);
	}
	else if(skill3 == n){
		pSk->jjsetInt(999, "skill3", sk_uname4);
	}
	else if(skill4 == n){
		pSk->jjsetInt(999, "skill4", sk_uname4);
	}

	showW2(); //스킬창 갱신

}

void skillwinLayer::cancelupload() {
	skillbox1->setVisible(true);
	skillbox2->setVisible(true);
	skillbox3->setVisible(true);
	skillbox4->setVisible(true);

	skill_win2->removeChildByTag(DAW);
	skill_win2->removeChildByTag(DAW);
	skill_win2->removeChildByTag(DAW);
	skill_win2->removeChildByTag(DAW);
	skill_win2->removeChildByTag(CANCEL);
	skill_win2->removeChildByTag(SBOX1);
	skill_win2->removeChildByTag(SBOX2);
	skill_win2->removeChildByTag(SBOX3);
	skill_win2->removeChildByTag(SBOX4);
	isupload = false;

}

void skillwinLayer::setskillbox(int n) {
	
	auto sbox1 = MenuItemImage::create("box.png", "box.png", CC_CALLBACK_1(skillwinLayer::clickedbox, this,n));
	sbox1->setTag(SBOXM1);
	auto skillb1 = Menu::create(sbox1, NULL);
	skillb1->setTag(SBOX1);
	skillb1->setAnchorPoint(Point(0.5, 0.5));
	skillb1->setPosition(Point(120, 150));
	skill_win2->addChild(skillb1);

	auto sbox2 = MenuItemImage::create("box.png", "box.png", CC_CALLBACK_1(skillwinLayer::clickedbox, this,n));
	sbox2->setTag(SBOXM2);
	auto skillb2 = Menu::create(sbox2, NULL);
	skillb2->setTag(SBOX2);
	skillb2->setAnchorPoint(Point(0.5, 0.5));
	skillb2->setPosition(Point(270, 150));
	skill_win2->addChild(skillb2);

	auto sbox3 = MenuItemImage::create("box.png", "box.png", CC_CALLBACK_1(skillwinLayer::clickedbox, this,n));
	sbox3->setTag(SBOXM3);
	auto skillb3 = Menu::create(sbox3, NULL);
	skillb3->setTag(SBOX3);
	skillb3->setAnchorPoint(Point(0.5, 0.5));
	skillb3->setPosition(Point(420, 150));
	skill_win2->addChild(skillb3);

	auto sbox4 = MenuItemImage::create("box.png", "box.png", CC_CALLBACK_1(skillwinLayer::clickedbox, this,n));
	sbox4->setTag(SBOXM4);
	auto skillb4 = Menu::create(sbox4, NULL);
	skillb4->setTag(SBOX4);
	skillb4->setAnchorPoint(Point(0.5, 0.5));
	skillb4->setPosition(Point(570, 150));
	skill_win2->addChild(skillb4);
	
}


