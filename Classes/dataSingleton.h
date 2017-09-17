#pragma once
#ifndef __dataSingleton__
#define __dataSingleton__
#include <iostream>

class dataSingleton
{
private:
	dataSingleton() {};
	static dataSingleton* m_plnstance;

public:
	static dataSingleton* getInstance();

	///////////////////////////////////
	bool elyonScene;
	// 여기에 변수 추가해서 쓰세요.
	bool clicked;//상점
	bool open;
	bool open2;
	bool winopen;
	bool enable;//이벤트 공지창
	bool touch;//시작버튼
	//캐릭터 위치
	bool playerDead;
	bool bosskill;
	float x;
	float y;
	//DtopLayer 
	float groundx;// 땅
	float groundy;
	float mon1x;//몬스터 위치
	float mon2x;
	float mon3x;
	float mon4x;
	float mon5x;
	//float sprM1x;
	float Mleafx1; //몬스터 입사귀 위치
	//float sprM2x;
	float Mleafx2; //몬스터 입사귀 위치
	//float sprM3x;
	float Mleafx3; //몬스터 입사귀 위치
	//플레이어 체력,마력, 경험치
	float pHP;
	float pEXP;
	float pMP;

	int itemnum;

	//충돌 박스 윛
	float floorbox1X, floorbox1Y;
	float floorbox2X, floorbox2Y;
	float floorbox3X, floorbox3Y;
	float floorbox4X, floorbox4Y;
	//포션 eat
	int redcount;
	int bluecount;

	int price;
	int userMoney;
	int total;
	int LL;
	//퀘스트 수락 여부 


	//퀘스트 완료 여부 
	bool SUC = false;

	//퀘스트 수락 후 경험치 올리기위한 변수
	bool rew = false;
	
	int cashtag;
	int holdingnum;
	int itemkeyid;
	bool isUser;

	bool skillpressedA;
	bool skillpressedS;
	bool skillpressedD;
	bool skillpressedF;

	bool isCM;
	bool risen;

	int steelcount;

	int time;
	int minute;


	bool skillupdate;

	std::string user;
	std::string keystr;
	int aryIndex;
	int cal_qty;
};


#endif // !
