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
	//��ü ������ �̹����� �߰��մϴ�.
	auto mapimg = Sprite::create("map.png");
	mapimg->setAnchorPoint(Point(0, 0));
	mapimg->setPosition(Point::ZERO);
	mapimg->setTag(0);
	this->addChild(mapimg);

	isTouch = false;

	//Ʃ�丮�󿡼� ������ ���� �̹����� �߰��մϴ�.
	//����ڰ� �� ������ ������ �� �ֵ��� ������ �̹����� �ξ����ϴ�.
	auto mappart1 = Sprite::create("part1.png");
	mappart1->setAnchorPoint(Point(0, 0));
	mappart1->setPosition(Point(420, 300));
	mappart1->setTag(1);
	this->addChild(mappart1);

	EventDispatcher * dispatcher = Director::getInstance()->getEventDispatcher();

	//�ش� ���� �̹����� ������ ��� �߻��Ǵ� �̺�Ʈ�� �����ʸ� �����մϴ�.
	//������ �Լ��� �̸��� onSprTouchBegan�Դϴ�.
	auto sprListener = EventListenerTouchOneByOne::create();
	sprListener->setSwallowTouches(true);
	sprListener->onTouchBegan = CC_CALLBACK_2(MapScene::onSprTouchBegan, this);
	//���� �̹����� mappart1.png�� Ŭ�������� �ش� ������ �� �� �ֵ��� �̺�Ʈ�� mappart1.png�̹����� �����մϴ�. 
	dispatcher->addEventListenerWithSceneGraphPriority(sprListener, mappart1);

	return true;
}

//�� �Լ��� mappart1.png�� Ŭ�������� ����Ǵ� �̺�Ʈ ó���� �մϴ�.
bool MapScene::onSprTouchBegan(Touch * touch, Event * event) {

	//��ġ�� ��ü�� Ÿ�ٿ� �����մϴ�.
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
		//�ش� ���� �̹����� �����ϸ� ���õ� ȭ������ ��ȯ�� �ݴϴ�.
		//Director::getInstance()->replaceScene(ElyonScene::createScene());
		return true;
	}
	return false;
}