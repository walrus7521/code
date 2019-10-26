#include <iostream>
#include <string>
#include <regex>

using std::string;

int main ()
{
#if 0
    string line = "this is a test";
    //test
    std::regex filename_regex ("\"[a-zA-Z0-9_-][a-zA-Z0-9_-]*.[a-zA-Z0-9_-]+\"");
    //if(regex_search(line, filename_regex))
    std::sregex_iterator r_it(line.begin, line.end, filename_regex);
    std::sregex_iterator r_it_end;
    while(r_it != r_it_end) {
        cout << "Found a #include with filename: " << *it;
        ++it;
    }
    //end test
#endif
    if (std::regex_match ("subject", std::regex("(sub)(.*)") ))
              std::cout << "string literal matched\n";

    std::string s ("subject");
    std::string s2 ("hey \"check.this\" out");
    std::regex e ("(sub)(.*)");
    std::regex e2 ("\"check\\.this\"");
    if (std::regex_match (s,e))
        std::cout << "string object matched\n";

    if ( std::regex_match ( s.begin(), s.end(), e ) )
        std::cout << "range matched\n";

    std::cmatch cm;    // same as std::match_results<const char*> cm;
    std::regex_match ("subject",cm,e);
    std::cout << "string literal with " << cm.size() << " matches\n";

    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match (s,sm,e);
    std::cout << "string object with " << sm.size() << " matches\n";

    std::regex_match ( s.cbegin(), s.cend(), sm, e);
    std::cout << "range with " << sm.size() << " matches\n";

    // using explicit flags:
    std::regex_match ( "subject", cm, e, std::regex_constants::match_default );

    std::cout << "the matches were: ";
    for (unsigned i=0; i<sm.size(); ++i) {
        std::cout << "[" << sm[i] << "] ";
    }

    std::cout << std::endl;
    return 0;
}
