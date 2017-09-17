#pragma once
#ifndef __StoreL_H__
#define __StoreL_H__
#define WEAPON 10
#define SHILD 20
#define POTION 40
#define ACC 30
#define ITEM1 11
#define ITEM2 12
#define ITEM3 13
#define ITEM4 14
#define W_LAYER 100
#define P_LAYER 101
#define S_LAYER 102

#include "cocos2d.h"

USING_NS_CC;

class StoreLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void itemSelect(Ref *sender);
	void buyLayer(Ref *sender);
	void closebut(Ref *sender);

	CREATE_FUNC(StoreLayer);
};


#endif 
