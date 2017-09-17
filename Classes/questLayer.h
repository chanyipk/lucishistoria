#pragma once

#ifndef __questL_H__
#define __questL_H__
#define EP1_1 5001
#define EP1_2 5002
#define EP1_3 5003
#define EP1_4 5004
#define EP1_5 5005

#include "cocos2d.h"

USING_NS_CC;

class questLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void closebut(Ref *sender);
	void questText(Ref* sender);
	void questClicked();

	Sprite *questwin;
	Sprite* ep1_1_t;
	Sprite* ep1_2_t;
	Sprite* ep1_3_t;
	Sprite* ep1_4_t;
	Sprite* ep1_5_t;

	CREATE_FUNC(questLayer);
};


#endif 
