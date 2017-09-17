#include "itemwinLayer.h"
#include "Jdata.h"
#include "dataSingleton.h"

Jdata* pI;
std::string atkupstr;
std::string defupstr;
std::string criupstr;
std::string cridamupstr;

Scene* itemwinLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = itemwinLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool itemwinLayer::init() {

	dataSingleton::getInstance()->open = true;

	if (!Layer::init()) {
		return false;
	}
	atkupstr = "-";
	defupstr = "-";
	criupstr = "-";
	cridamupstr = "-";


	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background);

	item_win1 = Sprite::create("itemwin1.png");
	item_win1->setAnchorPoint(Point(1, 0.5));
	item_win1->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 - 10, Director::getInstance()->
		getWinSize().height / 2));
	item_win1->setTag(ITEMW1);
	this->addChild(item_win1);

	item_win2 = Sprite::create("itemwin2.png");
	item_win2->setAnchorPoint(Point(0, 0.5));
	item_win2->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 + 10, Director::getInstance()->
		getWinSize().height / 2));
	item_win2->setTag(ITEMW2);
	this->addChild(item_win2);

	auto exit = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(itemwinLayer::closebut, this));
	auto exit_b = Menu::create(exit, NULL);
	exit_b->setTag(EXIT);
	exit_b->setPosition(Point(1665, 1002));
	this->addChild(exit_b);

	auto character = Sprite::create("a1.png");
	character->setPosition(Point(380, 650));
	item_win1->addChild(character);


	wpbox = Sprite::create("wapbox.png");
	wpbox->setPosition(Point(140, 870));
	item_win1->addChild(wpbox);

	shbox = Sprite::create("shbox.png");
	shbox->setPosition(Point(140, 720));
	item_win1->addChild(shbox);

	pabox = Sprite::create("pabox.png");
	pabox->setPosition(Point(140, 570));
	item_win1->addChild(pabox);

	acbox1 = Sprite::create("acbox1.png");
	acbox1->setPosition(Point(630, 870));
	item_win1->addChild(acbox1);


	acbox2 = Sprite::create("acbox2.png");
	acbox2->setPosition(Point(630, 720));
	item_win1->addChild(acbox2);

	//itemwin2에 대한 요소

	auto wear_but = MenuItemImage::create("wearbut.png", "wearbut.png", CC_CALLBACK_1(itemwinLayer::itemmenu, this));
	wear_but->setTag(wearb);
	auto wear = Menu::create(wear_but, NULL);
	//auto wear = Sprite::create("wearbut.png");
	wear->setAnchorPoint(Point(0.5, 0.5));
	wear->setPosition(Point(150, 910));
	item_win2->addChild(wear);

	auto consume_but = MenuItemImage::create("consumbut.png", "consumbut.png", CC_CALLBACK_1(itemwinLayer::itemmenu, this));
	consume_but->setTag(consumeb);
	auto consume = Menu::create(consume_but, NULL);
	//auto consume = Sprite::create("consumbut.png");
	consume->setAnchorPoint(Point(0.5, 0.5));
	consume->setPosition(Point(350, 910));
	item_win2->addChild(consume);

	auto makeitem_but = MenuItemImage::create("makeitembut.png", "makeitembut.png", CC_CALLBACK_1(itemwinLayer::itemmenu, this));
	makeitem_but->setTag(makeitemb);
	auto makeitem = Menu::create(makeitem_but, NULL);
	//auto makeitem = Sprite::create("makeitembut.png");
	makeitem->setAnchorPoint(Point(0.5, 0.5));
	makeitem->setPosition(Point(550, 910));
	item_win2->addChild(makeitem);

	auto questitem_but = MenuItemImage::create("questitembut.png", "questitembut.png", CC_CALLBACK_1(itemwinLayer::itemmenu, this));
	questitem_but->setTag(questitemb);
	auto questitem = Menu::create(questitem_but, NULL);
	//auto questitem = Sprite::create("questitembut.png");
	questitem->setAnchorPoint(Point(0.5, 0.5));
	questitem->setPosition(Point(150, 830));
	item_win2->addChild(questitem);

	itembox1 = Sprite::create("itembox.png");
	itembox1->setPosition(Point(120, 720));
	item_win2->addChild(itembox1);

	itembox2 = Sprite::create("itembox.png");
	itembox2->setPosition(Point(270, 720));
	item_win2->addChild(itembox2);

	itembox3 = Sprite::create("itembox.png");
	itembox3->setPosition(Point(420, 720));
	item_win2->addChild(itembox3);

	itembox4 = Sprite::create("itembox.png");
	itembox4->setPosition(Point(570, 720));
	item_win2->addChild(itembox4);

	showW1();
	showW2();//아이템창을 열었을 때 초기화 화면
	statusupdate();
	return true;
}

void itemwinLayer::itemmenu(Ref* sender) {
	auto buttag = (MenuItem*)sender;

	switch (buttag->getTag()) {
	case wearb: {
		showW2();
		break;
	}
	case consumeb: {
		showW3();
		break;
	}
	case makeitemb: {
		showW4();
		break;
	}
	default: {
		break;
	}

	}
}
void itemwinLayer::closebut(Ref *sender) {
	dataSingleton::getInstance()->open = false;
	this->removeAllChildren();
}

