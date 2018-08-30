//#define _POSIX_C_SOURCE
#include <regex.h>
#include <stdio.h>

int main()
{
    int r, e;
    char buf[256];
    char proc[] = "create_user";

    regex_t regex;
    char *source = "johnnydoe@cloudnine.com";
    //const char *reg_exp2 = "\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\b";
    const char *reg_exp2 = ".*doe.*";

    r = regcomp(&regex,reg_exp2,REG_EXTENDED);
    if (r) {
        printf("error regcomp...\n");
    } else {
        printf("success regcomp...\n");
    }

    r = regexec(&regex,source,0,NULL,0); // source email
    if(!r) {
        printf("got a match dawg...\n");
         e = 0;
    } else 
    if(r == 1) {
        printf("REGEX MATCH:Fail:%s\n",proc);
        e = 1;
    } else {
        regerror(r,&regex,buf,100);
        printf("REGEX MATCH:Fail:%s:%s\n",proc,buf);
        e = 1;
    }

    regfree(&regex);
}

