#include "AIBase.h"
#include "Stuff/Package/PackageEvent.h"

bool AIBase::init(int tag, MapBase* map)
{
    if (!CharacterBase::init(tag, map))
        return false;

    initBody();
    
    return true;
}

void AIBase::initBody()
{
    hand1->setTag(1);
    hand2->setTag(2);
}

void AIBase::update(float dt)
{
    MoveEvent();
    //ShotEvent();
    CharacterBase::update(dt);
}

void AIBase::MoveEvent()
{
    
    //this->reset();
    int distance = 100 * 5;
    if (this->floor == opponent->floor && opponent->gun->fire && !this->inTheAir) {
        this->keyMap["up"] = true;
    }
    if (!this->inTheAir||!Readytodie(opponent)) {//*����û���ͼ����ж�*
        //this->reset();
        if (opponent->floor >= 0 && opponent->floor < this->map->Floor.size()) {//player in the map

            if (this->floor == opponent->floor) {//ͬһ�㣬�����ƶ�
                if (opponent->getPosition().x - this->getPosition().x > distance) {
                    keyMap["left"] = false;
                    keyMap["right"] = true;
                }
                else if (opponent->getPosition().x - this->getPosition().x < -distance) {
                    keyMap["right"] = false;
                    keyMap["left"] = true;
                }
                else {

                    keyMap["right"] = false;
                    keyMap["left"] = false;
                }
                if (!this->InTheBoundary(this->map->Floor[this->floor], this->getPositionX() + (this->x_speed>0?20:-20) ) && //*��ǰ����*
                    !opponent->inTheAir) {
                    keyMap["up"] = true;
                }
            }
            else if(!this->inTheAir) {//����ͬһ�㣬��Ҫ�����ƶ�
                int up = this->floor < opponent->floor ? 1 : -1;
                int step = 0;
                if (std::abs(this->floor - opponent->floor) == 1) {//���һ������:����
                    //int i = 0;
                    for (int i = 0; i < (this->map->Floor[opponent->floor].size()); i += 2) {
                        if (opponent->getPositionX() > this->map->Floor[opponent->floor][i] && opponent->getPositionX() < this->map->Floor[opponent->floor][i + 1]) {
                            //keyMap["shot"] = true;
                            step = i;
                            break;
                        }
                    }
                }
                else {//���������:�������̨��
                    //�����Package
                    int d = pow(abs(this->getPositionX() - opponent->getPositionX()), 2) + pow(abs(this->getPositionY() - opponent->getPositionY()), 2);
                    PackageBase* colsePackage;
                    if (!this->map->packageEvent->packages.empty()) {

                        colsePackage = this->map->packageEvent->packages[0];
                        d = pow(abs(this->getPositionX() - colsePackage->getPositionX()), 2) + pow(abs(this->getPositionY() - colsePackage->getPositionY()), 2);
                        for (int i = 1; i < this->map->packageEvent->packages.size(); i++) {
                            PackageBase* package = this->map->packageEvent->packages[i];
                            if (package != nullptr) {
                                int temp_d = pow(abs(this->getPositionX() - package->getPositionX()), 2) + pow(abs(this->getPositionY() - package->getPositionY()), 2);
                                d = std::min(temp_d, d);
                                colsePackage = d == temp_d ? this->map->packageEvent->packages[i] : colsePackage;
                            }

                        }
                    }

                    int colse_step = 0;
                    //���˵����
                    if (d >= pow(abs(this->getPositionX() - opponent->getPositionX()), 2) + pow(abs(this->getPositionY() - opponent->getPositionY()), 2) || this->gun != this->initGun) {
                        float minDistance = 9999;

                        int target_floor = this->floor + up;
                        for (int i = 0; i < (this->map->Floor[target_floor].size()); i += 2) {
                            float temp_MinDistance1 = std::abs(this->getPositionX() - this->map->Floor[target_floor][i]);
                            float temp_MinDistance2 = std::abs(this->getPositionX() - this->map->Floor[target_floor][i + 1]);
                            temp_MinDistance1 = std::min(temp_MinDistance1, temp_MinDistance2);
                            if (temp_MinDistance1 < minDistance) {
                                minDistance = temp_MinDistance1;
                                colse_step = i;
                            }
                        }
                    }
                    else if (!this->map->packageEvent->packages.empty()) {//��Package���
                        /*this->getColsePackage(colsePackage);*/
                        auto package = colsePackage;
                        int distance = 0;
                        this->reset();
                        while (package != nullptr || abs(package->endFloor - this->floor) >= 2) {
                            if (package->endFloor == this->floor) {
                                if (opponent->getPosition().x - this->getPosition().x > distance) {
                                    keyMap["left"] = false;
                                    keyMap["right"] = true;
                                }
                                else if (opponent->getPosition().x - this->getPosition().x < -distance) {
                                    keyMap["right"] = false;
                                    keyMap["left"] = true;
                                }
                                else {
                                    keyMap["right"] = false;
                                    keyMap["left"] = false;
                                }
                            }
                            else if (abs(package->endFloor - this->floor) == 1) {
                                int i = 0;
                                for (; i < this->map->Floor[package->endFloor].size(); i += 2) {
                                    if (package->getPositionX() > this->map->Floor[package->endFloor][i] && package->getPositionX() < this->map->Floor[package->endFloor][i + 1]) {
                                        break;
                                    }
                                }
                                int up = this->floor < package->endFloor ? 1 : -1;
                                this->jumpTofloor(up, i);
                            }
                        }
                        colse_step = -1;
                    }
                    step = colse_step;
                }
                this->jumpTofloor(up, step);
            }
        }
        else {//�ص����
            if (this->floor < this->map->Floor.size() - 1) {
                float minDistance = 9999;
                int colse_step = 0;
                int target_floor = this->floor + 1;
                for (int i = 0; i < (this->map->Floor[target_floor].size()); i += 2) {
                    float temp_MinDistance1 = std::abs(this->getPositionX() - this->map->Floor[target_floor][i]);
                    float temp_MinDistance2 = std::abs(this->getPositionX() - this->map->Floor[target_floor][i + 1]);
                    temp_MinDistance1 = std::min(temp_MinDistance1, temp_MinDistance2);
                    if (temp_MinDistance1 < minDistance) {
                        minDistance = temp_MinDistance1;
                        colse_step = i;
                    }
                }
                this->jumpTofloor(1, colse_step);
            }
        }
    }

    if (this->inTheAir && !this->isDoubleJump) {
        keyMap["up"] = false;//*�Ȳ�Ҫ������*
    }

/* if (opponent->getPosition().x - this->getPosition().x > 400) {
        keyMap["left"] = false;
        keyMap["right"] = true;
    }
    else if (opponent->getPosition().x - this->getPosition().x < -400) {
        keyMap["right"] = false;
        keyMap["left"] = true;
    }
    else {
        keyMap["right"] = false;
        keyMap["left"] = false;
    }

    if (this->floor == opponent->floor && opponent->gun->fire && !this->inTheAir) {//���ֿ�ǹ������������ͬһ��
        keyMap["up"] = true;
    }

    if (this->inTheAir && this->getPositionX() < this->map->Floor[floor][0]) {//�ٿ��в��ҳ�����һ��ı߽�
        keyMap["left"] = false;
        keyMap["right"] = true;
        keyMap["up"] = true;
    }
    else if (this->inTheAir && this->getPositionX() > this->map->Floor[floor][1]) {//ͬ�ϵ�������
        keyMap["right"] = false;
        keyMap["left"] = true;
        keyMap["up"] = true;
    }

    if (!opponent->inTheAir && opponent->floor > this->floor && !this->inTheAir) {//���������棬�ƶ��ӽ�
        keyMap["up"] = true;
    }
    else if (!opponent->inTheAir && opponent->floor < this->floor) {//���������棬�ƶ��ӽ�
        keyMap["down"] = true;
    }*/
}

