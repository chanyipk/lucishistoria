#pragma once
#ifndef __MAINL_H__
#define __MAINL_H__
#define WIN 0
#define START 1
#define CLOSE 2
#define BACKG 3
#include "cocos2d.h"

USING_NS_CC;

class MainLayer : public Layer
{
public:
	virtual bool init();
	void initBG();
	void onStartTouchBegan(Ref *sender);
	void onCloseTouchBegan(Ref *sender);
	CREATE_FUNC(MainLayer);
};


#endif // __HELLOWORLD_SCENE_H__