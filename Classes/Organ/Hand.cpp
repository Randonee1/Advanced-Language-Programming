#include "Hand.h"


Hand* Hand::CreateWithName(const char* name)
{
    auto hand = new Hand();
    if (hand && hand->initWithName(name)) {
        hand->autorelease();
        return hand;
    }
    CC_SAFE_DELETE(hand);
    return NULL;
}

//void Hand::stopActionByTag(int tag)
//{
//    Node::stopActionByTag(tag);
//    if(getChildByName("gun"))
//        this->getChildByName("gun")->stopActionByTag(tag);
//}

void Hand::GetGun(GunBase* Gun)
{
    
    gun = Gun;
    gun->setPosition(Vec2(organ->getContentSize().width/2, organ->getContentSize().height/2));
    organ->addChild(gun,-1);
    gunPoint = gun->getPosition();
}

void Hand::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (gun)
        gun->setFlippedX(flippedX, organ->getContentSize().width);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        //organ->setPositionX(-organ->getPositionX());
        this->setPositionX(-this->getPositionX());
        flipX();

        actionState = false;
        organ->stopActionByTag(10);
        if(! onShot)
            organ->setPosition(Vec2(0, 0));
    }
}

void Hand::GoLeft()
{
    if (!actionState && !onShot)
    {
        Sequence* seq_left;
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(Hand::SetActionState, this));
        seq_left = Sequence::create(func, MoveTo::create(0, Vec2(0, 0)), MoveBy::create(0.2f, Vec2(-30, 0)), MoveBy::create(0.2f, Vec2(30, 0)), func, nullptr);
        seq_left->setTag(10);

        organ->runAction(seq_left);
        
    }
}

void Hand::GoRight()
{
    if (!actionState && !onShot)
    {
        Sequence* seq_right;
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(Hand::SetActionState, this));
        seq_right = Sequence::create(func, MoveTo::create(0, Vec2(0, 0)), MoveBy::create(0.2f, Vec2(30,0)), MoveBy::create(0.2f, Vec2(-30, 0)), func, nullptr);
        seq_right->setTag(10);
        

        organ->runAction(seq_right);
        
    }
}

void Hand::MoveDelay(bool up, bool floor)
{
    if (!onShot)
        OrganBase::MoveDelay(up, floor);
}

void Hand::RaiseHandToShoot(Node* background)
{
    if(!onRaise)
    {
        onShot = false;
        organ->stopAllActions();
        CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(Hand::SetShot, this));
        CallFunc* onraise = CallFunc::create(CC_CALLBACK_0(Hand::SetRaise, this));
        auto raise = MoveTo::create(0, Vec2(160, 40));
        auto delay = MoveBy::create(2, Vec2(0, 0));
        auto down = MoveTo::create(0.3, Vec2(0, 0));
        auto seq_shot = Sequence::create(onshot,onraise, raise, onraise, delay, down,onshot, nullptr);
        organ->runAction(seq_shot);

        gun->Shot(background);
    }
}

void Hand::SetActionState()
{
    actionState = !actionState;
}

void Hand::SetShot()
{

    onShot = !onShot;
}

void Hand::SetRaise()
{
    onRaise = !onRaise;
}
