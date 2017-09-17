#pragma once
#pragma execution_character_set("utf-8")
#ifndef __SaleL_H__
#define __SaleL_H__

#define EXIT 0
#define TOTAL 1
#define POSSES 2

#define ITEMW1 1001
#define ITEMW2 1002

#define wearb 107
#define consumeb 108

#define BOX1 201
#define BOX2 202
#define BOX3 203
#define BOX4 204
#define BOX5 205
#define BOX6 206

#include "cocos2d.h"
#include "Jdata.h"
#include "dataSingleton.h"
#include "ui/CocosGUI.h"
#include "CalculateInterface.h"

USING_NS_CC;
using namespace ui;

class StoresaleLayer : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();

	Jdata* pSale;
	ListView* listview = NULL;

	Sprite* itembox1;
	Sprite* itembox2;
	Sprite* itembox3;
	Sprite* itembox4;
	Sprite* item_win1;//user_item_win
	Sprite* item_win2;//selected_item_wine

	Label* hLabel1;
	Label* hLabel2;
	Label* hLabel3;
	Label* hLabel4;
	Label* totallb;
	Label* posslb;
	ui::Widget *list_btn = NULL;
	//Node* item;

	ssize_t listsize;
	std::string keyStr;
	std::string keyStr2;

	int id1;
	int id2;
	int id3;
	int id4;
	int id5;
	int id6;
	int keyId = NULL;
	int user_keyId = NULL;
	int total_price = 0;

	void showW1();
	void showW2();
	int sell = 100;

	void itemmenu(Ref* sender);
	void menuclose(Ref *sender);

	void sale(cocos2d::Ref* sender);
	void salecancel(cocos2d::Ref* sender);

	void movetoList();
	void movefromLsit(cocos2d::Ref* sender);
	void openinterface(cocos2d::Ref* sender);

	CREATE_FUNC(StoresaleLayer);

};

#endif 