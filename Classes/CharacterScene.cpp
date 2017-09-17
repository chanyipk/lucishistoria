#include "CharacterScene.h"
#include "SimpleAudioEngine.h"
#include "MapScene.h"
#include "MainScene.h"
#include "Jdata.h"
#include "dataSingleton.h"


USING_NS_CC;
using namespace ui;
Jdata* chpL;

Scene* CharacterScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CharacterScene::create();

	scene->addChild(layer);

	return scene;
}

bool CharacterScene::init()
{

	if (!Layer::init()) {
		return false;
	}

	initBG();

	Jdata* pL = dynamic_cast<Jdata*>(getParent());

	auto item_1 = MenuItemImage::create("boy1.png", "boy_push.png", CC_CALLBACK_1(CharacterScene::ButtonCallBack1, this));
	auto item_2 = MenuItemImage::create("girl1.png", "girl_push.png", CC_CALLBACK_1(CharacterScene::ButtonCallBack1, this));

	item_1->setTag(BOY_BUTTON);
	item_2->setTag(GIRL_BUTTON);

	auto select = Menu::create(item_1, NULL);
	select->alignItemsVertically();
	select->setScale(0.6);
	select->setAnchorPoint(Point(0.5, 0.5));
	select->setPosition(Point(1350, 500));
	this->addChild(select);

	auto select2 = Menu::create(item_2, NULL);
	select2->alignItemsVertically();
	select2->setScale(0.6);
	select2->setAnchorPoint(Point(0.5, 0.5));
	select2->setPosition(Point(1350, 300));
	this->addChild(select2);

	auto create1 = MenuItemImage::create("start.png", "start_push.png", CC_CALLBACK_1(CharacterScene::changeScene, this));
	auto start = Menu::create(create1, NULL);
	start->setAnchorPoint(Point(0.5, 0.5));
	start->setPosition(Point(1350, -80));
	start->setScale(0.6);
	this->addChild(start);

	auto editbox = EditBox::create(Size(500, 96), Scale9Sprite::create("name.png"));
	editbox->setPosition(Point(1000, 130));
	editbox->setPlaceHolder("\tName: ");
	editbox->setPlaceholderFont("", 50);
	editbox->setFont("", 30);
	editbox->setMaxLength(8);
	editbox->setFontColor(Color3B::YELLOW);
	this->addChild(editbox);
	editbox->setDelegate(this);


	auto man = Sprite::create("man_pro.png");
	man->setAnchorPoint(Point(0.5, 0.5));
	//	man->setPosition(Point(700, 540));
	man->setPosition(Point(960, 600));
	man->setScale(0.8);
	this->addChild(man);
	man->setTag(BOY_IMAGE);

	auto woman = Sprite::create("girl_pro.png");
	woman->setAnchorPoint(Point(0.5, 0.5));
	//	woman->setPosition(Point(700,540));
	woman->setPosition(Point(960, 600));
	woman->setVisible(false);
	woman->setScale(0.8);
	this->addChild(woman);
	woman->setTag(GIRL_IMAGE);


	auto before = MenuItemImage::create("before.png", "before_push.png", CC_CALLBACK_1(CharacterScene::ButtonCallBack2, this));
	auto beforebut = Menu::create(before, NULL);
	beforebut->alignItemsVertically();
	beforebut->setAnchorPoint(Point(0.5, 0.5));
	beforebut->setPosition(Point(100, 950));
	this->addChild(beforebut);

	return true;
}



void CharacterScene::ButtonCallBack1(cocos2d::Ref *sender)
{
	auto but = (MenuItem*)sender;
	Sprite *chr_1, *chr_2;

	chr_1 = (Sprite*)this->getChildByTag(BOY_IMAGE);
	chr_2 = (Sprite*)this->getChildByTag(GIRL_IMAGE);



	if (but->getTag() == BOY_BUTTON) {
		chr_1->setVisible(true);
		chr_2->setVisible(false);


	}
	else if (but->getTag() == GIRL_BUTTON) {
		chr_1->setVisible(false);
		chr_2->setVisible(true);


	}
}

void CharacterScene::ButtonCallBack2(cocos2d::Ref *sender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}


void CharacterScene::initBG()
{
	auto spr = Sprite::create("back.png");
	spr->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2, Director::getInstance()->
		getWinSize().height / 2));
	this->addChild(spr);

}

void CharacterScene::changeScene(Ref *sender)
{
	if (isStr == false) {//editBox 입력 없이 생성버튼을 누른 경우
		//중복확인도 해야하나?

		auto message = Label::createWithTTF("캐릭터의 이름을 입력해 주세요", "nanumgo.ttf", 100);
		message->setPosition(Point(Director::getInstance()->
			getWinSize().width / 2, Director::getInstance()->
			getWinSize().height / 2 + 100));
		message->setColor(Color3B::WHITE);
		this->addChild(message, 100);

	}
	else if (isStr == true) {//editBox를 통해 캐릭터 이름을 작성한 후 생성버튼을 누른 경우

		dataSingleton::getInstance()->user = inputStr;
		dataSingleton::getInstance()->isUser = true;

		chpL->jjAppend(inputStr);
		chpL->jjnameAppend(inputStr);
		chpL->jjPotionAppend();
		chpL->jjWeaponAppend();
		chpL->jjItemAppend();
		chpL->jjSkillAppend();

		Director::getInstance()->replaceScene(MainScene::createScene());
	}
}

void CharacterScene::editBoxEditingDidBegin(EditBox* editBox) {
	//editBox->setInputFlag(EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS);
}

void CharacterScene::editBoxEditingDidEnd(EditBox* editBox) {

}

void CharacterScene::editBoxTextChanged(EditBox* editBox, const std::string& text) {

}

void CharacterScene::editBoxReturn(EditBox* editBox) {

	isStr = true;
	inputStr = editBox->getText();
	editBox->setText(inputStr.c_str());

}