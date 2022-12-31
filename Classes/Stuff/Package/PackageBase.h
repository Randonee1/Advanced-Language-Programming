#ifndef PACKAGE_BASE_H
#define PACKAGE_BASE_H

#include "cocos2d.h"
#include "Sprite/CharacterBase.h"
#include "Map/MapBase.h"

USING_NS_CC;

class PackageBase : public Sprite
{
public:

	bool init(MapBase* map);

	virtual void GetPackage(CharacterBase* player);

	bool Disappear();

	void update(float dt);

	Sprite* package;

	int endFloor;
protected:
	bool intheair = true;
	float updatetime;
	float duration = 10;

	//int endFloor;
	float y_speed;
	float gravitation = -1000;
};

#endif