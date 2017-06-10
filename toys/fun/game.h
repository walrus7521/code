#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <sstream>
#include <memory>

class Room;

class Player {
private:
    Room* m_pCurrentRoom;    
public:
    Player() { std::cout << "Player - ctor\n"; }
    Room* GetCurrentRoom() const {
        return m_pCurrentRoom;
    }
};

class Entity
{
public:
    Entity() { std::cout << "Entity - ctor\n"; }
    void Update(){}
};


class Item
{
private:
    std::string m_name;
public:
    Item(const std::string& name)
        : m_name{ name }
    {}
    virtual ~Item() {}
    const std::string& GetName() const { return m_name; }
};

class Sword : public Item
{
public:
    Sword() : Item("Sword") {}
};


class Chest : public Entity
{
private:
    const Item* m_item;
    bool m_isOpen{ false };

public:
    Chest(const Item* item) {};
    void Update();
    bool IsOpen() const { return m_isOpen; }
    const Item* Open() {
        m_isOpen = true;
        return m_item;
    }
};


class EventHandler {};
class Event {};
class Option;

class Room : public Entity
{
private:
    using StaticOptions = std::map<unsigned int, Option*>;
    StaticOptions m_staticOptions;
    unsigned int m_staticOptionStartKey{ 1 };

    using DynamicOptions = std::vector<Option*>;
    DynamicOptions m_dynamicOptions;
    
public:
    using Pointer = std::shared_ptr<Room>;
    enum class JoiningDirections {
        North,
        South,
        East,
        West,
        None
    };
    void PrintOptions() const;
    Option* EvaluateInput(unsigned int playerInput) {
        Option* option = nullptr;
        const unsigned int numDynamicOptions = m_dynamicOptions.size();
        if (playerInput <= numDynamicOptions) {
            unsigned int dynamicIndex = playerInput - 1;
            option = m_dynamicOptions[dynamicIndex];
            m_dynamicOptions.erase(m_dynamicOptions.begin() + dynamicIndex);
        } else {
            option = m_staticOptions.at(playerInput - numDynamicOptions);
        }
        return option;
    }
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

    const std::string& GetOutputText() const { 
        return m_outputText;
    }

    virtual void Evaluate(Player& player) = 0;

    PlayerOptions GetChosenOption() const
    {
        return m_chosenOption;
    }

    
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

    EnemyType GetType() const { return m_type; }

    bool IsAlive() const { return m_alive; }

    void Kill() { m_alive = false; }
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
    Option::Pointer m_openSwordChest;
    Option::Pointer m_quitOption;

    Sword m_sword;
    Chest m_swordChest;

    using Enemies = std::vector<Enemy::Pointer>;
    Enemies m_enemies;

    bool m_playerQuit{ false };

    void InitializeRooms(){}
    void WelcomePlayer(){ std::cout << "yo player" << std::endl; }
    void GivePlayerOptions() const;
    void GetPlayerInput(std::stringstream& playerInput) const;
    PlayerOptions EvaluateInput(std::stringstream& playerInputStream);
    

public:
    Game()
        : m_attackDragonOption{CreateOption(PlayerOptions::AttackEnemy)},
          m_attackOrcOption{CreateOption(PlayerOptions::AttackEnemy)},
          m_moveNorthOption{CreateOption(PlayerOptions::GoNorth)},
          m_moveEastOption{CreateOption(PlayerOptions::GoEast)},
          m_moveSouthOption{CreateOption(PlayerOptions::GoSouth)},
          m_moveWestOption{CreateOption(PlayerOptions::GoWest)},
          m_openSwordChest{CreateOption(PlayerOptions::OpenChest)},
          m_quitOption{CreateOption(PlayerOptions::Quit)},
          m_swordChest{ &m_sword }
    {}

    void RunGame();

    virtual void HandleEvent(const Event* pEvent){}

};
