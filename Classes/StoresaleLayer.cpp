#include "StoresaleLayer.h"

Scene* StoresaleLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = StoresaleLayer::create();

	scene->addChild(layer);

	return scene;
}

bool StoresaleLayer::init() {//�⺻ ȭ�� ����


	if (!Layer::init()) {
		return false;
	}
	std::string sale_uname1 = dataSingleton::getInstance()->user;
	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background);



	//���� ������ ������ â ����
	item_win1 = Sprite::create("sale_win1.png");
	item_win1->setAnchorPoint(Point(1, 0.5));
	item_win1->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 - 10, Director::getInstance()->
		getWinSize().height / 2));
	item_win1->setTag(ITEMW1);
	this->addChild(item_win1);

	auto wear_but = MenuItemImage::create("wearbut.png", "wearbut.png", CC_CALLBACK_1(StoresaleLayer::itemmenu, this));
	wear_but->setTag(wearb);
	auto wear = Menu::create(wear_but, NULL);
	wear->setAnchorPoint(Point(0.5, 0.5));
	wear->setPosition(Point(170, 870));
	item_win1->addChild(wear);

	auto consume_but = MenuItemImage::create("consumbut.png", "consumbut.png", CC_CALLBACK_1(StoresaleLayer::itemmenu, this));
	consume_but->setTag(consumeb);
	auto consume = Menu::create(consume_but, NULL);
	consume->setAnchorPoint(Point(0.5, 0.5));
	consume->setPosition(Point(420, 870));
	item_win1->addChild(consume);

	itembox1 = Sprite::create("itembox.png");
	itembox1->setPosition(Point(140, 720));
	item_win1->addChild(itembox1);

	itembox2 = Sprite::create("itembox.png");
	itembox2->setPosition(Point(290, 720));
	item_win1->addChild(itembox2);

	itembox3 = Sprite::create("itembox.png");
	itembox3->setPosition(Point(440, 720));
	item_win1->addChild(itembox3);

	itembox4 = Sprite::create("itembox.png");
	itembox4->setPosition(Point(590, 720));
	item_win1->addChild(itembox4);

	//������ ������ �Ǹ�â ����
	item_win2 = Sprite::create("sale_win2.png");
	item_win2->setAnchorPoint(Point(0, 0.5));
	item_win2->setPosition(Point(Director::getInstance()->
		getWinSize().width / 2 + 10, Director::getInstance()->
		getWinSize().height / 2));
	item_win2->setTag(ITEMW2);
	this->addChild(item_win2);

	

	listview = ListView::create();
	listview->setDirection(ui::ScrollView::Direction::VERTICAL);
	listview->setTouchEnabled(true);
	listview->setBounceEnabled(true);
	listview->setBackGroundColor(Color3B::YELLOW);
	listview->setSize(Size(700, 400));
	listview->ignoreContentAdaptWithSize(false);
	listview->setPosition(Vec2(0, 450));
	item_win2->addChild(listview);


	totallb = Label::createWithTTF("0", "nanumgo.ttf", 60);
	totallb->setAnchorPoint(Point(0.5, 0.5));
	totallb->setPosition(Point(400, 200));
	totallb->setColor(Color3B::YELLOW);
	totallb->setTag(TOTAL);
	item_win2->addChild(totallb);

	int uMoney = pSale->jjgetInt("money", sale_uname1);
	posslb = Label::createWithTTF(std::to_string(uMoney), "nanumgo.ttf", 60);
	posslb->setAnchorPoint(Point(0.5, 0.5));
	posslb->setPosition(Point(400, 280));
	posslb->setColor(Color3B::YELLOW);
	posslb->setTag(POSSES);
	item_win2->addChild(posslb);

	auto sale = MenuItemImage::create("sale.png", "sale.png", CC_CALLBACK_1(StoresaleLayer::sale, this));
	auto salemenu = Menu::create(sale, NULL);
	salemenu->setAnchorPoint(Point(0.5, 0.5));
	salemenu->setPosition(Point(150, 100));
	item_win2->addChild(salemenu);

	auto salec = MenuItemImage::create("salecancel.png", "salecancel.png", CC_CALLBACK_1(StoresaleLayer::salecancel, this));
	auto salecancel = Menu::create(salec, NULL);
	salecancel->setAnchorPoint(Point(0.5, 0.5));
	salecancel->setPosition(Point(400, 100));
	item_win2->addChild(salecancel);

	auto exit = MenuItemImage::create("exit.png", "exit_push.png", CC_CALLBACK_1(StoresaleLayer::menuclose, this));
	auto exitmenu = Menu::create(exit, NULL);
	exitmenu->setTag(EXIT);
	exitmenu->setPosition(Point(1665, 1002));
	this->addChild(exitmenu);

	showW1();

	return true;
}

