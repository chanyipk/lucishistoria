#pragma once
#ifndef __CLEAR_LAYER_H__
#define __CLEAR_LAYER_H__
#pragma execution_character_set("utf-8")


#include "cocos2d.h"

USING_NS_CC;

class clearLayer : public Layer
{
public:
	static Scene* createScene();


	virtual bool init();
	CREATE_FUNC(clearLayer);

	Sprite* bg;
	Sprite* rank;
	Label* cleartime;
	int min;
	int sec;
	void timef();
	void rankf();
	void rewardf();
	int rwset(int n);
	void changeScene();
	

};

#endif 
