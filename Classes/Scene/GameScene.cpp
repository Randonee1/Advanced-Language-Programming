#include "GameScene.h"
#include "Layer/PlayerStateMenu.h"
#include "Map/MapBase.h"
#include "Map/MapTest.h"
#include "Map/MapSpace.h"
#include "Map/MapSunset.h"

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
    //auto playerStateMenu = PlayerStateMenu::create();
    MapBase* game;

    //���������������һЩģʽ
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
    }

    //game->bindPlayerStateMenu(playerStateMenu);
    //playerStateMenu->initPlayerState();
    this->addChild(game);
    //this->addChild(playerStateMenu);

    return true;
}
