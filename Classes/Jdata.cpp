#include "Jdata.h"
#include <cstdio>
#include "../../cocos2d/external/json/rapidjson.h"
#include "../../cocos2d/external/json/document.h"
#include "../../cocos2d/external/json/filestream.h"
#include "../../cocos2d/external/json/stringbuffer.h"
#include "../../cocos2d/external/json/writer.h"
#include "../../cocos2d/external/json/filewritestream.h"
#include "../../cocos2d/external/json/filereadstream.h"

using rapidjson::FileReadStream;
using rapidjson::FileWriteStream;

USING_NS_CC;

using namespace rapidjson;

Document doc;
char readBuffer[65536];
StringBuffer writeBuffer;

Scene* Jdata::createScene()
{
	auto scene = Scene::create();
	auto layer = Jdata::create();
	scene->addChild(layer);
	return scene;
}

bool Jdata::init()
{

	if (!Layer::init())
	{
		return false;
	}

	readBuffer[0] = '\0';
	writeBuffer.Flush();
	writeBuffer.Clear();
	return true;
}

bool Jdata::fileRead(std::string fName) {

	std::string path = "C:\\json\\";

	path.append(fName);
	path.append(".json");

	bool fexist = FileUtils::sharedFileUtils()->isFileExist(path);

	if (fexist == true) {
		FILE* fp = fopen(path.c_str(), "rb+");

		if (!fp) {
			log("----fileRead failed");
			return false;
		}
		else {
			readBuffer[0] = '\0';
			writeBuffer.Flush();
			writeBuffer.Clear();

			FileReadStream inputStrm(fp, readBuffer, sizeof(readBuffer));
			fclose(fp);

			if (doc.Parse(readBuffer).HasParseError() == true) {
				return true;
			}
			else {
				return true;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

std::string Jdata::jjgetString(const char* keystr, std::string fName) {

	bool readflag = fileRead(fName);
	if (!readflag) {
		log("----jjgetString failed");
		return "";
	}
	else
	{
		return doc[keystr].GetString();
	}
}

void Jdata::jjsetString(std::string setstr, const char* keystr, std::string fName) {

	bool readflag = fileRead(fName);
	if (!readflag) {
		log("----jjsetString failed");
	}
	else
	{
		const char* cstr = setstr.c_str();
		doc[keystr].SetString(StringRef(cstr));
		writetoFile(fName);
	}
}

int Jdata::jjgetInt(const char* keystr, std::string fName) {

	bool readflag = fileRead(fName);
	if (!readflag) {
		log("----jjgetInt failed");
		return 2323;
	}
	else
	{
		return doc[keystr].GetInt();
	}
}

void Jdata::jjsetInt(int setint, const char* keystr, std::string fName) {

	bool readflag = fileRead(fName);
	if (!readflag) {
		log("----jjsetInt failed");
	}
	else
	{
		doc[keystr].SetInt(setint);
		writetoFile(fName);
	}
}

bool Jdata::jjgetBool(const char* keystr, std::string fName) {

	bool readflag = fileRead(fName);
	if (!readflag) {
		log("----jjgetBool failed");
		return NULL;
	}
	else
	{
		return doc[keystr].GetBool();
	}
}

void Jdata::jjsetBool(bool setbool, const char* keystr, std::string fName) {

	bool readflag = fileRead(fName);
	if (!readflag) {
		log("----jjsetBool failed");
	}
	else
	{
		doc[keystr].SetBool(setbool);
		writetoFile(fName);
	}
}

//�����.json�� ����Ʈ ���� �� bool�� �����ϴ� �Լ�
void Jdata::jjsetArray(const char* keystr, std::string fName, bool tf, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& userquest = testData["userquest"];

		rapidjson::Value& b = userquest[order][keystr];

		b.SetBool(tf);
	}
	else
	{
		CCASSERT(false, "----jjsetArray failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);

}

//�����.json�� ����Ʈ ���� �� bool�� ��ȯ�ϴ� �Լ�
bool Jdata::jjgetArray(const char* keystr, std::string fName, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& user = testData["userquest"];

		rapidjson::Value& b = user[order][keystr];//�̷� ������ ���۷����� Value&�� �����ؼ� ����մϴ�.

		return b.GetBool();
	}
	else
	{
		CCASSERT(false, "----jjgetArray failed");
	}
}

//�����.json�� ����Ʈ ���� �� int�� �����ϴ� �Լ�
void Jdata::jjsetQint(const char* keystr, std::string fName, int setint, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& userquest = testData["userquest"];

		rapidjson::Value& b = userquest[order][keystr];//�̷� ������ ���۷����� Value&�� �����ؼ� ����մϴ�.

		b.SetInt(setint);
	}
	else
	{
		CCASSERT(false, "----jjsetQint failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);

}

//�����.json�� ����Ʈ ���� �� int�� ��ȯ�ϴ� �Լ�
int Jdata::jjgetQint(const char* keystr, std::string fName, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& userquest = testData["userquest"];

		rapidjson::Value& b = userquest[order][keystr];//�̷� ������ ���۷����� Value&�� �����ؼ� ����մϴ�.

		return b.GetInt();
	}
	else
	{
		CCASSERT(false, "----jjgetQint failed");
	}
}

//�����.json�� ���� ���� �� int�� ��ȯ�ϴ� �Լ�
int Jdata::jjgetpArray(const char* keystr, std::string fName, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& userpotion = testData["userpotion"];

		rapidjson::Value& p = userpotion[order][keystr];//�̷� ������ ���۷����� Value&�� �����ؼ� ����մϴ�.
		return p.GetInt();
	}
	else
	{
		CCASSERT(false, "----jjgetpArray failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);

}

//�����.json�� ���� ���� �� int�� �����ϴ� �Լ�
void Jdata::jjsetpArray(const char* keystr, std::string fName, int setint, int order) {
	
	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();
	
	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& userpotion = testData["userpotion"];

		rapidjson::Value& p = userpotion[order][keystr];//�̷� ������ ���۷����� Value&�� �����ؼ� ����մϴ�.

		p.SetInt(setint);
	}
	else
	{
		CCASSERT(false, "----jjsetpArray failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);
}

//(�����/����/����).json�� ��� �迭�̵� int���� ������ �� �ִ� �Լ�
//�Ű������� (keystr-������ value��), (keyary-������ value�� ���� �迭�� �̸�)�� ����մϴ�.
//fName�� potion�̳� weapon���� �����ϸ� �ش� JSON������ ��� ������ �����մϴ�.
void Jdata::jjsetAry(const char* keystr, const char * keyary, std::string fName, int setint, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& ary = testData[keyary];

		rapidjson::Value& aryvalue = ary[order][keystr];

		aryvalue.SetInt(setint);
	}
	else
	{
		CCASSERT(false, "----jjsetAry failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);

}

//(�����/����/����).json�� ��� �迭�̵� int���� ��ȯ�� �� �ִ� �Լ�
//�Ű������� (keystr-������ value��), (keyary-������ value�� ���� �迭�� �̸�)�� ����մϴ�.
//fName�� potion�̳� weapon���� �����ϸ� �ش� JSON������ ��� ������ ��ȯ�մϴ�.
int Jdata::jjgetAry(const char* keystr, const char * keyary, std::string fName, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& ary = testData[keyary];

		rapidjson::Value& aryint = ary[order][keystr];

		return aryint.GetInt();
	}
	else
	{
		CCASSERT(false, "----jjgetAry failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);
}

//fName.json�� �����ϴ� �Լ�
void Jdata::jjAppend(std::string fName) {

	std::string path = "C:\\json\\";
	path.append(fName);
	path.append(".json");

	bool fexist = FileUtils::sharedFileUtils()->isFileExist(path);
	if (fexist == true) {}
	else {
		//fopen ������ �������� ���� ��� �ڵ� �����ϵ��� wb+ ������ �־����ϴ�.
		FILE* fp = fopen(path.c_str(), "wb+");

		if (!fp) {

		}
		else {
			Document initdoc;
			initdoc.SetObject();
			rapidjson::Document::AllocatorType& allocator = initdoc.GetAllocator();

			rapidjson::Value chaName;
			char buff[10];

			//string ���� �׽�Ʈ��
			//SizeType len2 = strlen(buff);

			int len = sprintf(buff, "%s", fName.c_str());
			chaName.SetString(buff, len, allocator);
			memset(buff, 0, sizeof(buff));

			initdoc.AddMember("name", chaName, allocator);

			//default string Value
			//initdoc.AddMember("name", " ", allocator);
			//default int Value
			//rapidjson::Value val(0);

			rapidjson::Value val;
			val.SetInt(0);
			initdoc.AddMember("stat", val, allocator);
			val.SetInt(100);
			initdoc.AddMember("atk", val, allocator);
			val.SetInt(10);
			initdoc.AddMember("atkst", val, allocator);
			val.SetInt(1);
			initdoc.AddMember("class", val, allocator);
			val.SetInt(10);
			initdoc.AddMember("cri", val, allocator);
			val.SetInt(150);
			initdoc.AddMember("cridam", val, allocator);
			val.SetInt(100);
			initdoc.AddMember("def", val, allocator);
			val.SetInt(10);
			initdoc.AddMember("defst", val, allocator);
			val.SetInt(0);
			initdoc.AddMember("exp", val, allocator);
			val.SetInt(1300);
			initdoc.AddMember("hp", val, allocator);
			val.SetInt(1);
			initdoc.AddMember("level", val, allocator);
			val.SetInt(1000);
			initdoc.AddMember("maxexp", val, allocator);
			val.SetInt(1300);
			initdoc.AddMember("maxhp", val, allocator);
			val.SetInt(1000);
			initdoc.AddMember("maxmp", val, allocator);
			val.SetInt(0);
			initdoc.AddMember("money", val, allocator);
			val.SetInt(1000);
			initdoc.AddMember("mp", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("skill1", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("skill2", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("skill3", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("skill4", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("wweapon", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("wshirts", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("wpants", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("wac1", val, allocator);
			val.SetInt(999);
			initdoc.AddMember("wac2", val, allocator);

			rapidjson::Value boolval;
			boolval.SetBool(false);
			initdoc.AddMember("pro", boolval, allocator);

			rapidjson::Value userquest(kArrayType);//������� quest ����� �迭�� ����

			rapidjson::Value uquest0;
			uquest0.SetObject();
			uquest0.AddMember("read", false, allocator);//quest read ����
			uquest0.AddMember("done", false, allocator);//quest ���࿩��
			uquest0.AddMember("condition", 1, allocator);//����Ʈ ���� 
			uquest0.AddMember("nowing", 0, allocator);//����Ʈ ���� 
			uquest0.AddMember("rwrdcash", 1500, allocator);//rewardcash �����
			uquest0.AddMember("rwrdExp", 380, allocator);//rewardExp ����ġ����
			uquest0.AddMember("rwrdhp", 0, allocator);//rewardhp hp����(����)

			userquest.PushBack(uquest0, allocator);

			rapidjson::Value uquest1;
			uquest1.SetObject();
			uquest1.AddMember("read", false, allocator);//quest read ����
			uquest1.AddMember("done", false, allocator);//quest ���࿩��
			uquest1.AddMember("condition", 1, allocator);//����Ʈ ���� 
			uquest1.AddMember("nowing", 0, allocator);//����Ʈ ���� 
			uquest1.AddMember("rwrdcash", 1000, allocator);//rewardcash �����
			uquest1.AddMember("rwrdExp", 450, allocator);//rewardExp ����ġ����
			uquest1.AddMember("rwrdhp", 0, allocator);//rewardhp hp����(����)

			userquest.PushBack(uquest1, allocator);

			rapidjson::Value uquest2;
			uquest2.SetObject();
			uquest2.AddMember("read", false, allocator);//quest read ����
			uquest2.AddMember("done", false, allocator);//quest ���࿩��
			uquest2.AddMember("condition", 5, allocator);//����Ʈ ���� 
			uquest2.AddMember("nowing", 0, allocator);//����Ʈ ���� 
			uquest2.AddMember("rwrdcash", 2000, allocator);//rewardcash �����
			uquest2.AddMember("rwrdExp", 500, allocator);//rewardExp ����ġ����
			uquest2.AddMember("rwrdhp", 5, allocator);//rewardhp hp����(����)

			userquest.PushBack(uquest2, allocator);

			rapidjson::Value uquest3;
			uquest3.SetObject();
			uquest3.AddMember("read", false, allocator);//quest read ����
			uquest3.AddMember("done", false, allocator);//quest ���࿩��
			uquest3.AddMember("condition", 1, allocator);//����Ʈ ���� 
			uquest3.AddMember("nowing", 0, allocator);//����Ʈ ���� 
			uquest3.AddMember("rwrdcash", 1000, allocator);//rewardcash �����
			uquest3.AddMember("rwrdExp", 300, allocator);//rewardExp ����ġ����
			uquest3.AddMember("rwrdhp", 5, allocator);//rewardhp hp����(����)

			userquest.PushBack(uquest3, allocator);

			rapidjson::Value uquest4;

			uquest4.SetObject();
			uquest4.AddMember("read", false, allocator);//quest read ����
			uquest4.AddMember("done", false, allocator);//quest ���࿩��
			uquest4.AddMember("condition", 1, allocator);//����Ʈ ���� 
			uquest4.AddMember("nowing", 0, allocator);//����Ʈ ���� 
			uquest4.AddMember("rwrdcash", 6000, allocator);//rewardcash �����
			uquest4.AddMember("rwrdExp", 500, allocator);//rewardExp ����ġ����
			uquest4.AddMember("rwrdhp", 5, allocator);//rewardhp hp����(����)

			userquest.PushBack(uquest4, allocator);

			rapidjson::Value useritem(kArrayType);

			rapidjson::Value uitem0;

			uitem0.SetObject();
			uitem0.AddMember("keyid", 999, allocator);
			uitem0.AddMember("holding", 0, allocator);

			useritem.PushBack(uitem0, allocator);

			rapidjson::Value uitem1;

			uitem1.SetObject();
			uitem1.AddMember("keyid", 999, allocator);
			uitem1.AddMember("holding", 0, allocator);

			useritem.PushBack(uitem1, allocator);

			rapidjson::Value uitem2;

			uitem2.SetObject();
			uitem2.AddMember("keyid", 999, allocator);
			uitem2.AddMember("holding", 0, allocator);

			useritem.PushBack(uitem2, allocator);

			rapidjson::Value uitem3;

			uitem3.SetObject();
			uitem3.AddMember("keyid", 999, allocator);
			uitem3.AddMember("holding", 0, allocator);

			useritem.PushBack(uitem3, allocator);

			rapidjson::Value userpotion(kArrayType);

			rapidjson::Value upotion0;

			upotion0.SetObject();
			upotion0.AddMember("keyid", 999, allocator);
			upotion0.AddMember("holding", 0, allocator);
			upotion0.AddMember("efft", 0, allocator);

			userpotion.PushBack(upotion0, allocator);

			rapidjson::Value upotion1;

			upotion1.SetObject();
			upotion1.AddMember("keyid", 999, allocator);
			upotion1.AddMember("holding", 0, allocator);
			upotion1.AddMember("efft", 0, allocator);


			userpotion.PushBack(upotion1, allocator);

			rapidjson::Value upotion2;

			upotion2.SetObject();
			upotion2.AddMember("keyid", 999, allocator);
			upotion2.AddMember("holding", 0, allocator);
			upotion2.AddMember("efft", 0, allocator);

			userpotion.PushBack(upotion2, allocator);

			rapidjson::Value upotion3;

			upotion3.SetObject();
			upotion3.AddMember("keyid", 999, allocator);
			upotion3.AddMember("holding", 0, allocator);
			upotion3.AddMember("efft", 0, allocator);

			userpotion.PushBack(upotion3, allocator);

			rapidjson::Value userweapon(kArrayType);

			rapidjson::Value uweapon0;

			uweapon0.SetObject();
			uweapon0.AddMember("keyid", 999, allocator);
			uweapon0.AddMember("holding", 0, allocator);

			userweapon.PushBack(uweapon0, allocator);

			rapidjson::Value uweapon1;

			uweapon1.SetObject();
			uweapon1.AddMember("keyid", 999, allocator);
			uweapon1.AddMember("holding", 0, allocator);

			userweapon.PushBack(uweapon1, allocator);

			rapidjson::Value uweapon2;

			uweapon2.SetObject();
			uweapon2.AddMember("keyid", 999, allocator);
			uweapon2.AddMember("holding", 0, allocator);

			userweapon.PushBack(uweapon2, allocator);

			rapidjson::Value uweapon3;

			uweapon3.SetObject();
			uweapon3.AddMember("keyid", 999, allocator);
			uweapon3.AddMember("holding", 0, allocator);

			userweapon.PushBack(uweapon3, allocator);

			initdoc.AddMember("userquest", userquest, allocator);
			initdoc.AddMember("userpotion", userpotion, allocator);
			initdoc.AddMember("userweapon", userweapon, allocator);
			initdoc.AddMember("useritem", useritem, allocator);

			StringBuffer buffer;
			Writer<StringBuffer> writer(buffer);
			initdoc.Accept(writer);

			const char* schar = buffer.GetString();

			fputs(schar, fp);
			fclose(fp);
		}
	}
}

//�Ƹ��� �Ⱦ��� �Լ�
std::string Jdata::jjgetuserName(int tag) {

	bool readflag = fileRead("name");
	if (!readflag) {
		log("----jjgetuserName failed");
		return NULL;
	}
	else
	{
		return doc["name"][tag].GetString();
	}
}

void Jdata::jjnameAppend(std::string ChaName) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append("name.json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& plyrlist = testData["name"];

		rapidjson::Document::AllocatorType& challocator = testData.GetAllocator();

		rapidjson::Value chaName;
		char buff[10];

		int len = sprintf(buff, "%s", ChaName.c_str());
		chaName.SetString(buff, len, challocator);
		memset(buff, 0, sizeof(buff));
		bool pexist = false;

		assert(plyrlist.IsArray());
		SizeType i = 0;
		for (i = 0; i < plyrlist.Size(); i++) {
			if (plyrlist[i].GetString() == ChaName) {
				pexist = true;
			}
		}

		if (pexist == false) {
			plyrlist.PushBack(chaName, challocator);
		}
	}
	else
	{
		CCASSERT(false, "----jjnameAppend failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);

}

//name.json�� �����ϴ� �Լ�
void Jdata::jjnamelist() {

	std::string path = "C:\\json\\";
	path.append("name.json");

	bool fexist = FileUtils::sharedFileUtils()->isFileExist(path);

	if (fexist == true) {
	}
	else {

		FILE* fp = fopen(path.c_str(), "wb+");

		if (!fp) {
		}
		else {

			Document userdoc;
			userdoc.SetObject();
			rapidjson::Document::AllocatorType& ualloca = userdoc.GetAllocator();
			rapidjson::Value plyrdata(kArrayType);
			userdoc.AddMember("name", plyrdata, ualloca);

			StringBuffer buffer;
			Writer<StringBuffer> writer(buffer);
			userdoc.Accept(writer);
			const char* schar = buffer.GetString();

			fputs(schar, fp);
			fclose(fp);
		}
	}
}

void Jdata::jjnamedelete(std::string name) {

	log("In Name delete");
	rapidjson::Document tData;

	std::string fpath = "C:\\json\\";

	fpath.append("name.json");

	Data data2 = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size2 = data2.getSize();
	
	char* jsonBuffer2 = new char[size2 + 1];
	memcpy(jsonBuffer2, data2.getBytes(), size2);
	jsonBuffer2[size2] = '\0';
	data2.clear();
	
	if (tData.ParseInsitu<0>(jsonBuffer2).HasParseError() == true)
	{
		log("----jjnamedelete");
	}
	else {
		log("----jjnamedelete2");
		rapidjson::Value& plyrlist = tData["name"];

		rapidjson::Document::AllocatorType& challocator = tData.GetAllocator();

		assert(plyrlist.IsArray());
		
		SizeType i = 0;
		//for (i = 0; i < plyrlist.Size(); i++) {
			//if (plyrlist[i].GetString() == name.c_str()) {
				plyrlist.PopBack();
				log("in");
			//}
		//}
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	tData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);
}

//���� ������� �ʴ� �Լ�
void Jdata::jjplyrlist(std::string fName) {

	//std::string path = "C:\\cocos2d-x-3.11.1\\tools\\cocos2d-console\\bin\\test\\Resources\\res\\";
	std::string path = "C:\\json\\";
	
	path.append(fName);
	path.append("name.json");
	//log("path: %s", path.c_str());

	FILE* fp = fopen(path.c_str(), "wb+");

	if (!fp) {
		//log("cannot create file: %s", path);
	}
	else {
		//log("JSON Append Test");

		Document ddoc;
		ddoc.SetObject();
		rapidjson::Document::AllocatorType& allocator = ddoc.GetAllocator();

		rapidjson::Value userdata(kArrayType);
		/*
		rapidjson::Value userlist0;

		char buff[10];
		buff[0] = '\0';
		int len = sprintf(buff, "%s", fName.c_str());
		userlist0.SetString(buff, len, allocator);
		memset(buff, 0, sizeof(buff));

		userdata.PushBack(userlist0, allocator);

		rapidjson::Value userlist1;

		len = sprintf(buff, "%s", "yoonmin");
		userlist1.SetString(buff, len, allocator);
		memset(buff, 0, sizeof(buff));

		userdata.PushBack(userlist1, allocator);
		*/
		ddoc.AddMember("name", userdata, allocator);

		rapidjson::Value hasCharacter;

		StringBuffer buffer;

		Writer<StringBuffer> writer(buffer);
		ddoc.Accept(writer);


		const char* schar = buffer.GetString();

		//log("Create JSON file success: %s", path.c_str());
		//log("data: %s", schar);

		fputs(schar, fp);
		fclose(fp);
	}
}

void Jdata::jjPotionAppend() {

	std::string path = "C:\\json\\";

	path.append("potion.json");

	FILE* fp = fopen(path.c_str(), "wb+");

	if (!fp) {
		log("----jjPotionAppend failed");
	}
	else {

		Document potiondoc;
		potiondoc.SetObject();
		rapidjson::Document::AllocatorType& allocator = potiondoc.GetAllocator();

		rapidjson::Value potion(kArrayType);

		rapidjson::Value hp;
		hp.SetObject();
		hp.AddMember("shoppng", "store_hp(s).png", allocator);
		hp.AddMember("png", "hppotion.png", allocator);
		hp.AddMember("pngname", "store_hp(s).png", allocator);
		hp.AddMember("effect", 100, allocator);
		hp.AddMember("money", 1000, allocator);
		hp.AddMember("keyid", 0, allocator);
		hp.AddMember("infoimg", "hpinfo.png", allocator);
		hp.AddMember("infostr", "red effect 100 money 1000", allocator);

		potion.PushBack(hp, allocator);

		rapidjson::Value mp;
		mp.SetObject();
		mp.AddMember("shoppng", "store_mp(s).png", allocator);
		mp.AddMember("png", "mppotion.png", allocator);
		mp.AddMember("pngname", "store_mp(s).png", allocator);
		mp.AddMember("effect", 100, allocator);
		mp.AddMember("money", 1100, allocator);
		mp.AddMember("keyid", 1, allocator);
		mp.AddMember("infoimg", "mpinfo.png", allocator);
		mp.AddMember("infostr", "blue effect 100 money 1100", allocator);

		potion.PushBack(mp, allocator);

		potiondoc.AddMember("potion", potion, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		potiondoc.Accept(writer);

		const char* schar = buffer.GetString();

		fputs(schar, fp);
		fclose(fp);
	}
}

void Jdata::jjWeaponAppend() {

	std::string path = "C:\\json\\";

	path.append("weapon.json");

	FILE* fp = fopen(path.c_str(), "wb+");

	if (!fp) {
		log("----jjWeaponAppend failed");
	}
	else {

		Document weapondoc;
		weapondoc.SetObject();
		rapidjson::Document::AllocatorType& allocator = weapondoc.GetAllocator();

		rapidjson::Value weapon(kArrayType);

		rapidjson::Value wp0;
		wp0.SetObject();
		wp0.AddMember("shoppng", "store_wp1.png", allocator);
		wp0.AddMember("pngname", "wp1.png", allocator);
		wp0.AddMember("effect", 10, allocator);//�������� �� ���ݷ�
		wp0.AddMember("money", 3000, allocator);
		wp0.AddMember("keyid", 0, allocator);
		wp0.AddMember("infoimg", "wp1info.png", allocator);//�̹����� �����Ƿ� �����̹����� ��ü

		weapon.PushBack(wp0, allocator);

		rapidjson::Value wp1;
		wp1.SetObject();
		wp1.AddMember("shoppng", "store_shirts1.png", allocator);
		wp1.AddMember("pngname", "shirts1.png", allocator);
		wp1.AddMember("effect", 5, allocator);//�������� �� ���ݷ�
		wp1.AddMember("money", 2500, allocator);
		wp1.AddMember("keyid", 1, allocator);
		wp1.AddMember("infoimg", "sh1info.png", allocator);//�̹����� �����Ƿ� �����̹����� ��ü

		weapon.PushBack(wp1, allocator);

		rapidjson::Value wp2;
		wp2.SetObject();
		wp2.AddMember("shoppng", "store_pants1.png", allocator);
		wp2.AddMember("pngname", "pants1.png", allocator);
		wp2.AddMember("effect", 3, allocator);//�������� �� ���ݷ�
		wp2.AddMember("money", 2300, allocator);
		wp2.AddMember("keyid", 2, allocator);
		wp2.AddMember("infoimg", "pa1info.png", allocator);//�̹����� �����Ƿ� �����̹����� ��ü

		weapon.PushBack(wp2, allocator);

		weapondoc.AddMember("weapon", weapon, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		weapondoc.Accept(writer);

		const char* schar = buffer.GetString();

		fputs(schar, fp);
		fclose(fp);
	}
}

void Jdata::jjItemAppend() {

	std::string path = "C:\\json\\";

	path.append("item.json");

	FILE* fp = fopen(path.c_str(), "wb+");

	if (!fp) {
		log("----jjItemAppend failed");
	}
	else {

		Document itemdoc;
		itemdoc.SetObject();
		rapidjson::Document::AllocatorType& allocator = itemdoc.GetAllocator();

		rapidjson::Value item(kArrayType);

		rapidjson::Value item0;
		item0.SetObject();
		item0.AddMember("png", "steel.png", allocator);
		item0.AddMember("name", "steel", allocator);
		item0.AddMember("sellmoney", 500, allocator);
		item0.AddMember("keyid", 0, allocator);

		item.PushBack(item0, allocator);

		itemdoc.AddMember("item", item, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		itemdoc.Accept(writer);

		const char* schar = buffer.GetString();

		fputs(schar, fp);
		fclose(fp);
	}
}

void Jdata::jjSkillAppend() {

	std::string path = "C:\\json\\";

	path.append("skill.json");

	FILE* fp = fopen(path.c_str(), "wb+");

	if (!fp) {
		log("----jjSkillAppend failed");
	}
	else {

		Document skilldoc;
		skilldoc.SetObject();
		rapidjson::Document::AllocatorType& allocator = skilldoc.GetAllocator();

		rapidjson::Value skill(kArrayType);

		rapidjson::Value skill0;
		skill0.SetObject();
		skill0.AddMember("png", "skill1_img.png", allocator);
		skill0.AddMember("motion", "skill1_eff.png", allocator);
		skill0.AddMember("effect", 130, allocator);
		skill0.AddMember("skillmp", 80, allocator);
		skill0.AddMember("cooltime", 15, allocator);
		skill0.AddMember("hit", 6, allocator);
		skill0.AddMember("keyid", 0, allocator);

		skill.PushBack(skill0, allocator);

		skilldoc.AddMember("skill", skill, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		skilldoc.Accept(writer);

		const char* schar = buffer.GetString();

		fputs(schar, fp);
		fclose(fp);
	}
}

void Jdata::writetoFile(std::string fName) {

	std::string path = "C:\\json\\";

	path.append(fName);
	path.append(".json");

	FILE* fp = fopen(path.c_str(), "wb");

	if (!fp) {
		log("writetoFile failed");
	}
	else
	{
		Writer<StringBuffer> writer(writeBuffer);
		doc.Accept(writer);

		std::string fData = writeBuffer.GetString();
		const char* schar = fData.c_str();

		fputs(fData.c_str(), fp);
		fclose(fp);
	}
}

void Jdata::jjplyrdelete(std::string fName) {
	
	std::string path = "C:\\json\\";

	path.append(fName);
	path.append(".json");

	bool fexist = FileUtils::sharedFileUtils()->isFileExist(path);
	if (fexist == true) {
		bool rm = FileUtils::sharedFileUtils()->removeFile(path);
		if (rm == true) {
			log("----jjplyrdelete remove done");
		}
		else {
			log("----jjplyrdelete remove fail");
		}
	}
	else {
		log("----jjplyrdelete no file: %s", path.c_str());
	}
}

std::string Jdata::jjgetSAry(const char* keystr, const char * keyary, std::string fName, int order) {

	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{

		rapidjson::Value& uvalue = testData[keyary];

		rapidjson::Value& getval = uvalue[order][keystr];//�̷� ������ ���۷����� Value&�� �����ؼ� ����մϴ�.

		return getval.GetString();
	}
	else
	{
		CCASSERT(false, "----jjgetSAry failed");
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);
}

int Jdata::jjgetArySize(const char* keystr, std::string fName) {
	rapidjson::Document testData;

	std::string fpath = "C:\\json\\";

	fpath.append(fName);
	fpath.append(".json");

	Data data = FileUtils::getInstance()->getDataFromFile(fpath);
	ssize_t size = data.getSize();

	char* jsonBuffer = new char[size + 1];
	memcpy(jsonBuffer, data.getBytes(), size);
	jsonBuffer[size] = '\0';
	data.clear();

	if (testData.ParseInsitu<0>(jsonBuffer).HasParseError() == false)
	{
		rapidjson::Value& userary = testData[keystr];
		SizeType arySize = userary.Size();
		int size = arySize;
		return size;
	}
	else
	{
		CCASSERT(false, "----jjgetArySize failed");
		return NULL;
	}
	FILE* fpointer = fopen(fpath.c_str(), "wb+");

	StringBuffer b;
	Writer<StringBuffer> writer(b);
	testData.Accept(writer);

	std::string fData = b.GetString();
	const char* schar = fData.c_str();

	fputs(fData.c_str(), fpointer);
	fclose(fpointer);
}