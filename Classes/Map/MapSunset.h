#ifndef MAP_SUNSET_H
#define MAP_SUNSET_H

#include "cocos2d.h"
#include "MapBase.h"
#include "Sprite/AI1.h"
#include "Sprite/Player1.h"
#include "Sprite/CharacterBase.h"

USING_NS_CC;

class MapSunset : public MapBase
{
public:

	static MapBase* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

	void initPlayer();

	void ShotEvent() override;

private:
	Vec2 initCity1Position;
	Vec2 initCity2Position;
	Vec2 initCity3Position;
	Vec2 initMountain1Position;
	Vec2 initMountain2Position;

	Sprite* city1;
	Sprite* city2;
	Sprite* city3;
	Sprite* mountain1;
	Sprite* mountain2;

	std::vector<CharacterBase*> players;
};

#endif