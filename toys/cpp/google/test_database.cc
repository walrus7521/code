// test_database.cpp, Maggie Johnson
//
// Description: Test driver for a database of Composer records.
#include <iostream>
#include "database.h"
#include "composer.h"

using namespace std;

int get_user_choice()
{
    int choice;
    cout << "Composer Database" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "1) Add a new composer" << endl;
    cout << "2) Retrieve a composer's data" << endl;
    cout << "3) Promote/demote a composer's rank" << endl;
    cout << "4) List all composers" << endl;
    cout << "5) List all composers by rank" << endl;
    cout << "0) Quit    " << endl;
    cout << " ==> ";
    cin >> choice;
    return choice;
}

int add_new_composer()
{
    //std::string first_name_;
    //std::string last_name_;
    //int composer_yob_; // year of birth
    //std::string composer_genre_; // baroque, classical, romantic, etc.
    //std::string fact_;
    //int ranking_;
    cout << "1) Add a new composer" << endl; 
    return 0;
}

int retrieve_composer()
{
    cout << "2) Retrieve a composer's data" << endl;
    return 0;
}

int prodem_composer()
{
    cout << "3) Promote/demote a composer's rank" << endl;
    return 0;
}

int list_composers(int how)
{
    switch (how) {
        case 4:
            cout << "4) List all composers" << endl;
            break;
        case 5:
            cout << "5) List all composers by rank" << endl;
            break;
        default:
            break;
    }
    return 0;
}

int main() {
    Database myDB;
#if 0
    int cmd;
    while ((cmd = get_user_choice()) != 0) {
        switch (cmd) {
            case 1: 
                add_new_composer();
                break;
            case 2:
                retrieve_composer();
                break;
            case 3:
                prodem_composer();
                break;
            case 4:
                list_composers(cmd);
                break;
            case 5:
                list_composers(cmd);
                break;
            case 0:
                break;
        }
    }
#endif
    // Remember that AddComposer returns a reference to the new record.
    Composer& comp1 = myDB.AddComposer("Ludwig van", "Beethoven", "Romantic", 1770,
    "Beethoven was completely deaf during the latter part of his life - he never "
    "heard a performance of his 9th symphony.");
    comp1.Promote(7);

    Composer& comp2 = myDB.AddComposer("Johann Sebastian", "Bach", "Baroque", 1685,
    "Bach had 20 children, several of whom became famous musicians as well.");
    comp2.Promote(5);

    Composer& comp3 = myDB.AddComposer("Wolfgang Amadeus", "Mozart", "Classical", 1756,
    "Mozart feared for his life during his last year - there is some evidence "
    "that he was poisoned.");
    comp3.Promote(2);

    cout << endl << "all Composers: " << endl << endl;
    myDB.DisplayAll();

}