void AIBase::ShotEvent()
{
    if (this->shotLasttime) {//�ϴο�ǹ���򱾴β���ǹ�����������
        this->keyMap["shot"] = false;
        Sleep(1);
        this->shotLasttime = false;
    }
    else {
        if ((opponent->floor != map->Floor.size() - 1 || !opponent->inTheAir)  && this->valid )
        {
            if (opponent->getPosition().x - this->getPosition().x < 0 && this->floor == opponent->floor) {
                this->Flip(true);
                this->keyMap["shot"] = true;
                this->shotLasttime = true;
            }
            else if (opponent->getPosition().x - this->getPosition().x > 0 && this->floor == opponent->floor) {
                this->Flip(false);
                this->keyMap["shot"] = true;
                this->shotLasttime = true;
            }
            else {
                this->keyMap["shot"] = false;
            }
        
        }
    }
    if (std::abs(opponent->getPositionY() - this->getPositionY())>100) {
        this->keyMap["shot"] = false;
    }
}


void AIBase::reset() {
    keyMap["left"] = false;
    keyMap["right"] = false;
    keyMap["up"] = false;
    keyMap["down"] = false;
   
}
int AIBase::find_thisStep() {//�ҵ���������step
    for (int i = 0; i < this->map->Floor[this->floor].size(); i += 2) {
        if (this->getPositionX() >= this->map->Floor[this->floor][i] &&
            this->getPositionX() <= this->map->Floor[this->floor][i + 1]) {
            return i;
        }
    }
    return -1;
}