void StoresaleLayer::menuclose(Ref *sender) {
	this->removeAllChildrenWithCleanup(true);
}

void StoresaleLayer::itemmenu(Ref* sender) {
	auto buttag = (MenuItem*)sender;

	switch (buttag->getTag()) {
	case wearb: {
	
		showW1();
		break;
	}
	case consumeb: {
	
		showW2();
		break;
	}
	default: {
		//���߿� init����η� �̵�
		//keyStr = "weapon";
		//keyStr2 = "userweapon";
		//dataSingleton::getInstance()->keystr = keyStr2;
		break;
	}

	}
}

void StoresaleLayer::showW1() {

	keyStr = "weapon";
	keyStr2 = "userweapon";
	dataSingleton::getInstance()->keystr = keyStr2;

	std::string sale_uname2 = dataSingleton::getInstance()->user;
	itembox1->removeAllChildren();
	itembox2->removeAllChildren();
	itembox3->removeAllChildren();
	itembox4->removeAllChildren();
	sell = 0;
	//������ �ִ� ��� �迭�� ������ ���� �ϰ� �迭 ������� ��ġ�ϰ� �Ѵ�.
	//���������� �迭 ���� ��ġ�� ������ ���ִ��� �ƴ��� �˾ƾ� �ҵ�
	//�ΰ��� �ƴ϶�� ��ġ�ϵ��� �Ѵ�.
	//������ �ִ� �������� Ű���̵��
	//���� ���̽��� �ִ� ������� Ű���̵� ã�ƿ� �� Ű���̵��� �̹����� ȿ���� ���������� �Ѵ�.
	//weapon.json���� �������� keyid�� �� �迭�� ��ġ�� ��Ÿ��

	id1 = pSale->jjgetAry("keyid", "userweapon", sale_uname2, 0);//������ ���迭���� ������
	if (id1 != 999) {//999�� �������� ���ٴ� ��

		auto wp1file1 = pSale->jjgetSAry("pngname", "weapon", "weapon", id1);
		auto item1 = MenuItemImage::create(wp1file1, wp1file1, CC_CALLBACK_1(StoresaleLayer::openinterface, this));
		item1->setTag(BOX1);
		auto item1b = Menu::create(item1, NULL);

		item1b->setPosition(65, 65);
		itembox1->addChild(item1b);

		auto hold1 = pSale->jjgetAry("holding", "userweapon", sale_uname2, 0);
		std::string holding1 = std::to_string(hold1);
		hLabel1 = Label::createWithTTF(holding1, "nanumgo.ttf", 20);
		hLabel1->setPosition(Point(110, 20));
		itembox1->addChild(hLabel1);
	}


	id2 = pSale->jjgetAry("keyid", "userweapon", sale_uname2, 1);//������ ���迭���� ������
	if (id2 != 999) {//999�� �������� ���ٴ� ��

		auto wp2file2 = pSale->jjgetSAry("pngname", "weapon", "weapon", id2);
		auto item2 = MenuItemImage::create(wp2file2, wp2file2, CC_CALLBACK_1(StoresaleLayer::openinterface, this));
		item2->setTag(BOX2);
		auto item2b = Menu::create(item2, NULL);
		item2b->setPosition(65, 65);
		itembox2->addChild(item2b);

		auto hold2 = pSale->jjgetAry("holding", "userweapon", sale_uname2, 1);
		std::string holding2 = std::to_string(hold2);
		hLabel2 = Label::createWithTTF(holding2, "nanumgo.ttf", 20);
		hLabel2->setPosition(Point(110, 20));
		itembox2->addChild(hLabel2);
	}
	id3 = pSale->jjgetAry("keyid", "userweapon", sale_uname2, 2);//������ ���迭���� ������
	if (id3 != 999) {//999�� �������� ���ٴ� ��

		auto wp3file3 = pSale->jjgetSAry("pngname", "weapon", "weapon", id3);
		auto item3 = MenuItemImage::create(wp3file3, wp3file3, CC_CALLBACK_1(StoresaleLayer::openinterface, this));
		item3->setTag(BOX3);
		auto item3b = Menu::create(item3, NULL);
		item3b->setPosition(65, 65);
		itembox3->addChild(item3b);

		auto hold3 = pSale->jjgetAry("holding", "userweapon", sale_uname2, 2);
		std::string holding3 = std::to_string(hold3);
		hLabel3 = Label::createWithTTF(holding3, "nanumgo.ttf", 20);
		hLabel3->setPosition(Point(110, 20));
		itembox3->addChild(hLabel3);
	}
	id4 = pSale->jjgetAry("keyid", "userweapon", sale_uname2, 3);//������ ���迭���� ������
	if (id4 != 999) {//999�� �������� ���ٴ� ��

		auto wp4file4 = pSale->jjgetSAry("pngname", "weapon", "weapon", id4);
		auto item4 = MenuItemImage::create(wp4file4, wp4file4, CC_CALLBACK_1(StoresaleLayer::openinterface, this));
		item4->setTag(BOX4);
		auto item4b = Menu::create(item4, NULL);
		item4b->setPosition(65, 65);
		itembox4->addChild(item4b);

		auto hold4 = pSale->jjgetAry("holding", "userweapon", sale_uname2, 3);
		std::string holding4 = std::to_string(hold4);
		hLabel4 = Label::createWithTTF(holding4, "nanumgo.ttf", 20);
		hLabel4->setPosition(Point(110, 20));
		itembox4->addChild(hLabel4);

	}
}

