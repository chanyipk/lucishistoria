#pragma once


#ifndef __itemwinL_H__
#define __itemwinL_H__
#define EXIT 0

#define ITEMW1 1001
#define ITEMW2 1002

#define wearb 107
#define consumeb 108
#define makeitemb 109
#define questitemb 110

#define BOX1 201
#define BOX2 202
#define BOX3 203
#define BOX4 204

#define WPBOX 301
#define SHBOX 302
#define PABOX 303
#define ACBOX1 304
#define ACBOX2 305

#define WP 401
#define SH 402
#define PA 403

#include "cocos2d.h"

USING_NS_CC;

class itemwinLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();



	Sprite* item_win1;
	Sprite* item_win2;
	Sprite* itembox1;
	Sprite* itembox2;
	Sprite* itembox3;
	Sprite* itembox4;
	Sprite* wpbox;
	Sprite* pabox;
	Sprite* shbox;
	Sprite* acbox1;
	Sprite* acbox2;

	LabelTTF* hLabel1;
	LabelTTF* hLabel2;
	LabelTTF* hLabel3;
	LabelTTF* hLabel4;

	Label* atkatkstttf;
	Label* defdefstttf;
	Label* crittf;
	Label* cridamttf;

	Label* atkupttf;
	Label* defupttf;
	Label* criupttf;
	Label* cridamupttf;

	Menu* wpitemb;

	void itemmenu(Ref* sender);
	void showW1();//아이템1번째창 갱신
	void showW2();//아이템2번째창 갱신
	void showW3();//포션창
	void showW4();
	void closebut(Ref* sener);
	void dress(Ref* sender);
	void undress(Ref* sender);//버튼 눌러서 장비 해제
	void undressWP();//이미 장착되어 있는 아이템이 있는데 새로운 아이템을 찰 때. 자동 분리되도록
	void undressSH();
	void undressPA();
//	void undressAC1();
//	void undressAC2();
	void statusupdate();
	void eatPotion(Ref *sender);
	CREATE_FUNC(itemwinLayer);
};


#endif 
