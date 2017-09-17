#ifndef __START_SCENE_H__
#define __START_SCENE_H__


#include "cocos2d.h"


USING_NS_CC; //using namespace cocos2d

class StartScene : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(StartScene);

	void changeScene(cocos2d::Ref* sender);

};

#endif

