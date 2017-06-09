#include <iostream>
#include "game.h"

using namespace std;

Option* CreateOption(PlayerOptions optionType)
{
    Option* pOption = nullptr; // base pointer type

    switch (optionType) {
    case PlayerOptions::GoNorth:
        pOption = new MoveOption(
                Room::JoiningDirections::North,
                PlayerOptions::GoNorth, (const char *) "Go North");
        break;
    case PlayerOptions::GoEast:
        pOption = new MoveOption(
                Room::JoiningDirections::East,
                PlayerOptions::GoEast, "Go East");
        break;
    case PlayerOptions::GoSouth:
        pOption = new MoveOption(
                Room::JoiningDirections::South,
                PlayerOptions::GoSouth, "Go South");
        break;
    case PlayerOptions::GoWest:
        pOption = new MoveOption(
                Room::JoiningDirections::West,
                PlayerOptions::GoWest, "Go West");
        break;
    case PlayerOptions::OpenChest:
        //pOption = new OpenChestOption("Open Chest");
        break;
    case PlayerOptions::AttackEnemy:
        //pOption = new AttackEnemyOption();
        break;
    case PlayerOptions::Quit:
        //pOption = new QuitOption();
        break;
    case PlayerOptions::None:
        break;
    default:
        break;
    }

    return pOption;
}

Enemy* CreateEnemy(EnemyType enemyType)
{
    Enemy* pEnemy = nullptr;

    switch (enemyType) {
    case EnemyType::Dragon:
        pEnemy = new Enemy(EnemyType::Dragon);
        break;
    case EnemyType::Orc:
        pEnemy = new Enemy(EnemyType::Orc);
        break;
    default:
        //assert(false); // unknown enemy type
        break;
    }

    return pEnemy;
}



int main()
{
    Game game;
}

