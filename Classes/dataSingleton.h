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
	// ���⿡ ���� �߰��ؼ� ������.
	bool clicked;//����
	bool open;
	bool open2;
	bool winopen;
	bool enable;//�̺�Ʈ ����â
	bool touch;//���۹�ư
	//ĳ���� ��ġ
	bool playerDead;
	bool bosskill;
	float x;
	float y;
	//DtopLayer 
	float groundx;// ��
	float groundy;
	float mon1x;//���� ��ġ
	float mon2x;
	float mon3x;
	float mon4x;
	float mon5x;
	//float sprM1x;
	float Mleafx1; //���� �Ի�� ��ġ
	//float sprM2x;
	float Mleafx2; //���� �Ի�� ��ġ
	//float sprM3x;
	float Mleafx3; //���� �Ի�� ��ġ
	//�÷��̾� ü��,����, ����ġ
	float pHP;
	float pEXP;
	float pMP;

	int itemnum;

	//�浹 �ڽ� ��
	float floorbox1X, floorbox1Y;
	float floorbox2X, floorbox2Y;
	float floorbox3X, floorbox3Y;
	float floorbox4X, floorbox4Y;
	//���� eat
	int redcount;
	int bluecount;

	int price;
	int userMoney;
	int total;
	int LL;
	//����Ʈ ���� ���� 


	//����Ʈ �Ϸ� ���� 
	bool SUC = false;

	//����Ʈ ���� �� ����ġ �ø������� ����
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
