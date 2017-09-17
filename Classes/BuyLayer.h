#pragma once
#ifndef __BUYL_H__
#define __BUYL_H__

#include "cocos2d.h"
#define NUM 1

USING_NS_CC;

class BuyLayer : public Layer
{
public:

	static Scene* createScene();


	virtual bool init();

	void exit(cocos2d::Ref* sender);
	void ok(cocos2d::Ref* sender);
	CREATE_FUNC(BuyLayer);
};


#endif 