void StoresaleLayer::showW2() {

	keyStr = "potion";
	keyStr2 = "userpotion";
	dataSingleton::getInstance()->keystr = keyStr2;
	std::string sale_uname3 = dataSingleton::getInstance()->user;
	itembox1->removeAllChildren();
	itembox2->removeAllChildren();
	itembox3->removeAllChildren();
	itembox4->removeAllChildren();
	sell = 1;
	//������ �ִ� ���� �迭�� ������ ���� �ϰ� �迭 ������� ��ġ�ϰ� �Ѵ�.
	//���������� �迭 ���� ��ġ�� ������ ���ִ��� �ƴ��� �˾ƾ� �ҵ�
	//�ΰ��� �ƴ϶�� ��ġ�ϵ��� �Ѵ�.
	//������ �ִ� �������� Ű���̵��
	//���� ���̽��� �ִ� ���ǵ��� Ű���̵� ã�ƿ� �� Ű���̵��� �̹����� ȿ���� ���������� �Ѵ�.
	//potion.json���� �������� keyid�� �� �迭�� ��ġ�� ��Ÿ��

	id5 = pSale->jjgetAry("keyid", "userpotion", sale_uname3, 0);//������ ���ǹ迭���� ������
	if (id5 != 999) {//999�� �������� ���ٴ� ��

		auto hpfile = pSale->jjgetSAry("png", "potion", "potion", id5);
		auto item1 = MenuItemImage::create(hpfile, hpfile, CC_CALLBACK_1(StoresaleLayer::openinterface, this));
		item1->setTag(BOX5);
		auto item1b = Menu::create(item1, NULL);

		item1b->setPosition(65, 65);
		itembox1->addChild(item1b);

		auto hold1 = pSale->jjgetAry("holding", "userpotion", sale_uname3, 0);
		std::string holding1 = std::to_string(hold1);
		hLabel1 = Label::createWithTTF(holding1, "nanumgo.ttf", 20);
		hLabel1->setPosition(Point(110, 20));
		itembox1->addChild(hLabel1);
	}


	id6 = pSale->jjgetAry("keyid", "userpotion", sale_uname3, 1);//������ ���迭���� ������
	if (id6 != 999) {//999�� �������� ���ٴ� ��

		auto mpfile = pSale->jjgetSAry("png", "potion", "potion", id6);
		auto item2 = MenuItemImage::create(mpfile, mpfile, CC_CALLBACK_1(StoresaleLayer::openinterface, this));
		item2->setTag(BOX6);
		auto item2b = Menu::create(item2, NULL);
		item2b->setPosition(65, 65);
		itembox2->addChild(item2b);

		auto hold2 = pSale->jjgetAry("holding", "userpotion", sale_uname3, 1);
		std::string holding2 = std::to_string(hold2);
		hLabel2 = Label::createWithTTF(holding2, "nanumgo.ttf", 20);
		hLabel2->setPosition(Point(110, 20));
		itembox2->addChild(hLabel2);
	}

}

