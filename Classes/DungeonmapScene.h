#ifndef __DUNGEONMAP_SCENE_H__
#define __DUNGEONMAP_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //using namespace cocos2d

class DungeonmapScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(DungeonmapScene);

	Sprite* dun2;

	//void changeScene(Ref * sender);
	
	bool onSprTouchBegan(Touch * touch, Event * event);
	bool onSprTouchBegan2(Touch * touch, Event * event);

	bool isTouch;
	void ButtonCallBack1(Ref* sender);
};

#endif // __MAP_SCENE_H__