#pragma once
#ifndef __J_DATA_H__
#define __J_DATA_H__

#include "cocos2d.h"

USING_NS_CC;

class Jdata : public Layer
{
public:

	static Scene* createScene();
	CREATE_FUNC(Jdata);

	bool init();

	bool fileRead(std::string fName);
	void writetoFile(std::string fName);

	std::string jjgetString(const char* keystr, std::string fName);
	void jjsetString(std::string setstr, const char* keystr, std::string fName);
	int jjgetInt(const char* keystr, std::string fName);
	void jjsetInt(int setint, const char* keystr, std::string fName);
	bool jjgetBool(const char* keystr, std::string fName);
	void jjsetBool(bool setbool, const char* keystr, std::string fName);
	void jjsetArray(const char* keystr, std::string fName, bool tf,int order);
	bool jjgetArray(const char* keystr, std::string fName, int order);
	
	int jjgetpArray(const char* keystr, std::string fName, int order);
	void jjsetpArray(const char* keystr, std::string fName, int setint, int order);

	std::string jjgetuserName(int tag);

	void jjnameAppend(std::string name);
	void jjnamedelete(std::string name);
	void jjnamelist();

	void jjplyrlist(std::string fName);
	void jjAppend(std::string fName);
	void jjPotionAppend();
	void jjWeaponAppend();
	void jjItemAppend();
	void jjSkillAppend();
	int jjgetIArray(const char* keyary, const char* keystr, int order);
	void jjsetIArray(const char* keyary, const char* keystr, int order, int setint);

	void jjsetQint(const char* keystr, std::string fName, int setint, int order);
	int jjgetQint(const char* keystr, std::string fName, int order);
	void jjsetAry(const char* keystr, const char * keyary, std::string fName, int setint, int order);
	int jjgetAry(const char* keystr, const char * keyary, std::string fName, int order);

	std::string jjgetSAry(const char* keystr, const char * keyary, std::string fName, int order);
	int jjgetArySize(const char* keystr, std::string fName);
	void Jdata::jjplyrdelete(std::string fName);
};

#endif