void StoresaleLayer::openinterface(cocos2d::Ref* sender) {

	auto btntag = (MenuItem*)sender;

	switch (btntag->getTag()) {
	case BOX1: {
		keyId = id1;
		user_keyId = 0;
		dataSingleton::getInstance()->aryIndex = user_keyId;
		break;
	}
	case BOX2: {
		keyId = id2;
		user_keyId = 1;
		dataSingleton::getInstance()->aryIndex = user_keyId;
		break;
	}
	case BOX3: {
		keyId = id3;
		user_keyId = 2;
		dataSingleton::getInstance()->aryIndex = user_keyId;
		break;
	}

	case BOX4: {
		keyId = id4;
		user_keyId = 0;
		dataSingleton::getInstance()->aryIndex = user_keyId;
		break;
	}

	case BOX5: {
		keyId = id5;
		user_keyId = 0;
		dataSingleton::getInstance()->aryIndex = user_keyId;
		break;
	}

	case BOX6: {
		keyId = id6;
		user_keyId = 1;
		dataSingleton::getInstance()->aryIndex = user_keyId;
		break;
	}
	default: {
		break;
	}

	}

	//�Լ��� ����� �ͺ��� ���� ������ ������ ���̾ ����
	//�������̽��� ���� ������ �Է� ����
	//calLayer�� ���� �����ϰ� �ڵ� ������
	auto calLayer = CalculateInterface::create();
	this->addChild(calLayer);
}

void StoresaleLayer::movetoList() {
	std::string sale_uname4 = dataSingleton::getInstance()->user;
	//���õ� �������� keyid�� ����
	int item_qty = dataSingleton::getInstance()->cal_qty;

	//sale_qty�� 0�̸�, �����Է��� ������ ��Ÿ��
	//calLayer���� �Է� ����� ���ϸ� ȭ�鿡�� calLayer�� ������� ����
	if (item_qty != 0) {
		const char* item_str = keyStr.c_str();
	
		int item_price = pSale->jjgetAry("money", item_str, item_str, keyId);
		item_price *= item_qty;

		std::string item_img = pSale->jjgetSAry("shoppng", item_str, item_str, keyId);
		ui::Button *item_btn = Button::create(item_img, item_img);
		item_btn->setScale(0.8);
		item_btn->setTag(keyId);

		//���� ��
		auto qty_label = Label::createWithTTF(std::to_string(item_qty), "nanumgo.ttf", 50);
		qty_label->setAnchorPoint(Point(0.5, 0.5));
		qty_label->setPosition(Point(450, 50));
		qty_label->setColor(Color3B::YELLOW);
		qty_label->setTag(item_qty);
		item_btn->addChild(qty_label, 1, "qty");

		//�ݾ� ��
		auto price_label = Label::createWithTTF(std::to_string(item_price), "nanumgo.ttf", 50);
		price_label->setAnchorPoint(Point(0.5, 0.5));
		price_label->setPosition(Point(650, 50));
		price_label->setColor(Color3B::YELLOW);
		item_btn->addChild(price_label, 2, "price");

		//����Ʈ �信 ������ �߰�
		listview->pushBackCustomItem(item_btn);
		listsize = listview->getIndex(item_btn);
		listview->refreshView();

		//��ü �Ѿ� ����
		total_price += item_price;
		totallb->setString(std::to_string(total_price));

		//����� �������� ���� ->������� �߰� �Է¿� ���
		const char* useritem_str = keyStr2.c_str();
		int size = pSale->jjgetArySize(useritem_str, sale_uname4);
		int useritem_key;
		int holding;
		for (int i = 0; i < size; i++) {
			useritem_key = pSale->jjgetAry("keyid", useritem_str, sale_uname4, i);//���� ������ �ִ� �������� Ű���̵�
			if (useritem_key == keyId) {//�� �����۰� �Ǹ��ϴ� �������� Ű���̵� ��
				holding = pSale->jjgetAry("holding", useritem_str, sale_uname4, i);
				holding -= item_qty;
				pSale->jjsetAry("holding", useritem_str, sale_uname4, holding, i);
				if (holding == 0) {
					int n;
					for (n = i; n < 3; n++) {//1->0,2->1,3->2,3�� �ʱ�ȭ
											 //Ű���̵� �ű�
						auto nextkeyid = pSale->jjgetAry("keyid", useritem_str, sale_uname4, n+1);
						if (nextkeyid != 999) {
							pSale->jjsetAry("keyid", useritem_str, sale_uname4, nextkeyid, n);
							//���� �ű�
							auto nextholding = pSale->jjgetAry("holding", useritem_str, sale_uname4, n + 1);
							pSale->jjsetAry("holding", useritem_str, sale_uname4, nextholding, n);


						}
						else break;
					}
					pSale->jjsetAry("keyid", useritem_str, sale_uname4, 999, n);
					pSale->jjsetAry("holding", useritem_str, sale_uname4, 0, n);

					//������ �޴����� �����ϱ� ����
				}
				break;
			}
			
		}

		//showW2();

		if (sell == 0)
		{
			showW1();
		}
		else if (sell == 1)
		{
			showW2();
		}
		
	
	}
}

