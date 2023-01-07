#include"Scene/AfterGame.h"
#include"Scene/GameScene.h"
#include"Scene/PlayerSetup.h"
#include"Manager/UserManager.h"

Scene* AfterGame::createScene()
{
	return AfterGame::create();
}
bool AfterGame::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//��������
	auto background = Sprite::create("ranking/ranking.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//���ð�ť
	auto Continue = ui::Button::create("ranking/backon.png", "ranking/back.png");
	Continue->setScale(1.0f);
	Continue->addTouchEventListener(CC_CALLBACK_2(AfterGame::buttonCallBack, this));
	Continue->setPosition(Vec2(origin.x + visibleSize.width * (775.5 - 70 + 1160) / 2560, origin.y + 1440 - 420 - 198 * 4));
	this->addChild(Continue);

	auto manager = UserManager::getInstance();
	std::string player1 = manager->player1;
	std::string player2 = manager->player2;
	auto map = manager->Standing;
	//����
	map[player1] = { 100 ,0.75,7,6,4,420,300};
	//map[player1] = { 100,0.89,12,8,8,576,463 };
	map[player2] = { 100,0.89,12,8,8,576,463};

	//����map
	map = calculate(player1,map);
	manager->Standing = calculate(player2, map);
	
	//����ҳ��


	//�ж�û���������ֵ����
	if (player1 == "") {
		manager->Standing.erase("");
	}
	else if (player2 == "") {
		manager->Standing.erase("");
	}

	//д�ļ�
	std::ofstream outClientFile("StandingFile.txt", std::ios::out);
	if (!outClientFile) {
		log("File Write ERROR");
		std::exit(EXIT_FAILURE);
	}
	std::map<std::string, std::vector<double>>::iterator it;
	for (it = manager->Standing.begin(); it != manager->Standing.end();++it) {
		outClientFile << it->first << " " << it->second[0] << " " << it->second[1] << " " << it->second[2] << " " << it->second[3] << " " << it->second[4] << " " << it->second[5] <<" "<<it->second[6]<< std::endl;
	}
	outClientFile.close();

	return true;
}

std::map<std::string, std::vector<double>> AfterGame::calculate(std::string s, std::map<std::string, std::vector<double>> &m) {
	//name;   mark=������*��ɱ�������������ʣ�������ɱ��    �ܳ������þֻ�ɱ�����þ������;�þ�������
	m[s][3] += 1;//�ܳ�����
	double num = m[s][3];
	double rate = m[s][6] / m[s][5];//�þ�������
	double mark = rate * m[s][4];
	m[s][0] += mark;//�ܷ���
	m[s][1] = (m[s][1] * (num - 1) + rate) / num;//����������
	m[s][2] = (m[s][2] * (num - 1) + m[s][4]) / num;//������ɱ
	return m;
}

void AfterGame::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(Transition::create(0.5f, PlayerSetup::create()));
		break;
	default:
		break;
	}
}