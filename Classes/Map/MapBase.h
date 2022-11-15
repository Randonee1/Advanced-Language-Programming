#ifndef MAP_BASE_H
#define MAP_BASE_H

#include "cocos2d.h"
USING_NS_CC;

class MapBase : public Layer
{
public:

	bool init() override;

	CREATE_FUNC(MapBase);

	//void bindPlayerStateMenu(PlayerStateMenu* playerState);

	Sprite* background;
protected:
	Size visibleSize;

	Size backgroundSize;

	//void onEnterTransitionDidFinish() override;

	//��ͬ�ؿ���ͬ���¼�����
	//virtual void initBackground();

	//virtual void initPlatform();

	//virtual void initPlayer();
};

#endif