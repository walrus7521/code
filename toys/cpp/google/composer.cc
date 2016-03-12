#include <iostream>
#include <string>

#include "composer.h"

using namespace std;

// composer.h, Maggie Johnson
// Description: The class for a Composer record.
// The default ranking is 10 which is the lowest possible.
// Notice we use const in C++ instead of #define.

Composer::Composer()
{
}

  // Here is the destructor which has the same name as the class
  // and is preceded by ~. It is called when an object is destroyed
  // either by deletion, or when the object is on the stack and
  // the method ends.
Composer::~Composer()
{
}

void Composer::set_first_name(string in_first_name)
{
}

string Composer::first_name()
{
  return first_name_;
}

void Composer::set_last_name(string in_last_name)
{
}

string Composer::last_name()
{
  return last_name_;
}

void Composer::set_composer_yob(int in_composer_yob)
{
}

int Composer::composer_yob()
{
  return composer_yob_; // year of birth
}

void Composer::set_composer_genre(string in_composer_genre)
{
}

string Composer::composer_genre()
{
  return composer_genre_; // baroque, classical, romantic, etc.
}

void Composer::set_ranking(int in_ranking)
{
}

int Composer::ranking()
{
  return ranking_;
}

void Composer::set_fact(string in_fact)
{
}

string Composer::fact()
{
  return fact_;
}

void Composer::Promote(int increment)
{
}

void Composer::Demote(int decrement)
{
}

void Composer::Display()
{
}

