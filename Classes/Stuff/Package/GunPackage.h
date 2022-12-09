#ifndef GUN_PACKAGE_H
#define GUN_PACKAGE_H

#include "cocos2d.h"
#include "PackageBase.h"
#include "Weapons/Gun/Gun_MG_P90.h"
#include "Weapons/Gun/Gun_Gatling.h"
#include "Weapons/Gun/Gun_MG_MP5.h"
#include "Weapons/Gun/Gun_MG_MP7.h"
#include "Weapons/Gun/Gun_MG_Uzi.h"
#include "Weapons/Gun/Gun_Modern_Sniper.h"
#include "Weapons/Gun/Gun_Revolver.h"
#include "Weapons/Gun/Gun_Double.h"
#include "Weapons/others/Samurai_Sword.h"

USING_NS_CC;

class GunPackage : public PackageBase
{
public:

	static float updatetime;

	static GunPackage* createWithGun(MapBase* map);

	bool initWithGun(MapBase* map);

	void GetPackage(CharacterBase* player) override;

	void update(float dt) override;

	GunBase* gun;
private:
};

#endif