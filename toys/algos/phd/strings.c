#include <stdio.h>
#include <string.h>

int match(char *pattern, char *string)
/*
 * return position of the 1st occurence of pattern p
 * in the string, and -1 if not found.
 */
{
    int i, j;
    int plen, tlen;

    plen = strlen(pattern);
    tlen = strlen(string);

    for (i = 0; i <= (tlen-plen); ++i) {
        j = 0;
        while ((j < plen) && (string[i+j] == pattern[j]))
            ++j;
        if (j == plen) return (i);
    }
    return (-1);
}


int palindrome(char *s)
{
    int len = strlen(s);
    int n = len-1;
    int i;
    for (i = 0; i < len/2; i++, n--) {
        if (s[i] != s[n]) {
            return 0;
        }
    }
    return 1;
}

#if 0
def anagram(s1, s2):
    ascii = [0 for x in range(256)] # hash of ascii
    p1 = 0
    p2 = 0
    if (len(s1) != len(s2)):
        return False
    for i in range(0,len(s1)): # register asciis from s1
        ascii[ord(s1[i])] = ascii[ord(s1[i])] + 1
    for i in range(0,len(s2)):
        if (ascii[ord(s2[i])] == 0): # if ascii from s2 not registered fail 
            return False
        ascii[ord(s2[i])] = ascii[ord(s2[i])] - 1 # unregister 1 s2
    for i in range(0,256):
        if (ascii[i] != 0): # check for any still registered
            return False    # if so,fail
    return True
#endif

int main()
{
    int f;
    char data[]  = "sledbobber\0";
    char data2[] = "sleddels";
    
    //f = match("bob", data);
    //if (f != -1) printf("found match at %d -> %s\n", f, &data[f]);

    printf("is pal %d\n", palindrome(data2));

}

