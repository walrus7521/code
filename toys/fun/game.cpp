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

void Room::PrintOptions() const {
    for (unsigned int i = 0; i < m_dynamicOptions.size(); ++i) {
        const Option* option = m_dynamicOptions[i];
        std::cout << i + 1 << ": " << option->GetOutputText() << std::endl << std::endl;
    }

    for (StaticOptions::const_iterator iter = m_staticOptions.cbegin(); iter != m_staticOptions.cend(); ++iter) {
        const Option* option = iter->second;
        const unsigned int chosenOption = iter->first + m_dynamicOptions.size();
        std::cout << chosenOption << ": " << option->GetOutputText() << std::endl << std::endl;
    }
}

void Game::GivePlayerOptions() const
{
	cout << "What would you like to do? (Enter a corresponding number)" << endl << endl;

	// Print the options for the room
	m_player.GetCurrentRoom()->PrintOptions();
}


void Game::GetPlayerInput(stringstream& playerInputStream) const
{
	string input;
	cin >> input;
	playerInputStream << input;
}


PlayerOptions Game::EvaluateInput(stringstream& playerInputStream)
{
	PlayerOptions chosenOption = PlayerOptions::None;
	unsigned int playerInputChoice{ 0 };
	playerInputStream >> playerInputChoice;

	try
	{
		Option* option = m_player.GetCurrentRoom()->EvaluateInput(playerInputChoice);
		option->Evaluate(m_player);
		chosenOption = option->GetChosenOption();
	}
	catch (const std::out_of_range&)
	{
		cout << "I do not recognize that option, try again!" << endl << endl;
	}

	return chosenOption;
}

void Game::RunGame()
{
    InitializeRooms();

    WelcomePlayer();
    bool shouldEnd = false;
    while (shouldEnd == false)
    {
        GivePlayerOptions();

        stringstream playerInput;
        GetPlayerInput(playerInput);

        PlayerOptions selectedOption = EvaluateInput(playerInput);
        shouldEnd = selectedOption == PlayerOptions::Quit;
        if (shouldEnd == false)
        {
            //UpdateOnOption(selectedOption);
        }
    }
}



int main()
{
    Game game;
    game.RunGame();
}

