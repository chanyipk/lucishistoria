#pragma once
#ifndef __EVENTL_H__
#define __EVENTL_H__
#define EVENT 0
#define CLOSE 1
#include "cocos2d.h"

USING_NS_CC;

class EventLayer : public Layer
{
public:
	virtual bool init();
	void onCloseTouchBegan(Ref *sender);
	CREATE_FUNC(EventLayer);
};


#endif // __HELLOWORLD_SCENE_H__