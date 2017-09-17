#pragma once

#ifndef __statuswinL_H__
#define __statuswinL_H__
#define EXIT 0

#define STATUSW 1000

#include "cocos2d.h"

USING_NS_CC;

class statuswinLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	Sprite* status_win;
	Label* statttf;
	Label* atkstttf;
	Label* defstttf;
	Label* defstL;
	Label* atkstL;
	void statinfo();
	void addstat(Ref* sender, int n);
	void closebut(Ref* sender);
	CREATE_FUNC(statuswinLayer);
};


#endif 
