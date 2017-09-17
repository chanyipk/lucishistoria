#pragma once
#ifndef __MONTER_LAYER_H__
#define __MONSTER_LAYER_H__
#define M1 1
#define ACT3 30
#define ACT6 40
#define ANI 20
#define TAG_E 30

#include "cocos2d.h"

USING_NS_CC;

class MonsterLayer : public Layer
{
public:

	virtual bool init();
	ProgressTimer *m_pHPProgress;
	ProgressFromTo *progressToZero;
	Sprite* timer_gaze;
	Sprite* bar3;

	Sprite* sprM1;
	Sprite* sprM2;

	Vector<Sprite*>enemies;
	float hp;


	void setEnemy();

/*	void resetEnemy(Ref* sender);
	void setLeaf(float delta);
	void resetLeaf(Ref* sender);
	void update(float delta);
	void repeat(Ref* sender);
	void Hp(float delta);
	void F1(Ref* sender);
	void F2(Ref* sender);
	void F3(Ref* sender);
	void F4(Ref* sender);
	void HpBar();

	bool decHP;
	bool isChrash;
	bool isRepeat;
	bool flip1;
	bool flip2;
*/
	CREATE_FUNC(MonsterLayer);
};


#endif // __TOP_LAYER_H__#pragma once