void itemwinLayer::dress(Ref *sender) {
	std::string i_uname1 = dataSingleton::getInstance()->user;
	//해당 박스의 태그값을 가져와 첫번째 박스면 첫번째 배열의 키아이디를 가져와 해당 키아이디를 토대로
	//캐릭터의 공격력을 증가시키는데 키아이디값이 1이면 공격력, 2 3 이면 방어력이 오르도록 한다.
	//holding 값을 감소시키고
	//holding이 0이면 다음 배열의 값들을 앞으로 옮기고 마지막 배열은 999로 초기화 시킨다.

	//추가 구현 이미 아이템이 장착되어있을 때는 아이템이 서로 교차되는 방식 구현
	auto boxnum = (MenuItem*)sender;

	//캐릭터 스탯
	auto atk = pI->jjgetInt("atk", i_uname1);
	auto beforeatk = atk;
	auto def = pI->jjgetInt("def", i_uname1);
	auto beforedef = def;
	pI->jjsetQint("nowing", i_uname1, 1, 1);
	switch (boxnum->getTag()) {

	case BOX1: {


		auto id1 = pI->jjgetAry("keyid", "userweapon", i_uname1, 0);//유저의 장비배열에서 가져옴
		auto wp1file1 = pI->jjgetSAry("pngname", "weapon", "weapon", id1);
		auto plusnum = pI->jjgetAry("effect", "weapon", "weapon", id1);

		if (id1 < 1) {//현재 무기 아이템이 하나이기 때문에 1미만이 무기를 나타냄, 예를 들어 무기의 종류가 10개라면 0~9까지의 키코드가 무기를 의미함
			undressWP();
			atk = pI->jjgetInt("atk", i_uname1);
			pI->jjsetInt(id1, "wweapon", i_uname1);
			atk += plusnum;
			pI->jjsetInt(atk, "atk", i_uname1);


			auto difatk = atk - beforeatk;
			std::string mark;

			if (difatk >= 0)
				mark = "+";
			else if (difatk < 0) {
				difatk = -difatk;
				mark = "-";
			}

			atkupstr = mark + std::to_string(difatk);
		}
		else if (id1<2) {
			undressSH();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id1, "wshirts", i_uname1);
			def += plusnum;
			pI->jjsetInt(def, "def", i_uname1);


			auto difdef = def - beforedef;
			std::string mark;

			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";

			defupstr = mark + std::to_string(difdef);
		}
		else if (id1<3) {
			undressPA();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id1, "wpants", i_uname1);
			atk += plusnum;
			pI->jjsetInt(def, "def", i_uname1);


			auto difdef = def - beforedef;
			std::string mark;


			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";


			defupstr = mark + std::to_string(difdef);
		}
		//아이템창 2에서 아이템 갯수가 0이 되면 삭제되게 하기
		auto holding1 = pI->jjgetAry("holding", "userweapon", i_uname1, 0);
		holding1 = holding1 - 1;
		pI->jjsetAry("holding", "userweapon", i_uname1, holding1, 0);
		/*   String *str = String::createWithFormat("%d", holding1);
		hLabel1->setString(str->getCString());
		*/
		if (holding1 == 0) {
			auto itemimg = (Menu*)this->getChildByTag(BOX1);
			this->removeChild(itemimg);
			int n;
			for (n = 0; n < 3; n++) {//1->0,2->1,3->2,3은 초기화
									 //키아이디 옮김
				auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname1, n + 1);
				if (keyid != 999) {
					pI->jjsetAry("keyid", "userweapon", i_uname1, keyid, n);
					//갯수 옮김
					auto holding = pI->jjgetAry("holding", "userweapon", i_uname1, n + 1);
					pI->jjsetAry("holding", "userweapon", i_uname1, holding, n);

				}
				else break;
			}
			pI->jjsetAry("keyid", "userweapon", i_uname1, 999, n);
			pI->jjsetAry("holding", "userweapon", i_uname1, 0, n);

			;//아이템 메뉴얼을 갱신하기 위해
		}


		break;
	}
	case BOX2: {
		auto id2 = pI->jjgetAry("keyid", "userweapon", i_uname1, 1);//유저의 장비배열에서 가져옴
		auto wp2file2 = pI->jjgetSAry("pngname", "weapon", "weapon", id2);
		auto plusnum = pI->jjgetAry("effect", "weapon", "weapon", id2);

		if (id2<1) {//현재 무기 아이템이 하나이기 때문에 1미만이 무기를 나타냄, 예를 들어 무기의 종류가 10개라면 0~9까지의 키코드가 무기를 의미함
			undressWP();
			atk = pI->jjgetInt("atk", i_uname1);
			pI->jjsetInt(id2, "wweapon", i_uname1);
			atk += plusnum;
			pI->jjsetInt(atk, "atk", i_uname1);


			auto difatk = atk - beforeatk;
			std::string mark;


			if (difatk >= 0)
				mark = "+";
			else if (difatk < 0) {
				difatk = -difatk;
				mark = "-";
			}

			atkupstr = mark + std::to_string(difatk);
		}
		else if (id2<2) {
			undressSH();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id2, "wshirts", i_uname1);
			def += plusnum;
			pI->jjsetInt(def, "def", i_uname1);



			auto difdef = def - beforedef;
			std::string mark;

			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";


			defupstr = mark + std::to_string(difdef);
		}
		else if (id2<3) {
			undressPA();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id2, "wpants", i_uname1);
			def += plusnum;
			pI->jjsetInt(def, "def", i_uname1);


			auto difdef = def - beforedef;
			std::string mark;


			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";


			defupstr = mark + std::to_string(difdef);
		}
		//아이템창 2에서 아이템 갯수가 0이 되면 삭제되게 하기
		auto holding2 = pI->jjgetAry("holding", "userweapon", i_uname1, 1);
		holding2 = holding2 - 1;
		pI->jjsetAry("holding", "userweapon", i_uname1, holding2, 1);
		String *str = String::createWithFormat("%d", holding2);
		hLabel2->setString(str->getCString());

		if (holding2 == 0) {
			auto itemimg = (Menu*)this->getChildByTag(BOX2);
			this->removeChild(itemimg);
			int n;
			for (n = 1; n < 3; n++) {//1->0,2->1,3->2,3은 초기화
									 //키아이디 옮김
				auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname1, n + 1);
				if (keyid != 999) {
					pI->jjsetAry("keyid", "userweapon", i_uname1, keyid, n);
					//갯수 옮김
					auto holding = pI->jjgetAry("holding", "userweapon", i_uname1, n + 1);
					pI->jjsetAry("holding", "userweapon", i_uname1, holding, n);


				}
				else break;
			}
			pI->jjsetAry("keyid", "userweapon", i_uname1, 999, n);
			pI->jjsetAry("holding", "userweapon", i_uname1, 0, n);
			;//아이템 메뉴얼을 갱신하기 위해
		}


		break;

	}
	case BOX3: {
		auto id3 = pI->jjgetAry("keyid", "userweapon", i_uname1, 2);//유저의 장비배열에서 가져옴
		auto wp3file3 = pI->jjgetSAry("pngname", "weapon", "weapon", id3);
		auto plusnum = pI->jjgetAry("effect", "weapon", "weapon", id3);

		if (id3 < 1) {//현재 무기 아이템이 하나이기 때문에 1미만이 무기를 나타냄, 예를 들어 무기의 종류가 10개라면 0~9까지의 키코드가 무기를 의미함
			undressWP();
			atk = pI->jjgetInt("atk", i_uname1);
			pI->jjsetInt(id3, "wweapon", i_uname1);
			atk += plusnum;
			pI->jjsetInt(atk, "atk", i_uname1);


			auto difatk = atk - beforeatk;
			std::string mark;


			if (difatk >= 0)
				mark = "+";
			else if (difatk < 0) {
				difatk = -difatk;
				mark = "-";
			}

			atkupstr = mark + std::to_string(difatk);
		}
		else if (id3 < 2) {
			undressSH();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id3, "wshirts", i_uname1);
			def += plusnum;
			pI->jjsetInt(def, "def", i_uname1);


			auto difdef = def - beforedef;
			std::string mark;


			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";


			defupstr = mark + std::to_string(difdef);
		}
		else if (id3 < 3) {
			undressPA();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id3, "wpants", i_uname1);
			def += plusnum;
			pI->jjsetInt(def, "def", i_uname1);


			auto difdef = def - beforedef;
			std::string mark;


			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";


			defupstr = mark + std::to_string(difdef);
		}
		//아이템창 2에서 아이템 갯수가 0이 되면 삭제되게 하기
		auto holding3 = pI->jjgetAry("holding", "userweapon", i_uname1, 2);
		holding3 = holding3 - 1;
		pI->jjsetAry("holding", "userweapon", i_uname1, holding3, 2);
		String *str = String::createWithFormat("%d", holding3);
		hLabel3->setString(str->getCString());

		if (holding3 == 0) {
			auto itemimg = (Menu*)this->getChildByTag(BOX3);
			this->removeChild(itemimg);
			int n;
			for (n = 2; n < 3; n++) {//1->0,2->1,3->2,3은 초기화
									 //키아이디 옮김
				auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname1, n + 1);
				if (keyid != 999) {
					pI->jjsetAry("keyid", "userweapon", i_uname1, keyid, n);
					//갯수 옮김
					auto holding = pI->jjgetAry("holding", "userweapon", i_uname1, n + 1);
					pI->jjsetAry("holding", "userweapon", i_uname1, holding, n);


				}
				else break;
			}
			pI->jjsetAry("keyid", "userweapon", i_uname1, 999, n);
			pI->jjsetAry("holding", "userweapon", i_uname1, 0, n);

			;//아이템 메뉴얼을 갱신하기 위해
		}
		break;
	}
	case BOX4:
	{

		auto id4 = pI->jjgetAry("keyid", "userweapon", i_uname1, 3);//유저의 장비배열에서 가져옴
		auto wp4file4 = pI->jjgetSAry("pngname", "weapon", "weapon", id4);
		auto plusnum = pI->jjgetAry("effect", "weapon", "weapon", id4);

		if (id4<1) {//현재 무기 아이템이 하나이기 때문에 1미만이 무기를 나타냄, 예를 들어 무기의 종류가 10개라면 0~9까지의 키코드가 무기를 의미함
			undressWP();
			atk = pI->jjgetInt("atk", i_uname1);
			pI->jjsetInt(id4, "wweapon", i_uname1);
			atk += plusnum;
			pI->jjsetInt(atk, "atk", i_uname1);


			auto difatk = atk - beforeatk;
			std::string mark;


			if (difatk >= 0)
				mark = "+";
			else if (difatk < 0) {
				difatk = -difatk;
				mark = "-";
			}

			atkupstr = mark + std::to_string(difatk);
		}
		else if (id4<2) {
			undressSH();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id4, "wshirts", i_uname1);
			def += plusnum;
			pI->jjsetInt(def, "def", i_uname1);


			auto difdef = def - beforedef;
			std::string mark;


			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";


			defupstr = mark + std::to_string(difdef);
		}
		else if (id4<3) {
			undressPA();
			def = pI->jjgetInt("def", i_uname1);
			pI->jjsetInt(id4, "wpants", i_uname1);
			def += plusnum;
			pI->jjsetInt(def, "def", i_uname1);


			auto difdef = def - beforedef;
			std::string mark;


			if (difdef >= 0)
				mark = "+";
			else if (difdef < 0)
				mark = "-";


			defupstr = mark + std::to_string(difdef);
		}
		//아이템창 2에서 아이템 갯수가 0이 되면 삭제되게 하기
		auto holding4 = pI->jjgetAry("holding", "userweapon", i_uname1, 3);
		holding4 = holding4 - 1;
		pI->jjsetAry("holding", "userweapon", i_uname1, holding4, 3);
		String *str = String::createWithFormat("%d", holding4);
		hLabel4->setString(str->getCString());

		if (holding4 == 0) {
			auto itemimg = (Menu*)this->getChildByTag(BOX4);
			this->removeChild(itemimg);
			int n = 3;
			//현재 최대 배열 갯수가 4개이므로 for문을 사용할 수가 없음
			/*   for (n = 3; n < 4; n++) {//1->0,2->1,4->2,4은 초기화
			//키아이디 옮김
			auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname1, n + 1);
			if (keyid != 999) {
			pI->jjsetAry("keyid", "userweapon", i_uname1, keyid, n);
			//갯수 옮김
			auto holding = pI->jjgetAry("holding", "userweapon", i_uname1, n + 1);
			pI->jjsetAry("holding", "userweapon", i_uname1, holding, n);
			//이펙트 옮김
			auto effect = pI->jjgetAry("effect", "userweapon", i_uname1, n + 1);
			pI->jjsetAry("effect", "userweapon", i_uname1, effect, n);

			}
			else break;
			}*/
			pI->jjsetAry("keyid", "userweapon", i_uname1, 999, n);
			pI->jjsetAry("holding", "userweapon", i_uname1, 0, n);

			;//아이템 메뉴얼을 갱신하기 위해
		}

	}
	default: break;
	}
	showW1();
	showW2(); //item2창 갱신
	statusupdate();//스탯정보 갱신

}

