#pragma once
#ifndef __suitL_H__
#define __suitL_H__
#define SH 1  //절대 변경 금지, json배열 순서랑 같습니다.
#define PA 2  //절대 변경 금지, json배열 순서랑 같습니다.
#define SHIMG 2
#define PAIMG 3
#define PLUS 5
#define MINUS 6
#define NUMB 7
#define MONEY 8
#define BUY 9


#include "cocos2d.h"

USING_NS_CC;

class suitLayer : public Layer
{
public:
	static Scene* createScene();

	int plminum;
	int cash;
	int selected;
	std::string strnum;
	std::string docdata;


	virtual bool init();
	void suitSelect(cocos2d::Ref* sender);
	void suitBuy();
	void count(cocos2d::Ref *sender);
	void refresh();
	bool onSprTouchBegan(Touch * touch, Event * event);

	CREATE_FUNC(suitLayer);
};


#endif 
