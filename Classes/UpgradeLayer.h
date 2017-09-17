#pragma once
#ifndef __UPGRADEL_H__
#define __UPGRADL_H__
#define WEAPON 1
#define SHILD 2
#define POTION 4
#define ACC 3
#define ITEM1 11
#define ITEM2 12
#define ITEM3 13
#define ITEM4 14


#include "cocos2d.h"

USING_NS_CC;

class UpgradeLayer : public Layer
{
public:
	virtual bool init();
	void itemSelect(cocos2d::Ref *sender);
	void buyLayer(cocos2d::Ref *sender);
	bool onCloseTouchBegan(Touch * touch, Event * event);
	bool onSprTouchBegan(Touch * touch, Event * event);

	CREATE_FUNC(UpgradeLayer);
};


#endif 