void itemwinLayer::undress(Ref *sender) {
	std::string i_uname2 = dataSingleton::getInstance()->user;
	auto boxnum = (MenuItem*)sender;
	auto atk = pI->jjgetInt("atk", i_uname2);
	auto beforeatk = atk;
	auto def = pI->jjgetInt("def", i_uname2);
	auto beforedef = def;

	switch (boxnum->getTag()) {

	case WPBOX: {
		log("undress into wpbox");
		wpbox->removeAllChildren();

		auto wwpid = pI->jjgetInt("wweapon", i_uname2);
		auto wwpeft = pI->jjgetAry("effect", "weapon", "weapon", wwpid);
		atk -= wwpeft;//아이템이 분리되므로 장착했었던 아이템의 효과를 빼준다.
		pI->jjsetInt(atk, "atk", i_uname2);
		pI->jjsetInt(999, "wweapon", i_uname2);

		auto difatk = atk - beforeatk;
		std::string mark;

		if (difatk >= 0)
			mark = "+";
		else if (difatk < 0) {
			difatk = -difatk;
			mark = "-";
		}
		atkupstr = mark + std::to_string(difatk);

		//분리되었으므로 사용자의 보유 정보로 이동해야함
		for (int i = 0; i < 4; ) {
			//비어있는  배열 찾기or 동일한 아이디 찾기
			auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname2, i);
			if (keyid == 999) {
				pI->jjsetAry("keyid", "userweapon", i_uname2, wwpid, i);
				pI->jjsetAry("holding", "userweapon", i_uname2, 1, i);
				break;
			}
			else if (keyid == wwpid) {
				auto holding = pI->jjgetAry("holding", "userweapon", i_uname2, i);
				holding += 1;
				pI->jjsetAry("holding", "userweapon", i_uname2, holding, i);
				break;
			}
			else
				i++;
		}


		break;
	}
	case SHBOX: {
		shbox->removeAllChildren();
		auto wshid = pI->jjgetInt("wshirts", i_uname2);
		auto wsheft = pI->jjgetAry("effect", "weapon", "weapon", wshid);
		def -= wsheft;//아이템이 분리되므로 장착했었던 아이템의 효과를 빼준다.
		pI->jjsetInt(def, "def", i_uname2);
		pI->jjsetInt(999, "wshirts", i_uname2);

		auto difdef = def - beforedef;
		std::string mark;

		if (difdef >= 0)
			mark = "+";
		else if (difdef < 0) {
			difdef = -difdef;
			mark = "-";
		}
		defupstr = mark + std::to_string(difdef);

		//분리되었으므로 사용자의 보유 정보로 이동해야함
		for (int i = 0; i < 4; ) {
			//비어있는  배열 찾기or 동일한 아이디 찾기
			auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname2, i);
			if (keyid == 999) {
				pI->jjsetAry("keyid", "userweapon", i_uname2, wshid, i);
				pI->jjsetAry("holding", "userweapon", i_uname2, 1, i);
				break;
			}
			else if (keyid == wshid) {
				auto holding = pI->jjgetAry("holding", "userweapon", i_uname2, i);
				holding += 1;
				pI->jjsetAry("holding", "userweapon", i_uname2, holding, i);
				break;
			}
			else
				i++;
		}
		break;
	}
	case PABOX: {
		pabox->removeAllChildren();
		auto wpaid = pI->jjgetInt("wpants", i_uname2);
		auto wpaeft = pI->jjgetAry("effect", "weapon", "weapon", wpaid);
		def -= wpaeft;//아이템이 분리되므로 장착했었던 아이템의 효과를 빼준다.
		pI->jjsetInt(def, "def", i_uname2);
		pI->jjsetInt(999, "wpants", i_uname2);

		auto difdef = def - beforedef;
		std::string mark;

		if (difdef >= 0)
			mark = "+";
		else if (difdef < 0) {
			difdef = -difdef;
			mark = "-";
		}
		defupstr = mark + std::to_string(difdef);

		//분리되었으므로 사용자의 보유 정보로 이동해야함
		for (int i = 0; i < 4; ) {
			//비어있는  배열 찾기or 동일한 아이디 찾기
			auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname2, i);
			if (keyid == 999) {
				pI->jjsetAry("keyid", "userweapon", i_uname2, wpaid, i);
				pI->jjsetAry("holding", "userweapon", i_uname2, 1, i);
				break;
			}
			else if (keyid == wpaid) {
				auto holding = pI->jjgetAry("holding", "userweapon", i_uname2, i);
				holding += 1;
				pI->jjsetAry("holding", "userweapon", i_uname2, holding, i);
				break;
			}
			else
				i++;
		}
		break;
	}
	case ACBOX1: {
		acbox1->removeAllChildren();
		break;
	}
	case ACBOX2: {
		acbox2->removeAllChildren();
		break;
	}
	default: break;
	}
	showW1();
	showW2();
	statusupdate();
}

