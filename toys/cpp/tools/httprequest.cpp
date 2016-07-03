#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

// g++ -lcurl httprequest.cpp

class CURLplusplus
{
private:
    CURL* curl;
    stringstream ss;
    long http_code;
public:
    CURLplusplus()
            : curl(curl_easy_init())
    , http_code(0)
    {

    }
    ~CURLplusplus()
    {
        if (curl) curl_easy_cleanup(curl);
    }
    std::string Get(const std::string& url)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        ss.str("");
        http_code = 0;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            throw std::runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        return ss.str();
    }
    long GetHttpCode()
    {
        return http_code;
    }
private:
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
    }
    size_t Write(void *buffer, size_t size, size_t nmemb)
    {
        ss.write((const char*)buffer,size*nmemb);
        return size*nmemb;
    }
};


int main()
{
    unsigned counter = 0;

    std::regex url_regex (
        //R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
        R"(www\..*\.com)",
        std::regex::extended
      );
    std::smatch url_match_result;

    CURLplusplus client;
    string x = client.Get("http://google.com");
    string y = client.Get("http://yahoo.com");    

    if (std::regex_match(y, url_match_result, url_regex)) {
        for (const auto& res : url_match_result) {
            std::cout << counter++ << ": " << res << std::endl;
        }
    } else {
        std::cerr << "No urls." << std::endl;
    }

    //cout << x << endl;
    //string y = client.Get("http://yahoo.com");    
    //cout << y << endl;

}

