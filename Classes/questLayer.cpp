#include "questLayer.h"
#include "ElyonScene.h"
#include "dataSingleton.h"
#include "Jdata.h"

Jdata *pQ;

Scene* questLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = questLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool questLayer::init() {

	if (!Layer::init()) {
		return false;
	}
	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background);


	questwin = Sprite::create("store1.png");
	questwin->setAnchorPoint(Point(0.5, 0.5));
	questwin->setPosition(Point(Director::getInstance()->
		getWinSize().width /2, Director::getInstance()->
		getWinSize().height / 2));
	this->addChild(questwin);


	auto exit = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(questLayer::closebut, this));
	auto exit_b = Menu::create(exit, NULL);
	exit_b->setPosition(Point(1685, 962));
	this->addChild(exit_b);



	questClicked();
	return true;
}

void questLayer::questClicked()
{
	std::string quest_uname3 = dataSingleton::getInstance()->user;
	if (dataSingleton::getInstance()->open2 == false)
	{
		dataSingleton::getInstance()->open2 == true;
		if (pQ->jjgetArray("read", quest_uname3, 1) == true && pQ->jjgetArray("done", quest_uname3, 1) == false) {
			auto ep1_2 = MenuItemImage::create("ep1-2.png", "ep1-2_push.png", CC_CALLBACK_1(questLayer::questText, this));
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
		else if (pQ->jjgetArray("read", quest_uname3, 2) == true && pQ->jjgetArray("done", quest_uname3, 2) == false) {
			auto ep1_3 = MenuItemImage::create("ep1-3.png", "ep1-3_push.png", CC_CALLBACK_1(questLayer::questText, this));
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
		else if (pQ->jjgetArray("read", quest_uname3, 3) == true && pQ->jjgetArray("done", quest_uname3, 3) == false) {
			auto ep1_4 = MenuItemImage::create("ep1-4.png", "ep1-4_push.png", CC_CALLBACK_1(questLayer::questText, this));
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


		else if (pQ->jjgetArray("read", quest_uname3, 0) == true && pQ->jjgetArray("done", quest_uname3, 0) == false) {
			auto ep1_1 = MenuItemImage::create("ep1-1.png", "ep1-1_push.png", CC_CALLBACK_1(questLayer::questText, this));
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
		else if (pQ->jjgetArray("read", quest_uname3, 4) == true && pQ->jjgetArray("done", quest_uname3, 4) == false) {
			auto ep1_5 = MenuItemImage::create("ep1-5.png", "ep1-5_push.png", CC_CALLBACK_1(questLayer::questText, this));
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
	}
}
void questLayer::questText(Ref *sender)
{
	std::string quest_uname7 = dataSingleton::getInstance()->user;
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
		int cond = pQ->jjgetQint("condition", quest_uname7, 1);
		int now = pQ->jjgetQint("nowing", quest_uname7, 1);
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
		int cond = pQ->jjgetQint("condition", quest_uname7, 2);
		int now = pQ->jjgetQint("nowing", quest_uname7, 2);
		std::string conds = std::to_string(cond);
		std::string nows = std::to_string(now);
		auto connow = Label::createWithTTF(nows + " / " + conds, "nanumgo.ttf", 23);
		connow->setPosition(Point(770, 344));
		connow->setVisible(false);

		if (ep1_3_t->isVisible()) {
			connow->setVisible(false);
			ep1_3_t->setVisible(false);
		}
		else {
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
		int cond = pQ->jjgetQint("condition", quest_uname7, 1);
		int now = pQ->jjgetQint("nowing", quest_uname7, 1);
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

void questLayer::closebut(Ref *sender) {
	dataSingleton::getInstance()->open2 = false;
	this->removeAllChildren();
}
