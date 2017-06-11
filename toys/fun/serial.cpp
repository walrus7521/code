#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cassert>

using namespace std;


template <typename T>
class Singleton
{
private:
    static T* m_instance;
public:
    Singleton() {
        assert(m_instance == nullptr);
        if (m_instance == nullptr) {
            m_instance = static_cast<T*>(this);
        }
    }    
    virtual ~Singleton() {
        m_instance = nullptr;
    }
    static T& GetSingleton() {
        return *m_instance;
    }
    static T* GetSingletonPtr();
};

template <typename T>
T* Singleton<T>::m_instance = nullptr;

template <typename T>
T* Singleton<T>::GetSingletonPtr() {
    return m_instance;
}

class Serializable;
class SerializationManager;

class SerializationManager : public Singleton<SerializationManager>
{
public:
    void RegisterSerializable(Serializable* pSerializable);
    void RemoveSerializable(Serializable* pSerializable);
    Serializable* GetSerializable(uint32_t serializableId) const;
    void ClearSave();
    void Save();
    bool Load();
private:
    using Serializables = std::unordered_map<uint32_t, Serializable*>;
    Serializables m_serializables;

    const std::string m_filename{"Save.txt"};    
};

class Serializable
{
public:
    explicit Serializable(uint32_t id)
        : m_id{ id } {
            cout << "yo sup" << endl;
            SerializationManager::GetSingleton().
                RegisterSerializable(this);
        }
    ~Serializable() {
        SerializationManager* pSerializationManager = 
            SerializationManager::GetSingletonPtr();
        if (pSerializationManager) {
            pSerializationManager->RemoveSerializable(this);
        }
    }
    uint32_t GetId() { return m_id; }
    virtual void OnSave(ofstream& file) = 0; //{}
    virtual void OnLoad(ifstream& file) = 0; //{}
private:
    uint32_t m_id{ 0 };
};


void SerializationManager::RegisterSerializable(Serializable* pSerializable) {
    cout << "reg yo" << endl;
    uint32_t id = pSerializable->GetId();
    cout << "reg: " << id << endl;
    //m_serializables.find(id);
    //cout << "end: " << p << endl;
    bool isEmpty = m_serializables.empty();
    //assert(m_serializables.find(id) == m_serializables.end());
    cout << "emp yo" << endl;
    //m_serializables.emplace(pSerializable->GetId(), pSerializable);
}
void SerializationManager::RemoveSerializable(Serializable* pSerializable) {
    auto iter = m_serializables.find(pSerializable->GetId());
    if (iter != m_serializables.end()) {
        m_serializables.erase(iter);
    }
}
Serializable* SerializationManager::GetSerializable(uint32_t serializableId) const {
    Serializable *pSerializable{ nullptr };
    auto iter = m_serializables.find(serializableId);
    if (iter != m_serializables.end()) {
        pSerializable = iter->second;
    }
    return pSerializable;
}
void SerializationManager::ClearSave(){
    ofstream file{ m_filename };
    file << false;
}
void SerializationManager::Save(){
    ofstream file{ m_filename };
    file << true;
    file << endl;
    for (auto& serializable : m_serializables) {
        Serializable *pSerializable = serializable.second;
        file << pSerializable->GetId();
        pSerializable->OnSave(file);

        file << endl;
        file << endl;
    }
}
bool SerializationManager::Load() { 
    ifstream file{ m_filename };
    bool found = file.is_open();
    if (found) {
        bool isValid;
        file >> isValid;
        if (isValid) {
            cout <<
                "found data, load it?"
                "(type yes to load)"
                << endl;
            string shouldLoad;
            cin >> shouldLoad;
            if (shouldLoad == "yes") {
                while (!file.eof()) {
                    uint32_t serializableId{ 0 };
                    file >> serializableId;
                    auto iter = m_serializables.find(serializableId);
                    if (iter != m_serializables.end()) {
                        iter->second->OnLoad(file);
                    }
                }
            }
        } else {
            found = false;
        }
    }
    return found; 
}

class Test : public Serializable
{
public:
    Test(uint32_t id) : Serializable(id) { cout << "Test ctor" << endl; }
    virtual void OnSave(ofstream& file) {}
    virtual void OnLoad(ifstream& file) {}
};

int main()
{
    new SerializationManager();
    Test t(42);
}


