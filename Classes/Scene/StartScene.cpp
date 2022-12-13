#include "StartScene.h" 
#include"Scene/Loading.h"

bool StartScene::init() {
	
	if (!Scene::init())
	{
		return false;
	}
	//����delay�� ����׽���������л�
	auto* delay = DelayTime::create(1.05f);
	auto* func = CallFunc::create([this]() {
		Director::getInstance()->replaceScene(Loading::createScene());
		});
	this->runAction(Sequence::create(delay, func, nullptr));

}
