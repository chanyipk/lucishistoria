#pragma once
#ifndef __TOP_LAYER_H__
#define __TOP_LAYER_H__
#define TAG_PLAYER_SPRITE 1 //사용자가 생성한 캐릭터의 스프라이트 태그입니다. 식별용으로 사용됩니다.
#define TAG_PLAYER_SPRITE_SPEED 30 //스피드 결정합니다.
#define TAG_SPRITE_PLAYER_ACTION_UP 1
#define TAG_SPRITE_PLAYER_ACTION_DOWN 2
#define TAG_SPRITE_PLAYER_ACTION_LEFT 3
#define TAG_SPRITE_PLAYER_ACTION_RIGHT 4
#define TAG_BG 1 //백그라운드의 태그입니다. 식별용으로 사용됩니다
#define TAG_BG_SPEED 60 //배경의 스피드를 결정합니다.
#define TAG_BG_LEFT 1
#define TAG_BG_RIGHT 1
#define TAG_JUMP 1
#define NPC1 11
#define NPC2 12
#define NPC3 13
#define NPC4 14
#define NPC5 15
#define COMU 50
#define QUEST_O 21
#define STORE 22
#define UPGRADE 23
#define MAKE 24
#define Q_WIN 25

#define NEXT 28
#define CO1 29
#define CO2 30
#define SUB 31

#define QUEST_C 33
#define O_TITLE 101

#define QM 1001
#define QMING 1002
#define CM 1003

#define NPC1_Q 2001
#define NPC2_Q 2002
#define NPC3_Q 2003
#define NPC4_Q 2004
#define NPC5_Q 2005

#define EP1_1 5001
#define EP1_2 5002
#define EP1_3 5003
#define EP1_4 5004
#define EP1_5 5005

#define ITEM_CLOSE 6001
#define ITEM_W 6002
#define WE1 6003
#define WE2 6004

#include "cocos2d.h"

USING_NS_CC;

class TopLayer : public Layer
{
public:

	virtual bool init();
	bool isMove;
	bool isLeftPressed;
	bool isRightPressed;
	bool isUpPressed;
	bool isDownPressed;
	bool jumpYN;
	bool isnpcClicked;
	bool isCollusion;
	bool text1;

	float gx;
	Menu* npc1;
	Menu* quest1;
	Menu* quest3;
	Sprite* playerSpr;
	Sprite* ground;

	ParallaxNode* voidNode;
	Sprite* ground2;
	MenuItemImage* npc1_i;
	MenuItemImage* npc2_i;
	MenuItemImage* npc3_i;
	MenuItemImage* npc4_i;
	MenuItemImage* npc5_i;

	MenuItemImage* quest;
	MenuItemImage* quest2;
	Menu* quest_ok;

	void startMovingBackground();
	void stopMovingBackground();
	void moveBackground(float t);
	void update(float delta);
	void quest_ing();
	void storelayer(Ref *sender);
	void upgradelayer(Ref *sender);
	void npcClicked(Ref *sender);
	void questClicked(Ref *sender);
	void questText(Ref* sender);
	void nextClicked(Ref *sender);
	void completeClicked();

	void OKClicked();
	void closeClicked();
	void changeScene(Ref* pSender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void changeLabel();
	void salelayer(Ref* sender);
	int label_num;

	//퀘스트 스프라이트
	Sprite* qm;
	Sprite* qming;
	Sprite* cm;
	Menu* next;

	Sprite* comupro;
	Label* comunication;
	Label* plyr_lb;

	Sprite* ep1_1_t;
	Sprite* ep1_2_t;
	Sprite* ep1_3_t;
	Sprite* ep1_4_t;
	Sprite* ep1_5_t;



	int nextnum;
	CREATE_FUNC(TopLayer);
};


#endif // __TOP_LAYER_H__