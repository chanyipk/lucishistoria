#pragma once
#ifndef __NOTICEL_H__
#define __NOTICEL_H__
#define NOTICE 0
#define CLOSE 1

#include "cocos2d.h"

USING_NS_CC;

class NoticeLayer : public Layer
{
public:
	virtual bool init();
	void onCloseTouchBegan(Ref *sender);
	CREATE_FUNC(NoticeLayer);
};


#endif // __HELLOWORLD_SCENE_H__