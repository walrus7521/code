#include <iostream>
#include <string>
#include <list>

// https://en.wikibooks.org/

class MediatorInterface;

class PeerInterface {
        std::string name;
    public:
        PeerInterface (const std::string& newName) : name (newName) {}
        std::string getName() const {return name;}
        virtual void sendMessage (const MediatorInterface&, 
                const std::string&) const = 0;
        virtual void receiveMessage (const PeerInterface*, 
                const std::string&) const = 0;
};

class Peer : public PeerInterface {
    public:
        using PeerInterface::PeerInterface;
        virtual void sendMessage (const MediatorInterface&, 
                const std::string&) const override;
    private:
        virtual void receiveMessage (const PeerInterface*, 
                const std::string&) const override;
};

class MediatorInterface {
    private:
        std::list<PeerInterface*> colleagueList;
    public:
        const std::list<PeerInterface*>& getPeerList() 
            const {return colleagueList;}
        virtual void distributeMessage (const PeerInterface*, 
                const std::string&) const = 0;
        virtual void registerPeer (PeerInterface* colleague) 
            {colleagueList.emplace_back (colleague);}
};

class Mediator : public MediatorInterface {
    virtual void distributeMessage (const PeerInterface*, 
            const std::string&) const override;
};

void Peer::sendMessage (const MediatorInterface& mediator, 
        const std::string& message) const {
    mediator.distributeMessage (this, message);
}

void Peer::receiveMessage (const PeerInterface* sender, 
        const std::string& message) const {
    std::cout << getName() << 
        " received the message from " << 
        sender->getName() << ": " << 
        message << std::endl;
}

void Mediator::distributeMessage (const PeerInterface* sender, 
        const std::string& message) const {
    for (const PeerInterface* x : getPeerList())
        if (x != sender)  // Do not send the message back to the sender
            x->receiveMessage (sender, message);
}
 
int main()
{

    Peer *bob   = new Peer("Bob"),  
         *sam   = new Peer("Sam"),  
         *frank = new Peer("Frank"),  
         *tom   = new Peer("Tom");

    Peer* staff[] = {bob, sam, frank, tom};

    Mediator mediatorStaff, mediatorSamsBuddies;

    for (Peer* x : staff)
        mediatorStaff.registerPeer(x);

    bob->sendMessage(mediatorStaff, "I'm quitting this job!");

    mediatorSamsBuddies.registerPeer(frank);  
    mediatorSamsBuddies.registerPeer(tom);  // Sam's buddies only

    sam->sendMessage(mediatorSamsBuddies, "He's gone!  Let's go for a drink!"); 

    return 0;
}
