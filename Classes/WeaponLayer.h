#pragma once
#ifndef __WeaponL_H__
#define __WeaponL_H__
#define WP_1 0  //절대 변경 금지, json배열 순서랑 같습니다.
#define WP_2 1  //절대 변경 금지, json배열 순서랑 같습니다.
#define WP_1IMG 2
#define WP_2IMG 3
#define WP_PLUS 5
#define WP_MINUS 6
#define WP_NUM 7
#define WP_MONEY 8
#define WP_BUY 9


#include "cocos2d.h"

USING_NS_CC;

class WeaponLayer : public Layer
{
public:
	static Scene* createScene();
	
	int wplminum;
	int wpcash;
	int wpselected;
	std::string wstrnum;
	std::string wdocdata;


	virtual bool init();
	void weaponSelect(cocos2d::Ref* sender);
	void weaponBuy();
	void wpcount(cocos2d::Ref *sender);
	void wprefresh();
	bool wponSprTouchBegan(Touch * touch, Event * event);

	CREATE_FUNC(WeaponLayer);
};


#endif 
