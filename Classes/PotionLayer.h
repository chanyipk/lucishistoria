#pragma once
#ifndef __PotionL_H__
#define __PotionL_H__
#define HP 0  //���� ���� ����, json�迭 ������ �����ϴ�.
#define MP 1  //���� ���� ����, json�迭 ������ �����ϴ�.
#define HPIMG 2
#define MPIMG 3
#define PLUS 5
#define MINUS 6
#define NUMB 7
#define MONEY 8
#define BUY 9


#include "cocos2d.h"

USING_NS_CC;

class PotionLayer : public Layer
{
public:
	static Scene* createScene();

	int plminum;
	int cash;	
	int selected;
	std::string strnum;
	std::string docdata;

	
	virtual bool init();
	void potionSelect(cocos2d::Ref* sender);
	void potionBuy();
	void count(cocos2d::Ref *sender);
	void refresh();
	bool onSprTouchBegan(Touch * touch, Event * event);

	CREATE_FUNC(PotionLayer);
};


#endif 
