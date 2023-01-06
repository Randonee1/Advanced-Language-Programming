#include "GameScene.h"
#include "PlayerSetup.h"
#include "Layer/PlayerStateMenu.h"
#include "Map/MapBase.h"
#include "Map/MapTest.h"
#include "Map/MapSpace.h"
#include "Map/MapSunset.h"
#include "Map/MapSeele.h"

Scene* GameScene::CreateGame(int Level)
{
    auto scene = new GameScene();
    if (scene && scene->initGame(Level)) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return NULL;
}

bool GameScene::initGame(int Level)
{
    initKeyboardListener();

    auto playerStateMenu = PlayerStateMenu::create();
    MapBase* game;

    //后续会加入其他的一些模式
    switch (Level)
    {
    case(0):
        game = MapTest::createGame();
        break;
    case(1):
        game = MapSpace::createGame();
        break;
    case(2):
        game = MapSunset::createGame();
        break;
    case(3):
        game = MapSeele::createGame();
        break;
    }

    game->bindPlayerStateMenu(playerStateMenu);
    //playerStateMenu->initPlayerState();
    this->addChild(game);
    this->addChild(playerStateMenu);

    return true;
}

void GameScene::initKeyboardListener()
{
    EventListenerKeyboard* listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        EscapeEvent();
    }
}

void GameScene::EscapeEvent()
{
    //构想：点击esc游戏暂停，出现一个弹窗，两个选项，一个重开游戏，一个结束游戏
    Director::getInstance()->replaceScene(Transition::create(0.5f, PlayerSetup::create()));
}
