#include <string>
#include "database.h"

using namespace std;

Database::Database()
{
    next_slot_ = 0;
}

Database::~Database()
{
}

  // Add a new composer using operations in the Composer class.
  // For convenience, we return a reference (pointer) to the new record.
Composer& Database::AddComposer(string in_first_name, string in_last_name,
                        string in_genre, int in_yob, string in_fact)
{
    cout << "adding composer..." << endl;
    if (next_slot_ < kMaxComposers) {
        composers_[next_slot_].set_first_name(in_first_name);
        composers_[next_slot_].set_last_name(in_last_name);
        composers_[next_slot_].set_composer_yob(in_yob);
        composers_[next_slot_].set_composer_genre(in_genre);
        composers_[next_slot_].set_fact(in_fact);
        return composers_[next_slot_++];
    }

    return *(Composer*) nullptr;
    //return NULL;
}

  // Search for a composer based on last name. Return a reference to the
  // found record.
Composer& Database::GetComposer(string in_last_name)
{
    for (int i = 0; i < next_slot_; ++i) {
        if (in_last_name == composers_[i].last_name()) {
            return composers_[i];
        }
    }
    return *(Composer*) nullptr;
}
  // Display all composers in the database.
void Database::DisplayAll()
{
    for (int i = 0; i < next_slot_; ++i) {
        composers_[i].Display();
    }
}
  // Sort database records by rank and then display all.
void Database::DisplayByRank()
{
}


