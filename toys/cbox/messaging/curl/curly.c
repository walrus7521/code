#include <stdio.h>
#include <curl/curl.h>

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    printf("%s\n", buf);
    return size*nmemb; //tell curl how many bytes we handled
}

#define URL "https://www.intel.com/index.html"

int main()
{
    CURL *curl;
    CURLcode r;

    //char url[] = 
    //    "https://c-for-dummies.com/curl_test.txt";

    printf("libcurl version %s\n", LIBCURL_VERSION);

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();
    
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

}


