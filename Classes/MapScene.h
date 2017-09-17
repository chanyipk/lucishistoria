#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //using namespace cocos2d

class MapScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(MapScene);

	//void changeScene(Ref * sender);
	bool onPositionTouchBegan(Touch * touch, Event * event);
	bool onSprTouchBegan(Touch * touch, Event * event);
	bool onCloseTouchBegan(Touch * touch, Event * event);
	bool onPopTouchBegan(Touch * touch, Event * event);
	bool isTouch;
};

#endif // __MAP_SCENE_H__