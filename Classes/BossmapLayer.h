#pragma once
#pragma once
#ifndef __BossmapL_H__
#define __BossmapL_H__
#define ENTER 0
#define CLOSE 1
#define INFO 3
#include "cocos2d.h"

USING_NS_CC;

class BossmapLayer : public Layer
{
public:
	virtual bool init();
	void onTouchBegan(Ref *sender);
	void onCloseTouchBegan(Ref *sender);
	CREATE_FUNC(BossmapLayer);
};


#endif #pragma once
