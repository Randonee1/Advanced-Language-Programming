#include "Loading.h"

Scene* Loading::createScene()
{
    auto scene = Scene::create();
    auto layer = Loading::create();
    scene->addChild(layer);
    return scene;
}

bool Loading::init()
{
    if (!Layer::init())
        return false;
    isloaddone = false;
    auto back = LayerColor::create(Color4B::GRAY, 12000, 10000);
    back->setIgnoreAnchorPointForPosition(false);
    back->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(back);
    schedule(CC_SCHEDULE_SELECTOR(Loading::logic));
    return true;
}

void Loading::loadResources()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("test.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("space.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Player1.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MG_gtl.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("body_fx.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("blood.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bodyColored.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("superJumpHalo.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("colorSpots.plist");

    isloaddone = true;
}

void Loading::logic(float dt)
{
    if (!isloaddone) {
        loadResources();
    }
    if (isloaddone) {
        //��ʱ��д��������д��WelcomeScene�ٻ�
        //auto scene = GameScene::CreateGame(1);
        Director::getInstance()->replaceScene(Transition::create(0.2f, GameScene::CreateGame(0)));
    }
}
