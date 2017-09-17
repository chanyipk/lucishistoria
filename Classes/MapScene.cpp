#include "MapScene.h"
#include "ElyonScene.h"
#include "PopLayer.h"
#include "SimpleAudioEngine.h"

Scene* MapScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("In Game.mp3", true);
	//전체 지도를 이미지로 추가합니다.
	auto mapimg = Sprite::create("map.png");
	mapimg->setAnchorPoint(Point(0, 0));
	mapimg->setPosition(Point::ZERO);
	mapimg->setTag(0);
	this->addChild(mapimg);

	isTouch = false;

	//튜토리얼에서 진행할 구역 이미지를 추가합니다.
	//사용자가 이 구역을 선택할 수 있도록 선명한 이미지로 두었습니다.
	auto mappart1 = Sprite::create("part1.png");
	mappart1->setAnchorPoint(Point(0, 0));
	mappart1->setPosition(Point(420, 300));
	mappart1->setTag(1);
	this->addChild(mappart1);

	EventDispatcher * dispatcher = Director::getInstance()->getEventDispatcher();

	//해당 구역 이미지를 선택할 경우 발생되는 이벤트의 리스너를 생성합니다.
	//리스너 함수의 이름은 onSprTouchBegan입니다.
	auto sprListener = EventListenerTouchOneByOne::create();
	sprListener->setSwallowTouches(true);
	sprListener->onTouchBegan = CC_CALLBACK_2(MapScene::onSprTouchBegan, this);
	//구역 이미지인 mappart1.png를 클릭했을때 해당 맵으로 들어갈 수 있도록 이벤트와 mappart1.png이미지를 연결합니다. 
	dispatcher->addEventListenerWithSceneGraphPriority(sprListener, mappart1);

	return true;
}

//이 함수는 mappart1.png를 클릭했을때 실행되는 이벤트 처리를 합니다.
bool MapScene::onSprTouchBegan(Touch * touch, Event * event) {

	//터치한 객체를 타겟에 저장합니다.
	auto target = (Sprite *)event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);

	if (rect.containsPoint(pos)) {

		auto poplayer = PopLayer::create();
		this->addChild(poplayer);

		//auto info = Sprite::create("map_info.png");
		//info->setAnchorPoint(Point(0, 0));
		//info->setPosition(Point(400, 400));
		//this->addChild(info);
		//해당 맵의 이미지를 선택하면 관련된 화면으로 전환해 줍니다.
		//Director::getInstance()->replaceScene(ElyonScene::createScene());
		return true;
	}
	return false;
}