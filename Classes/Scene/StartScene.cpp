#include "StartScene.h" 
#include"Scene/Loading.h"

bool StartScene::init() {
	
	if (!Scene::init())
	{
		return false;
	}

	//�������ֿ��ƣ���ʱû�п����������⣩
	auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume;
	if (!instance->isBackgroundMusicPlaying()) {
		//volume = 1.0f;
	}
	else {
		//volume = instance->getBackgroundMusicVolume();
		instance->stopBackgroundMusic(); //stop���޷��ָ�����
	}
	instance->playBackgroundMusic("Music/Start.mp3", true);
	//instance->setBackgroundMusicVolume(volume);
	//auto backgroundAudioID = AudioEngine::play2d("Music/Start.mp3", true);//���ֻ���������õĻ����ᵼ��ÿ����һ�Σ��ͻῪʼ���ű������֣����������ص���



	//����delay�� ����׽���������л�
	auto* delay = DelayTime::create(1.05f);
	auto* func = CallFunc::create([this]() {
		Director::getInstance()->replaceScene(Loading::createScene());
		});
	this->runAction(Sequence::create(delay, func, nullptr));

	

}
