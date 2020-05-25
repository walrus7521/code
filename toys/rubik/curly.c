#include <stdio.h>
#include <curl/curl.h>

// gcc curly.c -lcurl

int main()
{
    printf("libcurl version %s\n", curl_version());
    return 0;
}

