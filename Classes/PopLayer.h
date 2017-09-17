#pragma once
#ifndef __POPL_H__
#define __POPL_H__
#define ENTER 0
#define CLOSE 1
#define INFO 3
#include "cocos2d.h"

USING_NS_CC;

class PopLayer : public Layer
{
public:
	virtual bool init();
	void onTouchBegan(Ref *sender);
	void onCloseTouchBegan(Ref *sender);
	CREATE_FUNC(PopLayer);
};


#endif 