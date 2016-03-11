#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    char pr_num[30], descr[30]; int id;
    char file_name[20];
    char cmd;
    string line;

    cout << endl << "Enter file name: "; cin >> file_name;
    ofstream oprs(file_name, ios::out | ios::app);
    ifstream iprs;

    while (1) {
        cout << "Enter: +, x, l:";
        cin >> cmd;
        switch (cmd) {
            case '+':
                cout << "pr num: "; cin >> pr_num;
                cout << "desc  : "; cin >> descr;
                cout << "id    : "; cin >> id;
                oprs << pr_num << endl << descr << endl << id << endl;
                break;
            case 'x':
                goto exit;
                break;
            case 'l':
                iprs.open(file_name, ios::out | ios::app);
                iprs.seekg(0);
                while (iprs) {
                    std::getline(iprs, line);
                    cout << line << endl;
                }
                iprs.close();
                break;
            default:
                break;
        }
    }
exit:
    oprs.close();
    return 0;
} 

