#include "MonsterLayer.h"
#include "MonsterLayer.h"
#include "DtopLayer.h"
#include "dataSingleton.h"

// on "init" you need to initialize your instance
bool MonsterLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	float gx = dataSingleton::getInstance()->groundx;
	auto m1 = Sprite::create("m1.png");
	m1->setAnchorPoint(Point(0.5, 0.5));
	m1->setPosition(Point(500, 390));
	m1->setTag(M1);
	this->addChild(m1);


}


void MonsterLayer::setEnemy()
{
	sprM1 = (Sprite*)this->getChildByTag(M1);


	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1);
	animation->addSpriteFrameWithFile("s1.png");
	animation->addSpriteFrameWithFile("s2.png");
	animation->addSpriteFrameWithFile("s3.png");
	animation->addSpriteFrameWithFile("s2.png");


	auto animate = Animate::create(animation);
	auto act = RepeatForever::create(animate);
	sprM1->runAction(act);
}


