#include "simple_file_parser.h" // The class interface
 #include <iostream>
 #include <iomanip>
 #include <map>
 #include <string>
 using namespace std;

 #define MYERR(msg) cerr << endl << "ERROR:" << __FILE__ << ":" << __LINE__ << ": " << msg << endl; exit(1)

 int main(int argc,char** argv)
 {
    string file_name = argv[1];
    simple_file_parser sfp;
    if (!sfp.open(file_name)) {
       MYERR("cannot read file: '" << file_name << "'");
    }

    // Describe additional single character delimiters
    // so that it will break out 'foo+bar' as 3 tokens
    // instead of 1.
    sfp.set_single_char_tokens(";+");

    // Read each line. Comments and blank lines are ignored.
    while (sfp.get_next_line()) {
       // Print out the tokens for each line.
       cout << "Line " << sfp.get_line_number() << " has "
          << sfp.get_num_tokens() << " tokens" << endl;
       for(size_t i=0;i<sfp.get_num_tokens();i++) {
          cout << "   token[" 
               << setw(2) << setfill('0') << right << i
               << left << setfill(' ') << "] = " 
               << "'" << sfp.get_token(i) << "'"
               << endl;
       }
    }
    return 0;
 }
 #include "simple_file_parser.cc" // The class implementation
