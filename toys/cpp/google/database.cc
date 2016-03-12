#include <string>
#include "database.h"

using namespace std;

Database::Database()
{
}

Database::~Database()
{
}

  // Add a new composer using operations in the Composer class.
  // For convenience, we return a reference (pointer) to the new record.
Composer& Database::AddComposer(string in_first_name, string in_last_name,
                        string in_genre, int in_yob, string in_fact)
{
    return composers_[0];
}

  // Search for a composer based on last name. Return a reference to the
  // found record.
Composer& Database::GetComposer(string in_last_name)
{
    return composers_[0];
}
  // Display all composers in the database.
void Database::DisplayAll()
{
}
  // Sort database records by rank and then display all.
void Database::DisplayByRank()
{
}


