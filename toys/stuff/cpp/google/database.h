#ifndef _DATABASE_H_
#define _DATABASE_H_

// database.h, Maggie Johnson
// Description: Class for a database of Composer records.
#include  <iostream>
#include <string>
#include "composer.h"

// Our database holds 100 composers, and no more.
const int kMaxComposers = 100;

class Database {
 public:
  Database();
  ~Database();

  // Add a new composer using operations in the Composer class.
  // For convenience, we return a reference (pointer) to the new record.
  Composer& AddComposer(std::string in_first_name, std::string in_last_name,
                        std::string in_genre, int in_yob, std::string in_fact);
  // Search for a composer based on last name. Return a reference to the
  // found record.
  Composer& GetComposer(std::string in_last_name);
  // Display all composers in the database.
  void DisplayAll();
  // Sort database records by rank and then display all.
  void DisplayByRank();

 private:
  // Store the individual records in an array.
  Composer composers_[kMaxComposers];
  // Track the next slot in the array to place a new record.
  int next_slot_;
};

#endif // _DATABASE_H_
