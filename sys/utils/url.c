#include <stdio.h>
#include <curl/curl.h>

/*
 * On Mac - brew install cURL
 *  gcc -lcurl url.c
 *
 */

int main(void)
{
    char *url = "http://www.microsoft.com";
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
