#pragma once
#ifndef __Prolog_SCENE2__H__
#define __Prolog_SCENE2_H__


#include "cocos2d.h"

USING_NS_CC; //using namespace cocos2d

class PrologScene2 : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(PrologScene2);

	void changeScene(Ref* pSender);
	void skipScene(Ref* Sender);
	//메뉴로 구현하는 경우 void changeScene(Ref * sender);

};

#endif // __HELLOWORLD_SCENE_H__