#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

void debug_cli( int argc, char** argv )
{
    vector <string> args( argv + 1, argv + argc );

    cout << argv[ 0 ] << " has " << args.size() << " arguments.\n";

    for (size_t n = 0; n < args.size(); n++) {
        cout << n << ": \"" << args[n] << "\"\n";
    }

    // Find the magic "-hello" argument.

    size_t n = std::find( args.begin(), args.end(), "-hello" ) - args.begin();
    if (n < args.size()) {
        cout << "Argument number " << n << " told me to tell you \"Hello\".\n";
    }

    n = std::find( args.begin(), args.end(), "-o" ) - args.begin();
    if (n < args.size()) {
        cout << "output file: " << args[n+1] << endl;
    }

    n = std::find( args.begin(), args.end(), "-i" ) - args.begin();
    if (n < args.size()) {
        cout << "input file: " << args[n+1] << endl;
    }
}

typedef enum {
    arg_in      = 0,
    arg_out     = 1,
    arg_inout   = 2
} argument_id;

vector<pair<int, string>> parse_args( int argc, char** argv )
{
    vector<pair<int, string>> parsed_args;

    vector <string> args( argv + 1, argv + argc );

    size_t n = std::find( args.begin(), args.end(), "-o" ) - args.begin();
    if (n < args.size()) {
        cout << "output file: " << args[n+1] << endl;
        pair<int, string> p = std::make_pair(arg_out, args[n+1]);
        parsed_args.push_back(p);
    }

    n = std::find( args.begin(), args.end(), "-i" ) - args.begin();
    if (n < args.size()) {
        cout << "input file: " << args[n+1] << endl;
        pair<int, string> p = std::make_pair(arg_in, args[n+1]);
        parsed_args.push_back(p);
    }
    return parsed_args;
}


int main( int argc, char** argv )
{
    //debug_cli(argc, argv);

    vector<pair<int, string>> args = parse_args(argc, argv);

    for (vector<pair<int, string>>::const_iterator it = args.begin() ; 
        it != args.end () ;  // Use (), and assuming itt was a typo
        it++) {
        //cout << it->first << " -> " << it->second << endl; // Use -> 
        switch (it->first) {
            case arg_in:  cout << "dude" << endl; break;
            case arg_out: cout << "yo sup" << endl; break;
        }
    }

    return 0;
}
