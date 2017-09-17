
#pragma once
#ifndef __DTOP_LAYER2_H__
#pragma execution_character_set("utf-8")
#define __DTOP_LAYER_H__
#define TAG_PLAYER_SPRITE 0 //사용자가 생성한 캐릭터의 스프라이트 태그입니다. 식별용으로 사용됩니다.
#define TAG_PLAYER_SPRITE_SPEED 30 //스피드 결정합니다.
#define TAG_SPRITE_PLAYER_ACTION_UP 1
#define TAG_SPRITE_PLAYER_ACTION_DOWN 2
#define TAG_SPRITE_PLAYER_ACTION_LEFT 3
#define TAG_SPRITE_PLAYER_ACTION_RIGHT 4
#define TAG_SPRITE_PLAYER_ACTION_ATTACK 5
#define TAG_SPRITE_PLAYER_ACTION_SKILL 6
#define TAG_SPRITE_PLAYER_ACTION_STAND 7
#define TAG_BG 20 //백그라운드의 태그입니다. 식별용으로 사용됩니다
#define TAG_BG_SPEED 60 //배경의 스피드를 결정합니다.
#define TAG_BG_LEFT 21
#define TAG_BG_RIGHT 22
#define TAG_JUMP 23
#define JUMPACT 10
#define M1 101
#define MonsterAttackMotion 5001
#define MonsterStandMotion 5000
#define MONEY 1000
#define REDP 1001
#define BLUEP 1003
#define RED2 1002
#define SKILL 1003
#define KNIFE 1004

#include "cocos2d.h"

USING_NS_CC;

class DtopLayer2 : public Layer
{
public:

	virtual bool init();

	bool isMove;
	bool isLeftPressed;
	bool isRightPressed;
	bool isUpPressed;
	bool isDownPressed;
	bool isAPressed;
	float isAttack;
	bool att1;
	bool att2;
	bool att3;
	bool att4;
	bool jumpYN;
	bool attYN;
	bool skillYN;


	//캐릭터가 보인다 안보인다
	bool playertrue;
	//게임이 종료됐다 안됐다
	bool gameovertrue;
	//스킬
	bool call;

	//캐릭터 상태정보 수치
	int PHP;
	int PMP;
	int PEXP;
	int PAtt;
	int PDef;
	int damage;
	int mdamage;

	Label* plyr_lb;
	//보스몬스터 
	Sprite *bmon;
	Rect* sMRect;
	int MAtt;
	int MDef;
	float MHP;
	ProgressTimer* MHPS;
	Label* MHPnum;
	Label* Mname;
	Sprite* mhps_back;
	Rect mRect;//플레이어 공격이 들어가는 구간
	void monSkillend();
	void MskillList(Ref* sender, int n);
	bool mSkilltrue = false;
	Sprite* root;
	float beforepx;
	bool isgas = false;
	bool gascu = false;

	//캐릭터부활
	ParticleSystemQuad* Prisen;

	Animation* act;
	Sprite* uk, *rk, *lk;
	Sprite* playerSpr;
	Sprite* ground1;
	ParallaxNode* voidNode;
	ParallaxNode* voidNode2;


	Sprite* ground2;
	Action* action1, *action2, *action3, *action4;
	Action* skill1;



	//아이템 스프라이트
	Sprite* money1;
	Sprite* money2;
	Sprite* money3;
	Sprite* money4;
	Sprite* money5;
	Sprite* red1;
	Sprite* red2;
	Sprite* red3;
	Sprite* blue1;
	Sprite* blue2;
	Sprite* blue3;

	Sprite* skill_eff;


	int delay = 50;
	int delay2 = 50;

	int skillhit;


	Rect pdropRect;
	Rect pgRect;
	Rect pRect;
	Rect pjRect;
	Rect ground1box;
	Rect ground3box;
	Rect ground3jumpbox;
	Rect ground2box;
	Rect ground2jumpbox;
	Rect groundnext1box;
	Rect groundnext1jumpbox;
	Rect groundnext2box;
	Rect groundnext2jumpbox;

//	void floornumCheck();
	void playerStandAction();
	void playerRunAction();
	void DropEnd();
	void JumpEnd();
	void AttackEnd(Ref* sender);
	void AttackEndAction();
	void skillEnd();

	void startMovingBackground();
	void stopMovingBackground();
	void moveBackground(float t);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	void update(float delta);

	void PattackMcrush(Ref* sender);

	//void playerDrop();
	void playerDead();
	void playerDis();
	void pill();
	void item();
	void giveexp();
	void DeleteMon();
	//void PlayerMonCruch();
	void damageeffect();
	void mdamageeffect();
	void skillList(Ref* sender, int n);
	void skillCrush();
	void skill_effEnd();

	void itemposition();

	void playerRisen();
	
	void setEnemy();
	void setMAttack();

	void callisgas();
	void callgascu();
	//캐릭터 점프 구현

	float a[500];
	float y[500];
	float accel;

	

	int skillid;

	void callClear();

	//혜니가 추가한 변수들
	int dunclear = false;
	int result;


	int havemoney;

	CREATE_FUNC(DtopLayer2);
};


#endif // __TOP_LAYER_H__#pragma once