#pragma once
#ifndef __CHARACTER_SCENE_H__
#define __CHARACTER_SCENE_H__
#define BOY_BUTTON 0
#define GIRL_BUTTON 1
#define BOY_IMAGE 2
#define GIRL_IMAGE 3


#include "ui/UIEditBox/UIEditBox.h"
#include "cocos2d.h"


USING_NS_CC; //using namespace cocos2d
using namespace ui;

class CharacterScene : public Layer, EditBoxDelegate
{
public:

	static Scene* createScene();
	virtual bool init();

	bool isStr = false;
	std::string inputStr;

	CREATE_FUNC(CharacterScene);


	void ButtonCallBack1(cocos2d::Ref* sender);
	void ButtonCallBack2(cocos2d::Ref* sender);
	void changeScene(cocos2d::Ref* sender);
	void initBG();

protected:
	void editBoxEditingDidBegin(EditBox* editBox);
	void editBoxEditingDidEnd(EditBox* editBox);
	void editBoxTextChanged(EditBox* editBox, const std::string& text);
	void editBoxReturn(EditBox* editBox);
};

#endif

