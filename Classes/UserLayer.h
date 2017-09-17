#pragma once
#pragma execution_character_set("utf-8")
#ifndef __USER_LAYER_H__
#define __USER_LAYER_H__
#define RISEN 0
#define SHIFT 1
#define REDP 10
#define statb 101
#define itemb 102
#define skillb 103
#define questb 104
#define backb 105
#define exitb 106
#define STATUSW 1000
#define BACK 109
#define MAGIC1 110
#define MAGIC2 111
#define RISE_WIN 112
#define BUT_1 113
#define BUT_2 114
#define OK 115
#define CA 116
#define MSG 117
#define OK1 118
#define CA1 119
#define EXIT 8000

#include "cocos2d.h"

USING_NS_CC;

class UserLayer : public Layer
{
public:

	virtual bool init();

	//캐릭터 상태정보 스프라이트

	Sprite* mpbar;
	ProgressTimer* PEXPbar;
	ProgressTimer* PHPbar;
	ProgressTimer* PMPbar;
	Label* hpnumsTTF;
	Label* mpnumsTTF;
	Label* expnumsTTF;
	Label* levelnumsTTF;
	Label* redNUM;//헤더에 선언하면 heap 에러 발생 + sprtie red 변수도 마찬가지
	Label* blueNUM;

	//Sprite* red;
	Menu* red;
	Menu* blue;
	//캐릭터 상태정보 수치
	int level;
	float PHP;//캐릭터 체력
	float PMP;
	float PEXP;
	float maxPEXP;
	 
	bool skilltime1;
	bool skilltime2;

	bool gameovertrue;
	bool playerDead;
	void gameover();
	void update(float delta);
	void redpotion();
	void levelupeffect();
	void risenpush(Ref* sender);
	void shiftpush(Ref* sender);
	void button(Ref* sender);
	void risenokay(Ref* sender);
	void onSprTouchBegan(Ref* sender);
	void onSprTouchBegan2(Ref* sender);
	void updateLabel1(Label* pLabel);
	void updateLabel2(Label* pLabel);
	void addLabelTimer1(Node* pParent, int nTime, const cocos2d::Vec2& pos);
	void addLabelTimer2(Node* pParent, int nTime, const cocos2d::Vec2& pos);
	void shiftokay(Ref* sender);
	void skillplace();
	void endClicked(Ref* sender);
	void endokayclicked(Ref* sender);
	void backClicked(Ref* sender);
	void backokayclicked(Ref* sender);
	Sprite* skillbox1;
	Sprite* skillbox2;
	Sprite* skillbox3;
	Sprite* skillbox4;

	CREATE_FUNC(UserLayer);
};


#endif // __TOP_LAYER_H__#pragma once
