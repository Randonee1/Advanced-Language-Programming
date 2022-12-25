#ifndef AI_BASE_H
#define AI_BASE_H

#include "cocos2d.h"
#include "CharacterBase.h"

USING_NS_CC;

class AIBase : public CharacterBase
{
public:

	bool init(int tag, MapBase* map);

	virtual void initBody();

	void update(float dt) override;

	void MoveEvent();

	void ShotEvent();
	void reset();

	int find_thisStep();

	bool opponentReadytodie();

	void jumpTofloor(int, int);//б��Ծ�����²�ĵ�step��̨��

	int findCloestStep(int floor);//Ѱ�ҵ�floor������step

	//void getColsePackage(PackageBase*);//��������İ���

protected:
	bool shotLasttime;
};

#endif