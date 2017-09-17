#include "GameScene2.h"
#include "DtopLayer2.h"
#include "dataSingleton.h"
#include "userLayer.h"
#include "ElyonScene.h"
#include "Jdata.h"
#include "SimpleAudioEngine.h"

Jdata* pG2;

Scene* GameScene2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool GameScene2::init() {
	if (!Layer::init()) {
		return false;
	}
	dataSingleton::getInstance()->elyonScene = false;

	initBG();
	change = 0;
	dataSingleton::getInstance()->time = 0;
	dataSingleton::getInstance()->minute = 0;

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Heated Battle.mp3", true);
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("siren.mp3");



	/*	auto MonsterLayer= MonsterLayer::create();
	this->addChild(MonsterLayer);
	*/
	auto particle = ParticleSystemQuad::create("rainpart.plist");
	particle->setDuration(-1);
	particle->setAnchorPoint(Point(0, 0));
	particle->setPosition(Point(0, 0));
	this->addChild(particle);


	addLabelTimer(this, 0, Vec2(1060, 900));

	auto DtopLayer2 = DtopLayer2::create();
	this->addChild(DtopLayer2);


	return true;



}
void GameScene2::initBG() {
	auto bgimg = Sprite::create("b2.png", Rect(0, 0, 1920, 1080));
	bgimg->setAnchorPoint(Point::ZERO);
	bgimg->setPosition(Point::ZERO);
	this->addChild(bgimg);

	auto tint1 = TintTo::create(0.5, 255, 0, 0);
	auto tint2 = TintTo::create(0.5, Color3B::BLACK);
	auto tint3 = TintTo::create(0.5, 255, 255, 255);
	auto seque = Sequence::create(tint1, tint2, NULL);
	auto rep = Repeat::create(seque, 3);
	auto end = Sequence::create(rep, tint3, NULL);
	bgimg->runAction(end);
}



void GameScene2::addLabelTimer(Node* pParent, int nTime, const cocos2d::Vec2& pos)
{
	auto pLabelTime = Label::create(StringUtils::toString(nTime), "Arial", 40);
	pLabelTime->setUserData((int*)nTime);
	pParent->addChild(pLabelTime);
	pLabelTime->setPosition(pos);
	pLabelTime->setVisible(false);

	minute1 = Label::create("0:", "Arial", 40);
	minute1->setPosition(Point(960, 900));
	minute1->setTag(MIN);
	minute1->setVisible(false);
	this->addChild(minute1);//ÂùÀÌ

	auto scheduleAction = CallFuncN::create(CC_CALLBACK_0(GameScene2::updateLabel, this, pLabelTime));
	auto repeatF = RepeatForever::create(Sequence::create(scheduleAction, DelayTime::create(1.0f), nullptr));
	pLabelTime->runAction(repeatF);

}

void GameScene2::updateLabel(Label* pLabel)
{
	if (pLabel)
	{
		int userTime = (int)(pLabel->getUserData());
		userTime += 1;
		pLabel->setString(StringUtils::toString(userTime));
		dataSingleton::getInstance()->time = userTime;

		if (dataSingleton::getInstance()->bosskill == true)
		{
			pLabel->stopAllActions();
		}

		if (userTime == 60) {
		
			userTime = 0;
			dataSingleton::getInstance()->time = userTime;
			pLabel->setString(StringUtils::toString(userTime));
			change++;
			dataSingleton::getInstance()->minute = change;
			std::string min = std::to_string(change);
			/*if (change == 1) {
				minute1->setString("1:");
				dataSingleton::getInstance()->minute = 1;
			}
			else if (change == 2) {

				minute1->setString("2:");
				dataSingleton::getInstance()->minute = 1;
			}
			else if (change == 3) {
				minute1->setString("3:");
				pLabel->stopAllActions();
				this->removeChild(pLabel);
			}*/
			minute1->setString(min + ":");
		
		}

	
		pLabel->setUserData((int*)userTime);
	}

}
