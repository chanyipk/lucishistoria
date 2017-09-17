#pragma once
#ifndef __Prolog_SCENE1_H__
#define __Prolog_SCENE1_H__
#define PRO_1 1
#define PRO_2 2
#define PRO_3 3
#define PRO_4 4
#define PRO_5 5

#include "cocos2d.h"

USING_NS_CC; //using namespace cocos2d

class PrologScene1 : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(PrologScene1);

	void changeScene(Ref* Sender);
	void skipScene(Ref* Sender);
	//메뉴로 구현하는 경우 void changeScene(Ref * sender);

};

#endif // __HELLOWORLD_SCENE_H__