void itemwinLayer::showW1() {
	std::string i_uname3 = dataSingleton::getInstance()->user;
	wpbox->removeAllChildren();
	shbox->removeAllChildren();
	pabox->removeAllChildren();
	acbox1->removeAllChildren();
	acbox2->removeAllChildren();

	auto wweapon = pI->jjgetInt("wweapon", i_uname3);
	auto wshirts = pI->jjgetInt("wshirts", i_uname3);
	auto wpants = pI->jjgetInt("wpants", i_uname3);
	auto wac1 = pI->jjgetInt("wac1", i_uname3);
	auto wac2 = pI->jjgetInt("wac2", i_uname3);
	log("show1 wweapon %d", wweapon);
	if (wweapon != 999) {
		auto wpfile = pI->jjgetSAry("pngname", "weapon", "weapon", wweapon);
		auto wpitem = MenuItemImage::create(wpfile, wpfile, CC_CALLBACK_1(itemwinLayer::undress, this));
		wpitem->setTag(WPBOX);
		auto wpitemb = Menu::create(wpitem, NULL);
		wpitemb->setPosition(65, 65);
		wpbox->addChild(wpitemb);
		log("show1 wweapon not 999");

	}
	if (wshirts != 999) {
		auto shfile = pI->jjgetSAry("pngname", "weapon", "weapon", wshirts);
		auto shitem = MenuItemImage::create(shfile, shfile, CC_CALLBACK_1(itemwinLayer::undress, this));
		shitem->setTag(SHBOX);
		auto shitemb = Menu::create(shitem, NULL);
		shitemb->setPosition(65, 65);
		shbox->addChild(shitemb);
	}
	if (wpants != 999) {
		auto pafile = pI->jjgetSAry("pngname", "weapon", "weapon", wpants);
		auto paitem = MenuItemImage::create(pafile, pafile, CC_CALLBACK_1(itemwinLayer::undress, this));
		paitem->setTag(PABOX);
		auto paitemb = Menu::create(paitem, NULL);
		paitemb->setPosition(65, 65);
		pabox->addChild(paitemb);
	}
	if (wac1 != 999) {
		auto acfile1 = pI->jjgetSAry("pngname", "weapon", "weapon", wac1);
		auto acitem1 = MenuItemImage::create(acfile1, acfile1, CC_CALLBACK_1(itemwinLayer::undress, this));
		acitem1->setTag(ACBOX1);
		auto acitemb1 = Menu::create(acitem1, NULL);
		acitemb1->setPosition(65, 65);
		acbox1->addChild(acitemb1);
	}
	if (wac2 != 999) {
		auto acfile2 = pI->jjgetSAry("pngname", "weapon", "weapon", wac2);
		auto acitem2 = MenuItemImage::create(acfile2, acfile2, CC_CALLBACK_1(itemwinLayer::undress, this));
		acitem2->setTag(ACBOX2);
		auto acitemb2 = Menu::create(acitem2, NULL);
		acitemb2->setPosition(65, 65);
		acbox2->addChild(acitemb2);
	}
}
void itemwinLayer::showW2() {
	std::string i_uname4 = dataSingleton::getInstance()->user;
	itembox1->removeAllChildren();
	itembox2->removeAllChildren();
	itembox3->removeAllChildren();
	itembox4->removeAllChildren();
	//가지고 있는 장비 배열을 가지고 오게 하고 배열 순서대로 배치하게 한다.
	//유저웨폰의 배열 내의 위치에 내용이 비여있는지 아닌지 알아야 할듯
	//널값이 아니라면 배치하도록 한다.
	//가지고 있는 아이템의 키아이디와
	//무기 제이슨에 있는 무기들의 키아이디를 찾아와 그 키아이디의 이미지와 효과를 가져오도록 한다.
	//weapon.json내가 수정했음 keyid는 곧 배열의 위치를 나타냄
	auto id1 = pI->jjgetAry("keyid", "userweapon", i_uname4, 0);//유저의 장비배열에서 가져옴
	if (id1 != 999) {//999는 아이템이 없다는 것

		auto wp1file1 = pI->jjgetSAry("pngname", "weapon", "weapon", id1);
		auto item1 = MenuItemImage::create(wp1file1, wp1file1, CC_CALLBACK_1(itemwinLayer::dress, this));
		item1->setTag(BOX1);
		auto item1b = Menu::create(item1, NULL);

		item1b->setPosition(65, 65);
		itembox1->addChild(item1b);

		auto hold1 = pI->jjgetAry("holding", "userweapon", i_uname4, 0);
		std::string holding1 = std::to_string(hold1);
		hLabel1 = LabelTTF::create(holding1, "Thonbri", 20);
		hLabel1->setPosition(Point(110, 20));
		itembox1->addChild(hLabel1);
	}


	auto id2 = pI->jjgetAry("keyid", "userweapon", i_uname4, 1);//유저의 장비배열에서 가져옴
	if (id2 != 999) {//999는 아이템이 없다는 것

		auto wp2file2 = pI->jjgetSAry("pngname", "weapon", "weapon", id2);
		auto item2 = MenuItemImage::create(wp2file2, wp2file2, CC_CALLBACK_1(itemwinLayer::dress, this));
		item2->setTag(BOX2);
		auto item2b = Menu::create(item2, NULL);
		item2b->setPosition(65, 65);
		itembox2->addChild(item2b);

		auto hold2 = pI->jjgetAry("holding", "userweapon", i_uname4, 1);
		std::string holding2 = std::to_string(hold2);
		hLabel2 = LabelTTF::create(holding2, "Thonbri", 20);
		hLabel2->setPosition(Point(110, 20));
		itembox2->addChild(hLabel2);
	}
	auto id3 = pI->jjgetAry("keyid", "userweapon", i_uname4, 2);//유저의 장비배열에서 가져옴
	if (id3 != 999) {//999는 아이템이 없다는 것

		auto wp3file3 = pI->jjgetSAry("pngname", "weapon", "weapon", id3);
		auto item3 = MenuItemImage::create(wp3file3, wp3file3, CC_CALLBACK_1(itemwinLayer::dress, this));
		item3->setTag(BOX3);
		auto item3b = Menu::create(item3, NULL);
		item3b->setPosition(65, 65);
		itembox3->addChild(item3b);

		auto hold3 = pI->jjgetAry("holding", "userweapon", i_uname4, 2);
		std::string holding3 = std::to_string(hold3);
		hLabel3 = LabelTTF::create(holding3, "Thonbri", 20);
		hLabel3->setPosition(Point(110, 20));
		itembox3->addChild(hLabel3);
	}
	auto id4 = pI->jjgetAry("keyid", "userweapon", i_uname4, 3);//유저의 장비배열에서 가져옴
	if (id4 != 999) {//999는 아이템이 없다는 것

		auto wp4file4 = pI->jjgetSAry("pngname", "weapon", "weapon", id4);
		auto item4 = MenuItemImage::create(wp4file4, wp4file4, CC_CALLBACK_1(itemwinLayer::dress, this));
		item4->setTag(BOX4);
		auto item4b = Menu::create(item4, NULL);
		item4b->setPosition(65, 65);
		itembox4->addChild(item4b);

		auto hold4 = pI->jjgetAry("holding", "userweapon", i_uname4, 3);
		std::string holding4 = std::to_string(hold4);
		hLabel4 = LabelTTF::create(holding4, "Thonbri", 20);
		hLabel4->setPosition(Point(110, 20));
		itembox4->addChild(hLabel4);

	}
	//이런형태로 20개를 만들어야 하는 건가...?

}

