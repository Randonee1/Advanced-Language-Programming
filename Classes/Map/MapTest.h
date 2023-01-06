#ifndef MAP_TEST_H
#define MAP_TEST_H

#include "cocos2d.h"
#include "Map/MapBase.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/PlayerBase.h"
#include "Sprite/Player2.h"
#include "Sprite/AI2.h"

USING_NS_CC;

class MapTest : public MapBase
{
public:

	static MapTest* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

	//void initPlayer();

	//void ShotEvent() override;

private:
	Vec2 initBackgroundPosition;
	Sprite* background;
	/*CharacterBase* player1;
	CharacterBase* player2;*/
	//std::vector<CharacterBase*> players;
	//PackageEvent* packageEvent;
};

#endif