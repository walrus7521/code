#ifndef _COMPOSER_H_
#define _COMPOSER_H_

#include <iostream>
#include <string>

using namespace std;

// composer.h, Maggie Johnson
// Description: The class for a Composer record.
// The default ranking is 10 which is the lowest possible.
// Notice we use const in C++ instead of #define.
const int kDefaultRanking = 10;

class Composer {
 public:
  // Constructor
  Composer(){}
  // Here is the destructor which has the same name as the class
  // and is preceded by ~. It is called when an object is destroyed
  // either by deletion, or when the object is on the stack and
  // the method ends.
  ~Composer(){}

  // Accessors and Mutators
  void set_first_name(std::string in_first_name) {
    first_name_ = in_first_name;
  }  
  std::string first_name() {
    return first_name_;
  }  
  void set_last_name(std::string in_last_name) {
    this->last_name_ = in_last_name;
    cout << "setting last name: " << this->last_name_ << endl;
  }
  
  std::string last_name() {
    return last_name_;
  }
  
  void set_composer_yob(int in_composer_yob) {
    this->composer_yob_ = in_composer_yob;
  }
  
  int composer_yob() {
    return composer_yob_; // year of birth
  }
  
  void set_composer_genre(std::string in_composer_genre) {
    this->composer_genre_ = in_composer_genre;
  }

  std::string composer_genre() {
    return composer_genre_; // baroque, classical, romantic, etc.
  }
  void set_ranking(int in_ranking) {
    this->ranking_ = in_ranking;
  }
  
  int ranking() {
    return ranking_;
  }
  
  void set_fact(std::string in_fact) {
    this->fact_ = in_fact;
  }

  std::string fact() {
    return fact_;
  }

  // Methods
  // This method increases a composer's rank by increment.
  void Promote(int increment) {
    this->ranking_ += increment;
  }  
  // This method decreases a composer's rank by decrement.
  void Demote(int decrement) {
    this->ranking_ -= decrement;
  }
  
  // This method displays all the attributes of a composer.
  void Display() {
    cout << "first name:    : " << this->first_name_ << endl;
    cout << "last name:     : " << this->last_name_ << endl;
    cout << "composer yob   : " << this->composer_yob_ << endl;
    cout << "composer genre : " << this->composer_genre_ << endl;
    cout << "fact           : " << this->fact_ << endl;
    cout << "ranking        : " << this->ranking_ << endl;
  }
  

 private:
  std::string first_name_;
  std::string last_name_;
  int composer_yob_; // year of birth
  std::string composer_genre_; // baroque, classical, romantic, etc.
  std::string fact_;
  int ranking_;
};

#endif // _COMPOSER_H_

