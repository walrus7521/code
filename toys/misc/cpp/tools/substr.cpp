#include <iostream>

using std::cout;

bool hasSubstring(const char *str, const char *find) {
    if (str[0] == '\0' && find[0] == '\0')
        return true;
    for (int i = 0; str[i] != '\0'; i++) {
        bool foundNonMatch = false;
        for(int j = 0; find[j] != '\0'; j++) {
            if (str[i + j] != find[j]) {
                foundNonMatch = true;
                break; 
            }
        }
        if (!foundNonMatch) return true;
    }
    return false;
}

int main()
{
    char str[] = {"google"};
    char p1[] = {"oog"};
    char p2[] = {"og"};
    char p3[] = {"go"};
    char p4[] = {"glee"};
    if (hasSubstring(str, p4)) {
        cout << "has substring\n";
    } else {
        cout << "doesn't have substring\n";
    }
    return 0;
}
