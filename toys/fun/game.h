#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <memory>

class Player {};
class Entity {};
class Sword {};
class Chest {};

class EventHandler {};
class Event {};

class Room : public Entity
{
public:
    using Pointer = std::shared_ptr<Room>;
    enum class JoiningDirections {
        North,
        South,
        East,
        West,
        None
    };
};

enum class PlayerOptions {
    GoNorth,
    GoEast,
    GoSouth,
    GoWest,
    OpenChest,
    AttackEnemy,
    Quit,
    None
};

enum class EnemyType {
    Dragon,
    Orc,
    None
};

class Option
{
public:
    Option(){}
    using Pointer = std::shared_ptr<Option>;

protected:
    PlayerOptions m_chosenOption;
    std::string m_outputText;

public:
    Option(PlayerOptions chosenOption, const std::string& outputText)
        : m_chosenOption(chosenOption),
          m_outputText(outputText)
    {}

    const std::string& GetOutput() const { 
        return m_outputText;
    }

    virtual void Evaluate(Player& player) = 0;

};


class MoveOption : public Option {
public:
    MoveOption(){}
    MoveOption(Room::JoiningDirections roomOption, PlayerOptions playerOption, const char *optionName)
    {}
    void Evaluate(Player& player) {}
};

//        pOption = new MoveOption(
//                Room::JoiningDirections::North,
//                PlayerOptions::GoNorth, "Go North");




class Enemy : public Entity
{
public:
    using Pointer = std::shared_ptr<Enemy>;
private:
    EnemyType m_type;
    bool m_alive{ true };

public:
    Enemy(EnemyType type)
        : m_type{ type }
    {}

    EnemyType GetType() const {
        return m_type;
    }

    bool IsAlive() const {
        return m_alive;
    }

    void Kill() {
        m_alive = false;
    }
};

Option* CreateOption(PlayerOptions optionType);

class Game : public EventHandler
{
private:
    static const unsigned int m_numberOfRooms = 4;
    using Rooms = std::array<Room::Pointer, m_numberOfRooms>;
    Rooms m_rooms;

    Player m_player;

    Option::Pointer m_attackDragonOption;
    Option::Pointer m_attackOrcOption;
    Option::Pointer m_moveNorthOption;
    Option::Pointer m_moveEastOption;
    Option::Pointer m_moveSouthOption;
    Option::Pointer m_moveWestOption;
    Option::Pointer m_openSwordChestOption;
    Option::Pointer m_quitOption;

    Sword m_sword;
    Chest m_swordChest;

    using Enemies = std::vector<Enemy::Pointer>;
    Enemies m_enemies;

    bool m_playerQuit{ false };

    void InitializeRooms(){};
    void WelcomePlayer(){};
    void GivePlayerOptions() const{};
    void GetPlayerInput(std::stringstream& playerInput) const{};
    void EvaluateInput(std::stringstream& playerInput){};

public:
    Game()
        : m_attackDragonOption{CreateOption(PlayerOptions::AttackEnemy)},
          m_attackOrcOption{CreateOption(PlayerOptions::AttackEnemy)},
          m_moveNorthOption{CreateOption(PlayerOptions::GoNorth)},
          m_moveEastOption{CreateOption(PlayerOptions::GoEast)},
          m_moveSouthOption{CreateOption(PlayerOptions::GoSouth)},
          m_moveWestOption{CreateOption(PlayerOptions::GoWest)}
    {};

    void RunGame(){};

    virtual void HandleEvent(const Event* pEvent){};

};
