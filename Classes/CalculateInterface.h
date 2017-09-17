#pragma once
#pragma execution_character_set("utf-8")
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__
#define NUM_1 1
#define NUM_2 2
#define NUM_3 3
#define NUM_4 4
#define NUM_5 5
#define NUM_6 6
#define NUM_7 7
#define NUM_8 8 
#define NUM_9 9
#define NUM_0 0
#define NUMBACK 10

#include "cocos2d.h"
#include "Jdata.h"
#include "dataSingleton.h"
#include "StoresaleLayer.h"

USING_NS_CC;

using namespace ui;

class CalculateInterface : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();

	bool isDigit = false;
	int resultnum = 0;

	Jdata* pCal;
	Label* result_lb = NULL;

	void calculate(cocos2d::Ref* sender);
	void close(cocos2d::Ref* sender);
	void enter(cocos2d::Ref* sender);

	CREATE_FUNC(CalculateInterface);

};

#endif