void itemwinLayer::statusupdate() {
	std::string i_uname5 = dataSingleton::getInstance()->user;
	item_win1->removeChild(atkatkstttf, 1);
	item_win1->removeChild(defdefstttf, 1);
	item_win1->removeChild(crittf, 1);
	item_win1->removeChild(cridamttf, 1);
	item_win1->removeChild(atkupttf, 1);
	item_win1->removeChild(defupttf, 1);
	item_win1->removeChild(criupttf, 1);
	item_win1->removeChild(cridamupttf, 1);

	int atk = pI->jjgetInt("atk", i_uname5);
	std::string atkstr = std::to_string(atk);

	int atkst = pI->jjgetInt("atkst", i_uname5);
	std::string atkststr = std::to_string(atkst);

	int def = pI->jjgetInt("def", i_uname5);
	std::string defstr = std::to_string(def);

	int defst = pI->jjgetInt("defst", i_uname5);
	std::string defststr = std::to_string(defst);

	int cri = pI->jjgetInt("cri", i_uname5);
	std::string cristr = std::to_string(cri);

	int cridam = pI->jjgetInt("cridam", i_uname5);
	std::string cridamstr = std::to_string(cridam);

	atkatkstttf = Label::createWithTTF("ATK  " + atkstr + " (+" + atkststr + ")", "nanumgo.ttf", 30);
	atkatkstttf->setAnchorPoint(Point(0, 0));
	atkatkstttf->setPosition(Point(120, 350));
	item_win1->addChild(atkatkstttf);

	defdefstttf = Label::createWithTTF("DEF  " + defstr + " (+" + defststr + ")", "nanumgo.ttf", 30);
	defdefstttf->setAnchorPoint(Point(0, 0));
	defdefstttf->setPosition(Point(120, 270));
	item_win1->addChild(defdefstttf);

	crittf = Label::createWithTTF("CRITICAL  " + cristr + " (%)", "nanumgo.ttf", 30);//+0은 장비 착용시 증각하도록
	crittf->setAnchorPoint(Point(0, 0));
	crittf->setPosition(Point(120, 190));
	item_win1->addChild(crittf);

	cridamttf = Label::createWithTTF("CRITICAL DAMAGE  " + cridamstr + " (%)", "nanumgo.ttf", 30);//+0은 장비 착용시 증각하도록
	cridamttf->setAnchorPoint(Point(0, 0));
	cridamttf->setPosition(Point(120, 110));
	item_win1->addChild(cridamttf);

	//장비를 장착했을 때 증가해지는 값을 옆에 표시하도록
	atkupttf = Label::createWithTTF("( " + atkupstr + " )", "nanumgo.ttf", 30);
	atkupttf->setAnchorPoint(Point(0, 0));
	atkupttf->setPosition(Point(600, 350));
	item_win1->addChild(atkupttf);

	defupttf = Label::createWithTTF("( " + defupstr + " )", "nanumgo.ttf", 30);
	defupttf->setAnchorPoint(Point(0, 0));
	defupttf->setPosition(Point(600, 270));
	item_win1->addChild(defupttf);

	criupttf = Label::createWithTTF("( " + criupstr + " )", "nanumgo.ttf", 30);
	criupttf->setAnchorPoint(Point(0, 0));
	criupttf->setPosition(Point(600, 190));
	item_win1->addChild(criupttf);

	cridamupttf = Label::createWithTTF("( " + cridamupstr + " )", "nanumgo.ttf", 30);
	cridamupttf->setAnchorPoint(Point(0, 0));
	cridamupttf->setPosition(Point(600, 110));
	item_win1->addChild(cridamupttf);


}

