#include <iostream>
#include <string>

using namespace std;

bool is_valid(string ip)
{
    int len = ip.size();
    return false;
}
#if 0
bool is_valid(string ip, int len)
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
#endif

int main()
{
    string ip = "19216811";
    int len = ip.size();
    cout << "ip: " << len << endl;
    string ip_build;
    for (int i = 0; i < len-3; ++i) {
        for (int j = 0; j < 3; i++) {
            ip_build.append(ip[i]);
            if (is_valid(ip_build)) {
            }
        }
    }
}

