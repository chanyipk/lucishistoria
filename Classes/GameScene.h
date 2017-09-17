
#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#define LEAF 1000
#include "cocos2d.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	void endclicked(Ref* sender);
	void okayclicked(Ref* sender);


	CREATE_FUNC(GameScene);


	void initBG();

};

#endif 

