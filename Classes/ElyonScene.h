#pragma once
#ifndef __ELYON_SCENE_H__
#define __ELYON_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //using namespace cocos2d

class ElyonScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(ElyonScene);
	void initBG();
	void changeScene(cocos2d::Ref* pSender);
	void ButtonCallBack(cocos2d::Ref* sender);

};

#endif 