void itemwinLayer::undressWP() {
	std::string i_uname6 = dataSingleton::getInstance()->user;
	auto atk = pI->jjgetInt("atk", i_uname6);
	//장착되어 있던 아이템 있으면 빼주기
	if (pI->jjgetInt("wweapon", i_uname6) != 999) { //아이템 착용중이라는 것을 의미
		auto wshid = pI->jjgetInt("wweapon", i_uname6);
		auto wsheft = pI->jjgetAry("effect", "weapon", "weapon", wshid);
		atk -= wsheft;//아이템이 분리되므로 장착했었던 아이템의 효과를 빼준다.
		pI->jjsetInt(atk, "atk", i_uname6);
		wpbox->removeAllChildren();

		//분리되었으므로 사용자의 보유 정보로 이동해야함
		for (int i = 0; i < 4; ) {
			//비어있는  배열 찾기or 동일한 아이디 찾기
			auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname6, i);
			if (keyid == 999) {
				pI->jjsetAry("keyid", "userweapon", i_uname6, wshid, i);
				pI->jjsetAry("holding", "userweapon", i_uname6, 1, i);
				break;
			}
			else if (keyid == wshid) {
				auto holding = pI->jjgetAry("holding", "userweapon", i_uname6, i);
				pI->jjsetAry("holding", "userweapon", i_uname6, holding + 1, i);
				break;
			}
			else
				i++;
		}

	}

}
void itemwinLayer::undressSH() {
	std::string i_uname7 = dataSingleton::getInstance()->user;
	auto def = pI->jjgetInt("def", i_uname7);
	//장착되어 있던 아이템 있으면 빼주기
	if (pI->jjgetInt("wshirts", i_uname7) != 999) { //아이템 착용중이라는 것을 의미
		auto wshid = pI->jjgetInt("wshirts", i_uname7);
		auto wsheft = pI->jjgetAry("effect", "weapon", "weapon", wshid);
		def -= wsheft;//아이템이 분리되므로 장착했었던 아이템의 효과를 빼준다.

		pI->jjsetInt(def, "def", i_uname7);
		shbox->removeAllChildren();

		//분리되었으므로 사용자의 보유 정보로 이동해야함
		for (int i = 0; i < 4; ) {
			//비어있는  배열 찾기or 동일한 아이디 찾기
			auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname7, i);
			if (keyid == 999) {
				pI->jjsetAry("keyid", "userweapon", i_uname7, wshid, i);
				pI->jjsetAry("holding", "userweapon", i_uname7, 1, i);
				break;
			}
			else if (keyid == wshid) {
				auto holding = pI->jjgetAry("holding", "userweapon", i_uname7, i);
				pI->jjsetAry("holding", "userweapon", i_uname7, holding + 1, i);
				break;
			}
			else
				i++;
		}

	}

}
void itemwinLayer::undressPA() {
	std::string i_uname8 = dataSingleton::getInstance()->user;
	auto def = pI->jjgetInt("def", i_uname8);
	//장착되어 있던 아이템 있으면 빼주기
	if (pI->jjgetInt("wpants", i_uname8) != 999) { //아이템 착용중이라는 것을 의미
		auto wpaid = pI->jjgetInt("wpants", i_uname8);
		auto wpaeft = pI->jjgetAry("effect", "weapon", "weapon", wpaid);
		def = def - wpaeft;//아이템이 분리되므로 장착했었던 아이템의 효과를 빼준다.
		log("def %d wpaeft %d", def,wpaeft);
		pI->jjsetInt(def, "def", i_uname8);
		pabox->removeAllChildren();

		//분리되었으므로 사용자의 보유 정보로 이동해야함
		for (int i = 0; i < 4; ) {
			//비어있는  배열 찾기or 동일한 아이디 찾기
			auto keyid = pI->jjgetAry("keyid", "userweapon", i_uname8, i);
			if (keyid == 999) {
				pI->jjsetAry("keyid", "userweapon", i_uname8, wpaid, i);
				pI->jjsetAry("holding", "userweapon", i_uname8, 1, i);
				break;
			}
			else if (keyid == wpaid) {
				auto holding = pI->jjgetAry("holding", "userweapon", i_uname8, i);
				pI->jjsetAry("holding", "userweapon", i_uname8, holding + 1, i);
				break;
			}
			else
				i++;
		}

	}

}

