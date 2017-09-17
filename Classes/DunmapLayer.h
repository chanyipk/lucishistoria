#pragma once
#ifndef __DUNMAPL_H__
#define __DUNMAPL_H__
#define ENTER 0
#define CLOSE 1
#define INFO 3
#include "cocos2d.h"

USING_NS_CC;

class DunmapLayer : public Layer
{
public:
	virtual bool init();
	void onTouchBegan(Ref *sender);
	void onCloseTouchBegan(Ref *sender);
	CREATE_FUNC(DunmapLayer);
};


#endif #pragma once
