#include "CharacterBase.h"
#include <iostream>

bool CharacterBase::init(MapBase* map)
{
    if (!Sprite::init())
        return false;

    this->map = map;
    accelerate = 0;
    x_speed = 0;
    y_speed = 0;
    isDoubleJump = false;
    inTheAir = true;

    this->scheduleUpdate();

	return true;
}

void CharacterBase::update(float dt)
{
	Sprite::update(dt);

    if (!inTheAir) {
        y_speed = 0;
        isDoubleJump = false;
        if(getPositionX() < map->Floor[floor][0] || getPositionX() > map->Floor[floor][1]){
            keyMap["down"] = true;
            inTheAir = true;
            if (floor > 0)
                floor--;
        }
        else if (keyMap["up"]) {
            inTheAir = true;
            y_speed = status->y_maxSpeed;
            MoveDelay(true, false);
            keyMap["up"] = false;
            if (floor < map->Floor.size() - 1)
                floor++;
        }
        else if (keyMap["down"]) {
            if (floor > 0){
                inTheAir = true;
                floor--;
            }
        }
        
    }
    if(inTheAir){
        //跳起暂停走路动作
        StopWork();
        if (std::abs(y_speed) <= std::abs(status->gravitation * dt))
            MoveDelay(false, false);
        if (!isDoubleJump && keyMap["up"]) {
            if (keyMap["down"] && floor < map->Floor.size() - 1)
                floor++;
            y_speed = status->y_maxSpeed / 1.2;
            MoveDelay(true, false);
            isDoubleJump = true;
        }
        y_speed += status->gravitation* dt;
        if (y_speed < -status->y_maxSpeed*1.5)
            y_speed = -status->y_maxSpeed*1.5;
        keyMap["up"] = false;
    }
    if(y_speed < 0)
    {
        if (getPositionY() > map->floor_base + floor * map->floor_height && 
            getPositionY() + y_speed * dt < map->floor_base + floor * map->floor_height &&
            getPositionX() > map->Floor[floor][0] && getPositionX() < map->Floor[floor][1]) {
            keyMap["down"] = false;
            MoveDelay(true, true);
            inTheAir = false;
            y_speed = 0;
            this->setPositionY(map->floor_base + floor * map->floor_height);
        }
        else {
            this->setPositionY(getPositionY() + y_speed * dt);
            if (getPositionY() < map->floor_base + floor * map->floor_height && floor > 0)
                floor--;
        }
    }else
        this->setPositionY(getPositionY() + y_speed * dt);

    if (getPositionY() < 0)
    {
        y_speed = 0;
        floor = map->Floor.size() - 1;
        setPosition(initPosition);
    }
   
    //inTheAir ? CCLOG("intheair") : CCLOG("not intheair");

    if ((keyMap["left"] ^ keyMap["right"])) {

        if (keyMap["left"])
            Flip(true);
        else
            Flip(false);

        accelerate = keyMap["right"] ? status->acceleration: -status->acceleration;
        if (!inTheAir) {
            feet1->Work(false);
            feet2->Work(true);
            hand1->Work(true);
            hand2->Work(false);

        }
        x_speed += accelerate * dt;
        if (std::abs(x_speed) > status->x_maxSpeed)
            x_speed -= accelerate * dt;
    }
    else {
        accelerate = x_speed > 0 ? -status->resistance : status->resistance;
        if (std::abs(accelerate * dt) > std::abs(x_speed))
            x_speed = 0;
        else
            x_speed += accelerate * dt;
    }
    this->setPositionX(getPositionX() + x_speed * dt);

    if (keyMap["shot"]) {
        hand1->RaiseHandToShoot(map->platform,true);
        hand2->RaiseHandToShoot(map->platform, false);
        this->_flippedX ? x_speed += status->recoil_speed : x_speed -= status->recoil_speed;
        if (std::abs(x_speed) > status->x_maxSpeed)
            this->_flippedX ? x_speed = status->x_maxSpeed : x_speed = -status->x_maxSpeed;
        keyMap["shot"] = false;
    }
}

void CharacterBase::MoveDelay(bool up, bool floor)
{
    for (int i = 2; i < organs.size(); i++)
        organs[i]->MoveDelay(up, floor);
}

void CharacterBase::Flip(bool direction)
{
    this->setFlippedX(direction);
    for (auto organ : organs)
        organ->setFlippedX(direction);
}

void CharacterBase::StopWork()
{
    feet1->organ->stopActionByTag(10);
    feet2->organ->stopActionByTag(10);
    feet1->actionState = false;
    feet2->actionState = false;
    hand1->organ->stopActionByTag(10);
    hand2->organ->stopActionByTag(10);
    hand1->actionState = false;
    hand2->actionState = false;
}