void itemwinLayer::showW3() {
	std::string i_uname9 = dataSingleton::getInstance()->user;
	itembox1->removeAllChildren();
	itembox2->removeAllChildren();
	itembox3->removeAllChildren();
	itembox4->removeAllChildren();
	//가지고 있는 장비 배열을 가지고 오게 하고 배열 순서대로 배치하게 한다.
	//유저웨폰의 배열 내의 위치에 내용이 비여있는지 아닌지 알아야 할듯
	//널값이 아니라면 배치하도록 한다.
	//가지고 있는 아이템의 키아이디와
	//무기 제이슨에 있는 무기들의 키아이디를 찾아와 그 키아이디의 이미지와 효과를 가져오도록 한다.
	//weapon.json내가 수정했음 keyid는 곧 배열의 위치를 나타냄
	auto id1 = pI->jjgetAry("keyid", "userpotion", i_uname9, 0);//유저의 장비배열에서 가져옴
	if (id1 != 999) {//999는 아이템이 없다는 것

		auto hpfile1 = pI->jjgetSAry("png", "potion", "potion", id1);
		auto item1 = MenuItemImage::create(hpfile1, hpfile1, CC_CALLBACK_1(itemwinLayer::eatPotion, this));
		item1->setTag(BOX1);
		auto item1b = Menu::create(item1, NULL);

		item1b->setPosition(65, 65);
		itembox1->addChild(item1b);

		auto hold1 = pI->jjgetAry("holding", "userpotion", i_uname9, 0);
		std::string holding1 = std::to_string(hold1);

		hLabel1 = LabelTTF::create(holding1, "Thonbri", 20);
		hLabel1->setPosition(Point(110, 20));
		itembox1->addChild(hLabel1);

	}


	auto id2 = pI->jjgetAry("keyid", "userpotion", i_uname9, 1);//유저의 장비배열에서 가져옴
	if (id2 != 999) {//999는 아이템이 없다는 것

		auto hpfile2 = pI->jjgetSAry("png", "potion", "potion", id2);
		auto item2 = MenuItemImage::create(hpfile2, hpfile2, CC_CALLBACK_1(itemwinLayer::eatPotion, this));
		item2->setTag(BOX2);
		auto item2b = Menu::create(item2, NULL);

		item2b->setPosition(65, 65);
		itembox2->addChild(item2b);

		auto hold2 = pI->jjgetAry("holding", "userpotion", i_uname9, 1);
		std::string holding2 = std::to_string(hold2);
		hLabel2 = LabelTTF::create(holding2, "Thonbri", 20);
		hLabel2->setPosition(Point(110, 20));
		itembox2->addChild(hLabel2);

	}

}
void itemwinLayer::showW4() {
	std::string i_uname10 = dataSingleton::getInstance()->user;
	itembox1->removeAllChildren();
	itembox2->removeAllChildren();
	itembox3->removeAllChildren();
	itembox4->removeAllChildren();
	//가지고 있는 장비 배열을 가지고 오게 하고 배열 순서대로 배치하게 한다.
	//유저웨폰의 배열 내의 위치에 내용이 비여있는지 아닌지 알아야 할듯
	//널값이 아니라면 배치하도록 한다.
	//가지고 있는 아이템의 키아이디와
	//무기 제이슨에 있는 무기들의 키아이디를 찾아와 그 키아이디의 이미지와 효과를 가져오도록 한다.
	//weapon.json내가 수정했음 keyid는 곧 배열의 위치를 나타냄
	auto id1 = pI->jjgetAry("keyid", "useritem", i_uname10, 0);//유저의 장비배열에서 가져옴
	if (id1 != 999) {//999는 아이템이 없다는 것

		auto itemfile1 = pI->jjgetSAry("png", "item", "item", id1);
		auto item1 = Sprite::create(itemfile1);
		item1->setPosition(65, 65);
		itembox1->addChild(item1);

		auto hold1 = pI->jjgetAry("holding", "useritem", i_uname10, 0);
		std::string holding1 = std::to_string(hold1);
		hLabel1 = LabelTTF::create(holding1, "Thonbri", 20);
		hLabel1->setPosition(Point(110, 20));
		itembox1->addChild(hLabel1);
	}


	auto id2 = pI->jjgetAry("keyid", "useritem", i_uname10, 1);//유저의 장비배열에서 가져옴
	if (id2 != 999) {//999는 아이템이 없다는 것

		auto itemfile2 = pI->jjgetSAry("png", "item", "item", id2);
		auto itme2 = Sprite::create(itemfile2);
		itme2->setTag(BOX2);

		itme2->setPosition(65, 65);
		itembox2->addChild(itme2);

		auto hold2 = pI->jjgetAry("holding", "useritem", i_uname10, 1);
		std::string holding2 = std::to_string(hold2);
		hLabel2 = LabelTTF::create(holding2, "Thonbri", 20);
		hLabel2->setPosition(Point(110, 20));
		itembox2->addChild(hLabel2);
	}
	auto id3 = pI->jjgetAry("keyid", "useritem", i_uname10, 2);//유저의 장비배열에서 가져옴
	if (id3 != 999) {//999는 아이템이 없다는 것

		auto itemfile3 = pI->jjgetSAry("png", "item", "item", id3);
	
		auto item3 = Sprite::create(itemfile3);
		item3->setPosition(65, 65);
		item3->setTag(BOX3);
		itembox3 ->addChild(item3);

		auto hold3 = pI->jjgetAry("holding", "useritem", i_uname10, 2);
		std::string holding3 = std::to_string(hold3);
		hLabel3 = LabelTTF::create(holding3, "Thonbri", 20);
		hLabel3->setPosition(Point(110, 20));
		itembox3->addChild(hLabel3);
	}
	auto id4 = pI->jjgetAry("keyid", "useritem", i_uname10, 3);//유저의 장비배열에서 가져옴
	if (id4 != 999) {//999는 아이템이 없다는 것
		auto itemfile4 = pI->jjgetSAry("png", "item", "item", id4);
		auto item4 = Sprite::create(itemfile4);
		item4->setTag(BOX4);

		item4->setPosition(65, 65);
		itembox4->addChild(item4);

		auto hold4 = pI->jjgetAry("holding", "useritem", i_uname10, 3);
		std::string holding4 = std::to_string(hold4);
		hLabel4 = LabelTTF::create(holding4, "Thonbri", 20);
		hLabel4->setPosition(Point(110, 20));
		itembox4->addChild(hLabel4);

	}
	//이런형태로 20개를 만들어야 하는 건가...?

}

