

#pragma once
#ifndef __DTOP_LAYER_H__
#pragma execution_character_set("utf-8")
#define __DTOP_LAYER_H__
#define TAG_PLAYER_SPRITE 0 //����ڰ� ������ ĳ������ ��������Ʈ �±��Դϴ�. �ĺ������� ���˴ϴ�.
#define TAG_PLAYER_SPRITE_SPEED 30 //���ǵ� �����մϴ�.
#define TAG_SPRITE_PLAYER_ACTION_UP 1
#define TAG_SPRITE_PLAYER_ACTION_DOWN 2
#define TAG_SPRITE_PLAYER_ACTION_LEFT 3
#define TAG_SPRITE_PLAYER_ACTION_RIGHT 4
#define TAG_SPRITE_PLAYER_ACTION_ATTACK 5
#define TAG_SPRITE_PLAYER_ACTION_SKILL 6
#define TAG_SPRITE_PLAYER_ACTION_STAND 7
#define TAG_BG 20 //��׶����� �±��Դϴ�. �ĺ������� ���˴ϴ�
#define TAG_BG_SPEED 60 //����� ���ǵ带 �����մϴ�.
#define TAG_BG_LEFT 21
#define TAG_BG_RIGHT 22
#define TAG_JUMP 23
#define JUMPACT 10
#define M1 101
#define monsterAction_1 201
#define MonsterWalkMotion 501
#define MonsterShiftMotion 502
#define MonsterAttackMotion 503
#define LEAFATK1 504
#define LEAFATK2 505
#define LEAFATK3 506
#define MONEY 1000
#define REDP 1001
#define BLUEP 1003
#define RED2 1002
#define SKILL 1003
#define STEEL 1004

#include "cocos2d.h"

USING_NS_CC;

