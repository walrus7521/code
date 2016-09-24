#include <iostream>
#include <string>

using namespace std;

bool is_valid(const char *ip, int len)
{
    int dot[3] = {-1,-1,-1}, idot = 0;
    for (int i = 0; i < len; ++i) {
        if (ip[i] == '.') {
            dot[idot++] = i;
        }
    }
    for (int i = 0; i < 3; i++) {
        cout << "dot[" << i << "] = " << dot[i] << endl;
    }
    if ((dot[0] == -1) || (dot[1] == -1) || (dot[2] == -1)) {
        return false;
    }
    if ((dot[2] > dot[1]) && (dot[1] > dot[0])) {
        if ((dot[0] > 0) && dot[2] < len-1) {
            // now make sure not too many digits per field
            return true;
        }
    }
    return false;
}

int main()
{
    string ip = "1.9216.81.1";
    int n = 3;
    int min = 1, max = 3;
    int len = ip.size();
    cout << "ip: " << len << endl;
    for (int i = 0; i < len*len; ++i) {
    }
    // permute 3 dots and test
    if (is_valid(ip.c_str(), ip.size())) {
        cout << "valid" << endl;
    } else {
        cout << "invalid" << endl;
    }
}

