#include "DungeonmapScene.h"
#include "DunmapLayer.h"
#include "BossmapLayer.h"
#include "ElyonScene.h"
#include "Jdata.h"
#include "dataSingleton.h"

Jdata *pDM;
Scene* DungeonmapScene::createScene()
{

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DungeonmapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool DungeonmapScene::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	std::string dun_uname1 = dataSingleton::getInstance()->user;

	pDM = dynamic_cast<Jdata*>(getParent());
	int level = pDM->jjgetInt("level", dun_uname1);

	//전체 지도를 이미지로 추가합니다.
	auto dunmap = Sprite::create("dm1.png");
	dunmap->setAnchorPoint(Point(0, 0));
	dunmap->setPosition(Point::ZERO);
	dunmap->setTag(0);
	this->addChild(dunmap);

	auto before = MenuItemImage::create("before.png", "before_push.png", CC_CALLBACK_1(DungeonmapScene::ButtonCallBack1, this));
	auto beforebut = Menu::create(before, NULL);
	beforebut->alignItemsVertically();
	beforebut->setAnchorPoint(Point(0.5, 0.5));
	beforebut->setPosition(Point(100,950));
	this->addChild(beforebut);

	auto dun1 = Sprite::create("dun1.png");
	dun1->setAnchorPoint(Point(0, 0));
	dun1->setPosition(Point(1200, 180));
	dun1->setTag(1);
	this->addChild(dun1);

	dun2 = Sprite::create("dun2_no.png");
	dun2->setAnchorPoint(Point(0, 0));
	dun2->setPosition(Point(500, 300));
	this->addChild(dun2);

	EventDispatcher * dispatcher = Director::getInstance()->getEventDispatcher();
	EventDispatcher * dispatcher2 = Director::getInstance()->getEventDispatcher();


	if (level >= 3)
	{
		dun2->setTexture(Director::getInstance()->getTextureCache()->addImage("dun2.png"));
		auto dunListener = EventListenerTouchOneByOne::create();
		dunListener->setSwallowTouches(true);
		dunListener->onTouchBegan = CC_CALLBACK_2(DungeonmapScene::onSprTouchBegan2, this);
		dispatcher2->addEventListenerWithSceneGraphPriority(dunListener, dun2);
	}

	


	auto sprListener = EventListenerTouchOneByOne::create();
	sprListener->setSwallowTouches(true);
	sprListener->onTouchBegan = CC_CALLBACK_2(DungeonmapScene::onSprTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(sprListener, dun1);

	
	

	return true;
}

//이 함수는 mappart1.png를 클릭했을때 실행되는 이벤트 처리를 합니다.
bool DungeonmapScene::onSprTouchBegan(Touch * touch, Event * event) {

	//터치한 객체를 타겟에 저장합니다.
	auto target = (Sprite *)event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);

	if (rect.containsPoint(pos)) {

		auto dunmaplayer = DunmapLayer::create();
		this->addChild(dunmaplayer);

		return true;
	}
	return false;
}

bool DungeonmapScene::onSprTouchBegan2(Touch * touch, Event * event) {

	//터치한 객체를 타겟에 저장합니다.
	auto target = (Sprite *)event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);

	if (rect.containsPoint(pos)) {

		auto bossmaplayer = BossmapLayer::create();
		this->addChild(bossmaplayer);

		return true;
	}
	return false;
}

void DungeonmapScene::ButtonCallBack1(Ref *sender)
{
	Director::getInstance()->popScene();
}