bool AIBase::Readytodie(CharacterBase* player) {
    
    if (player->getPositionX() <= this->map->Floor[player->floor].front() ||
        player->getPositionX() >= this->map->Floor[player->floor].back()) {
        return true;
    }
    else if (player->getPositionY() < this->map->floor_base) {
        return true;
    }
    return false;
}

bool AIBase::opponentReadytodie()//�ж�����Ƿ�׼������
{
    for (int floor = opponent->floor; floor >= 0; floor--) {
        for (int i = 0; i < this->map->Floor[floor].size(); i += 2) {
            if (opponent->getPositionX() >= this->map->Floor[floor][i] &&
                opponent->getPositionX() <= this->map->Floor[floor][i + 1]) {
                return false;
            }
        }
    }
    return true;
}

void AIBase::jumpTofloor(int up, int step) {//��Ծ������up��1����������-1����������step��Ŀ��̨��
    if (step < 0) { return; }
    std::string keyboard = up == 1 ? "up" : "down";
    float add_width = 20;
    int this_step = this->find_thisStep();
    int target_floor = this->floor + up;
    if (step >= 0 && step < this->map->Floor[target_floor].size()) {
        if (!opponent->inTheAir&&this->getPositionX() > this->map->Floor[target_floor][step] - add_width * 3 && this->getPositionX() < this->map->Floor[target_floor][step + 1] + add_width * 3
            || (this_step >= 0 && this->getPositionX() - this->map->Floor[this->floor][this_step] >= 0 && this->getPositionX() - this->map->Floor[this->floor][this_step] <= add_width)
            || (this_step >= 0 && this->getPositionX() - this->map->Floor[this->floor][this_step + 1] <= 0 && this->getPositionX() - this->map->Floor[this->floor][this_step + 1] >= -add_width)) {
            keyMap[keyboard] = true;
            
        }
        if (this->getPositionX() <= this->map->Floor[target_floor][step] + add_width * 5) {
            keyMap["right"] = true;
            keyMap["left"] = false;
        }
        else if (this->getPositionX() >= this->map->Floor[target_floor][step + 1] - add_width * 5) {
            keyMap["left"] = true;
            keyMap["right"] = false;
        }
        if (!this->InTheBoundary(this->map->Floor[this->floor], this->getPositionX()) && !opponent->inTheAir) {
            keyMap["up"] = true;

        }
    }
}
//void AIBase::getColsePackage(PackageBase* package) {
//    int distance = 0;
//    this->reset();
//    while (package != nullptr || abs(package->endFloor-this->floor)>=2) {
//        if (package->endFloor == this->floor) {
//            if (opponent->getPosition().x - this->getPosition().x > distance) {
//                keyMap["left"] = false;
//                keyMap["right"] = true;
//            }
//            else if (opponent->getPosition().x - this->getPosition().x < -distance) {
//                keyMap["right"] = false;
//                keyMap["left"] = true;
//            }
//            else {
//                keyMap["riuu'haoght"] = false;
//                keyMap["left"] = false;
//            }
//        }
//        else if (abs(package->endFloor - this->floor) == 1) {
//            int i = 0;
//            for (; i < this->map->Floor[package->endFloor].size(); i+=2) {
//                if (package->getPositionX() > this->map->Floor[package->endFloor][i] && package->getPositionX() < this->map->Floor[package->endFloor][i + 1]) {
//                    break;
//                }
//            }
//            int up = this->floor < package->endFloor ? 1 : -1;
//            this->jumpTofloor(up, i);
//        }
//    }
//}