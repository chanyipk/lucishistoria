#pragma once


#ifndef __skillwinL_H__
#define __skillwinL_H__
#define EXIT 0
#define BG 1
#define DAW 2
#define CANCEL 3
#define SKILLW1 1001
#define SKILLW2 1002

#define wearb 107
#define consumeb 108
#define makeskillb 109
#define questskillb 110

#define SBOX1 201
#define SBOX2 202
#define SBOX3 203
#define SBOX4 204

#define SBOXM1 205
#define SBOXM2 206
#define SBOXM3 207
#define SBOXM4 208

#define SK1 301
#define SK2 302
#define SK3 303
#define SK4 304

#define WP 401
#define SH 402
#define PA 403

#include "cocos2d.h"

USING_NS_CC;

class skillwinLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	bool isupload = false;
	


	Sprite* skill_win1;
	Sprite* skill_win2;
	Sprite* skillbox1;
	Sprite* skillbox2;
	Sprite* skillbox3;
	Sprite* skillbox4;
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

	
	//Menu* upload;
	//Menu* solve;;

	void skillmenu(Ref* sender);
	void showW1();//아이템1번째창 갱신
	void showW2();//아이템2번째창 갱신
	void setskillbox(int n);
	void closebut(Ref* sener);
	void infoopen(Ref* sender, int n, int b);

	void uploadskill(Ref* sender,int n);
	void clickedbox(Ref* sender,int n);
	void solveskill(Ref* sender,int n);
	void cancelupload();

	CREATE_FUNC(skillwinLayer);
};


#endif 
