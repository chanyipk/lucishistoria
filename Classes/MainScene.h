#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#define CLOSE_SPRITE 0
#define ENTERBTN 5
#define CIRBUT_1 3
#define CIRBUT_2 4
#define PLAYER_0 7
#define PLAYER_0_LB 8
#define PLAYER_0_BTN 6
#define STANDARD_SPRITE_1 1
#define STANDARD_SPRITE_2 2
#define PLAYER_SPRITE 9
#define PLAYER_ACTION 10
#define CHBTN 11
#define CABTN 12
#define DNOTICE 13
#define BACK 14
#define NL 15
#define CH 16
#define CA 17
#include "cocos2d.h"
#include "MapScene.h"
#include "MainLayer.h"
#include "EventLayer.h"
#include "NoticeLayer.h"
#include "dataSingleton.h"
#include "CharacterScene.h"

#include "Jdata.h"
#include "../../cocos2d/external/json/rapidjson.h"
#include "../../cocos2d/external/json/document.h"
#include "../../cocos2d/external/json/filestream.h"

USING_NS_CC;

using namespace rapidjson;

class MainScene : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();

	Sprite* playerSpr;
	Menu* plyr;
	MenuItemImage* player_but;
	Label* player0;
	std::string user_name;
	int namesize;
	int listnum;
	Sprite* back;
	Sprite* notice;
	Sprite* startwin;
	Menu* ebtn;

	void initBG();
	void gotomapScene(Ref *sender);

	void ButtonCallBack1(Ref *sender);
	void ButtonCallBack2(Ref *sender);
	void ButtonCallBack3(Ref *sender);

	void plyrListshow();
	void playerMake(Ref *sender);
	void playerSelect(Ref* sender);
	void playerDelete(Ref* sender);
	void deletenotice(Ref* sender);

	CREATE_FUNC(MainScene);

};

#endif
