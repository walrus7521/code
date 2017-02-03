#include <stdio.h>
#include <string.h>

int is_anagram(char *s1, char *s2) {
    char tester[256];
    int i, len = strlen(s1), is_ana = 0;
    memset(tester, 0, 256);
    for (i = 0; i < len; i++) {
        tester[s1[i]]++;
    }
    len = strlen(s2);
    for (i = 0; i < len; i++) {
        if (tester[s2[i]]) {
            tester[s2[i]]--;
        } else {
            break;
        }
    }
    if (i == len) is_ana = 1;
    return is_ana;
}

int main()
{
    char s1[] = "skooby dooby dod";
    char s2[] = "skooby dooby doo";
    printf("'%s' %s an anagram of '%s'\n", s1, (is_anagram(s1, s2)? "is" : "is not"), s2);
}
