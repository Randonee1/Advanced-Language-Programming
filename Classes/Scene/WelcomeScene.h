#ifndef WELCOME_SCENE_H
#define WELCOME_SCENE_H

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public Layer
{
public:
	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(WelcomeScene);

	//���ɱ���
	void initBackGround();

	//����Logo
	void initLogo();

	//���ɲ˵�
	void initButton();

	//�˳�����
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) override;

private:
};

#endif