void itemwinLayer::eatPotion(Ref *sender) {
	std::string i_uname11 = dataSingleton::getInstance()->user;
	auto boxnum = (MenuItem*)sender;

	switch (boxnum->getTag()) {

	case BOX1: {
		auto maxPHP = pI->jjgetInt("maxhp", i_uname11);
		auto PHP = pI->jjgetInt("hp", i_uname11);
		if (dataSingleton::getInstance()->redcount > 0 && PHP > 0 && PHP < maxPHP) {
			dataSingleton::getInstance()->redcount -= 1;

			if (PHP + 200 > maxPHP)
				dataSingleton::getInstance()->pHP = maxPHP;
			else
				dataSingleton::getInstance()->pHP = dataSingleton::getInstance()->pHP + 200;
			pI->jjsetpArray("holding", i_uname11, dataSingleton::getInstance()->redcount, 0);
			pI->jjsetInt(dataSingleton::getInstance()->pHP, "hp", i_uname11);

			String *str = String::createWithFormat("%d", dataSingleton::getInstance()->redcount);
			hLabel1->setString(str->getCString());
		}
		break;
	}
	case BOX2: {
		auto maxPMP = pI->jjgetInt("maxmp", i_uname11);
		auto PMP = pI->jjgetInt("mp", i_uname11);
		if (dataSingleton::getInstance()->bluecount > 0 && PMP > 0 && PMP < maxPMP) {
			dataSingleton::getInstance()->bluecount -= 1;

			if (PMP + 200 > maxPMP)
				dataSingleton::getInstance()->pMP = maxPMP;
			else
				dataSingleton::getInstance()->pMP = dataSingleton::getInstance()->pMP + 200;
			pI->jjsetpArray("holding", i_uname11, dataSingleton::getInstance()->bluecount, 1);
			pI->jjsetInt(dataSingleton::getInstance()->pMP, "mp", i_uname11);

			String *str = String::createWithFormat("%d", dataSingleton::getInstance()->bluecount);
			hLabel2->setString(str->getCString());
		}
		break;
	}
	default: {
		break;
	}
	}
}