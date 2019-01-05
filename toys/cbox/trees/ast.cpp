#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <string>
#include <regex>


using namespace std;

typedef struct ast_node {
    int type;
    int level;
    vector<ast_node> sibs;
    ast_node *child;
} ast_node;

int level = 0;
stack<ast_node> stack;

void add_sibling()
{
}

void add_child()
{
}

int main()
{
    ast_node root;
    root.type = 42;
    string line;
    int no = 0;
    regex r("(include)(.*)");
    while (getline(std::cin, line)) {
        //printf("%d: %s\n", no, line.c_str());
        std::smatch m;
        if (std::regex_search(line, m, r)) {
            //for(auto v: m) std::cout << v << std::endl;
            cout <<  m[2] << endl;
        }
        no++;
    }
}

