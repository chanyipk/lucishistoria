#pragma once
#ifndef __GAME_SCENE2_H__
#define __GAME_SCENE2_H__
#pragma execution_character_set("utf-8")
#define TAG_PLAYER_SPRITE 10
#define TAG_SPRITE_PLAYER_ACTION_LEFT 11
#define TAG_SPRITE_PLAYER_ACTION_UP 12
#define TAG_SPRITE_PLAYER_ACTION_RIGHT 13
#define MIN 14
#define MIN2 15

#include "cocos2d.h"

USING_NS_CC;

class GameScene2 : public Layer
{
public:
	static Scene* createScene();


	virtual bool init();
	CREATE_FUNC(GameScene2);

	Sprite* bgimg;
	void endclicked(Ref* sender);
	void okayclicked(Ref* sender);
	void updateLabel(Label* pLabel);
	void addLabelTimer(Node* pParent, int nTime, const cocos2d::Vec2& pos);
	void initBG();

	int change;
	Label* minute1;

};

#endif 