class DtopLayer : public Layer
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
	float mPositionX;
	bool Matt1;
	bool Matt2;
	bool Matt3;
	bool Matt4;
	bool leafcru1;
	bool leafcru2;
	bool leafcru3;
	//���Ͱ� ���δ� �Ⱥ��δ�
	bool sprM1true;
	bool sprMa1true;
	bool sprM2true;
	bool sprMa2true;
	bool sprM3true;
	bool sprMa3true;
	bool sprM4true;
	bool sprM5true;
	//ĳ���Ͱ� ���δ� �Ⱥ��δ�
	bool playertrue;
	//������ ����ƴ� �ȵƴ�
	bool gameovertrue;
	//��ų
	bool call;
	//���� �������� ��ġ
	float MHP1;
	float mhppercent1;
	float MHP2;
	float mhppercent2;
	float MHP3;
	float mhppercent3;
	float MHP4;
	float mhppercent4;
	float MHP5;
	float mhppercent5;
	int MAtt;
	int MDef;
	//ĳ���� �������� ��ġ
	int PHP;
	int PMP;
	int PEXP;
	int PAtt;
	int PDef;
	int damage;
	int mdamage;
	//���� �ѹ�
	int monsternum;
	//���� ���� ��ġ��
	float leafx1;
	float leafy1;
	float leafx2;
	float leafy2;
	float leafx3;
	float leafy3;
	//�� ��ġ
	int floornum;

	int kill = 0;
	Label* count;
	Label* plyr_lb;

	//���� ü�� ��������Ʈ
	ProgressTimer* MHPS1;
	Label* numsTTF1;
	Label* monname1;
	Sprite* mhps_back1;
	//���� �ٻ�� ����
	Sprite* leafatk1;
	ParticleSystemQuad* mparticle1;
	//����2
	ProgressTimer* MHPS2;
	Label* numsTTF2;
	Label* monname2;
	Sprite* mhps_back2;
	//���� �ٻ�� ����
	Sprite* leafatk2;
	ParticleSystemQuad* mparticle2;
	//����3
	ProgressTimer* MHPS3;
	Label* numsTTF3;
	Label* monname3;
	Sprite* mhps_back3;
	//���� �ٻ�� ����
	Sprite* leafatk3;
	ParticleSystemQuad* mparticle3;
	//����4
	ProgressTimer* MHPS4;
	Label* numsTTF4;
	Label* monname4;
	Sprite* mhps_back4;
	//����5
	ProgressTimer* MHPS5;
	Label* numsTTF5;
	Label* monname5;
	Sprite* mhps_back5;

	//ĳ���ͺ�Ȱ
	ParticleSystemQuad* Prisen;

	Animation* act;
	Sprite* uk, *rk, *lk;
	Sprite* playerSpr;
	Sprite* ground1;
	ParallaxNode* voidNode;
	ParallaxNode* voidNode2;


	Sprite* ground2, *ground3, *groundnext1, *groundnext2;
	Action* action1, *action2, *action3, *action4;
	Action* skill1;

	//���� ��������Ʈ
	Sprite* sprM1;
	Sprite* sm1;
	Sprite* sprMa1;
	Sprite* sprM2;
	Sprite* sm2;
	Sprite* sprMa2;
	Sprite* sprM3;
	Sprite* sm3;
	Sprite* sprMa3;
	Sprite* leaf;
	Sprite* sm4;   //����
	Sprite* sprM4;
	Sprite* sm5;   //����
	Sprite* sprM5;

	//������ ��������Ʈ
	Sprite* money1;
	Sprite* money2;
	Sprite* money3;
	Sprite* money4;
	Sprite* money5;
	Sprite* red1;
	Sprite* red2;
	Sprite* red3;
	Sprite* steel1;
	Sprite* steel2;
	Sprite* blue1;
	Sprite* blue2;
	Sprite* blue3;

	Sprite* skill_eff;


	int delay = 50;
	int delay2 = 50;

	int skillhit;

	//�浹�ڽ�
	Rect pRect;
	Rect pgRect;
	Rect pdropRect;
	Rect mRect1;
	Rect mRect2;
	Rect mRect3;
	Rect mRect4;
	Rect mRect5;
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
	Rect leafRect1;
	Rect leafRect2;
	Rect leafRect3;

	void floornumCheck();
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
	void setEnemy();
	void MonAttstart1();
	void MonAttstart2();
	void MonAttstart3();
	void MonAttend1();
	void MonAttend2();
	void MonAttend3();
	void setLeaf1();
	void setLeaf2();
	void setLeaf3();
	void DeleteMon1(Ref* sender);
	void DeleteMon2(Ref* sender);
	void DeleteMon3(Ref* sender);
	void DeleteMon4(Ref* sender);
	void DeleteMon5(Ref* sender);
	void DeleteLeaf1(Ref* sender);
	void DeleteLeaf2(Ref* sender);
	void DeleteLeaf3(Ref* sender);
	void playerDrop();
	void playerDead();
	void playerDis();
	void pill(Ref* sender, int n);
	void item(Ref* sender, int n);
	void giveexp(Ref* sender);
	void clearLabel();
	void clearBack();
	void damageeffect();
	void mdamageeffect();

	void skillList(Ref* sender, int n);
	void skillCrush();
	void skill_effEnd();

	void itemposition();

	void changeScene();

	void playerRisen();
	//ĳ���� ���� ����

	float a[500];
	float y[500];
	float accel;

	//����ġ
	float moneyx1;
	float moneyx2;
	float moneyx3;
	float moneyx4;
	float moneyx5;
	float moneygx1;
	float moneygx2;
	float moneygx3;
	float moneygx4;
	float moneygx5;
	//������ġ
	float redx1;
	float redx2;
	float redx3;
	float redx4;
	float redx5;
	float redgx1;
	float redgx2;
	float redgx3;
	float redgx4;
	float redgx5;
	//������ġ
	float bluex1;
	float bluex2;
	float bluex3;
	float bluex4;
	float bluex5;
	float bluegx1;
	float bluegx2;
	float bluegx3;
	float bluegx4;
	float bluegx5;

	int skillid;
	//���� ĳ���� �浹
	void PlayerMonCruch();


	//���ϰ� �߰��� ������
	int m_kill = 0;
	int result;


	int havemoney;

	CREATE_FUNC(DtopLayer);
};


#endif // __TOP_LAYER_H__#pragma once