void StoresaleLayer::sale(cocos2d::Ref* sender) {
	std::string sale_uname5 = dataSingleton::getInstance()->user;
	int user_money = pSale->jjgetInt("money", sale_uname5);
	int remain_money;
	if ( total_price == 0) {
		//�Ǹ� ������ ��ǰ�� �����ϴ�. �޼��� ����ֱ�
		auto nosale = Label::createWithTTF("�Ǹ��� �������� �������ּ���", "nanumgo.ttf", 40);
		nosale->setAnchorPoint(Point(0.5, 0.5));
		nosale->setPosition(Point(350, 750));
		nosale->setColor(Color3B::YELLOW);
		item_win2->addChild(nosale);

		auto del = DelayTime::create(2.0);
		auto fad = FadeOut::create(1.5);
		auto seq = Sequence::create(del, fad, NULL);
		nosale->runAction(seq);

	}
	else if ( total_price != 0) {
		remain_money = user_money + total_price;
		pSale->jjsetInt(remain_money, "money", sale_uname5);
		posslb->setString(std::to_string(remain_money));
		total_price = 0;
		totallb->setString(std::to_string(total_price));
		listview->removeAllItems();
		listview->removeAllChildrenWithCleanup(true);
	}
	
}

void StoresaleLayer::salecancel(cocos2d::Ref* sender) {
	std::string sale_uname6 = dataSingleton::getInstance()->user;
	size_t i = 0;
	ui::Widget *list_btn = listview->getItem(i);

	//�Ǹ� ��� �����ȵ� ->movefromList�� ���� �� �����ؾ� ��
	int list_keyid;
	int list_qty;
	int u_keyid;
	int u_holding;

	if (list_btn == NULL)
	{

	}
	else if (listview != NULL) {
		int jj = pSale->jjgetAry("keyid", keyStr2.c_str(), sale_uname6, 0);
		log("listsize: %d", listsize);
		for (i = 0; i <= listsize; i++) {

			//holding ������ ������ �� keyId�� 999�� �ٲ��� �ʾ����Ƿ� 
			//�Ʒ��� ������ ������

			list_keyid = list_btn->getTag();
			auto qty_lb = list_btn->getChildByName("qty");
			list_qty = qty_lb->getTag();
			log("qty: %d", list_qty);

			int k = -1;
			int bound = pSale->jjgetAry("keyid", keyStr2.c_str(), sale_uname6, 0);
			for (; bound != 999; ) {
				k++;
				bound = pSale->jjgetAry("keyid", keyStr2.c_str(), sale_uname6, k);
				log("bound: %d", bound);
			}

			//listsize�� json�迭 ������ �´��� Ȯ��
			//for (int j = 0; (j < bound) && (jj != 999); j++) {
			for (int j = 0; (j < k) && (k != -1); j++) {
				u_keyid = pSale->jjgetAry("keyid", keyStr2.c_str(), sale_uname6, j);
				if (list_keyid == u_keyid) {
					u_holding = pSale->jjgetAry("holding", keyStr2.c_str(), sale_uname6, j);
					u_holding += list_qty;
					pSale->jjsetAry("holding", keyStr2.c_str(), sale_uname6, u_holding, j);
				}
				else if (u_keyid == 999) {
					pSale->jjsetAry("keyid", keyStr2.c_str(), sale_uname6, list_keyid, j);
					u_holding = pSale->jjgetAry("holding", keyStr2.c_str(), sale_uname6, j);
					u_holding += list_qty;
					pSale->jjsetAry("holding", keyStr2.c_str(), sale_uname6, u_holding, j);
				}
				jj = pSale->jjgetAry("keyid", keyStr2.c_str(), sale_uname6, j);
			}
		}
	}


	if (sell == 0)
	{
		showW1();
	}
	else if (sell == 1)
	{
		showW2();
	}

	total_price = 0;
	totallb->setString(std::to_string(total_price));
	listview->removeAllItems();
	listview->removeAllChildrenWithCleanup(true);
}

void StoresaleLayer::movefromLsit(cocos2d::Ref* sender) {
	//���߿� ����Ʈ�� �ִ� �������� Ŭ���ؼ� �Ǹ� ����ϴ� ��� �� �Լ��� ����
	//����� ��Ͽ� ��� ������ �ϳ��� ������� ���� ->�����ʷ� �ؾߵǴµ� ���� ����

	/*
	if (listview != NULL) {
	for (size_t j = 0; j <= listsize; j++) {

	ui::Widget *list_btn = listview->getItem(j);
	int list_keyid = list_btn->getTag();


	}
	}
	*/
}