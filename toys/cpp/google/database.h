#ifndef _DATABASE_H_
#define _DATABASE_H_

// database.h, Maggie Johnson
// Description: Class for a database of Composer records.
#include  <iostream>
#include <string>
#include "composer.h"

using namespace std;

// Our database holds 100 composers, and no more.
const int kMaxComposers = 100;

class Database {
 public:
  Database() {
      next_slot_ = 0;
  }
  ~Database(){};

  // Add a new composer using operations in the Composer class.
  // For convenience, we return a reference (pointer) to the new record.
  Composer& AddComposer(std::string in_first_name, std::string in_last_name,
                        std::string in_genre, int in_yob, std::string in_fact) {
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
  Composer& GetComposer(std::string in_last_name) {
    for (int i = 0; i < next_slot_; ++i) {
        if (in_last_name == composers_[i].last_name()) {
            return composers_[i];
        }
    }
    return *(Composer*) nullptr;
  }
  
  // Display all composers in the database.
  void DisplayAll() {
    for (int i = 0; i < next_slot_; ++i) {
        composers_[i].Display();
    }
  }
  
  // Sort database records by rank and then display all.
  void DisplayByRank() {}

 private:
  // Store the individual records in an array.
  Composer composers_[kMaxComposers];
  // Track the next slot in the array to place a new record.
  int next_slot_;
};

#endif // _DATABASE_H_
