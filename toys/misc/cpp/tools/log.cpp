/**
* Logger.h
*
* Definition of a singleton logger class, implemented with static methods.
*/
#include <iostream>
#include <fstream>
#include <vector>
class Logger
{
public:
    static const std::string kLogLevelDebug;
    static const std::string kLogLevelInfo;
    static const std::string kLogLevelError;
    // Logs a single message at the given log level
    static void log(const std::string& inMessage, const std::string& inLogLevel);
    // Logs a vector of messages at the given log level
    static void log(const std::vector<std::string>& inMessages, const std::string& inLogLevel);
    // Closes the log file
    static void teardown();
protected:
    static void init();
    static const char* const kLogFileName;
    static bool sInitialized;
    static std::ofstream sOutputStream;
private:
    Logger() {}
};
/**
* Logger.cpp
*
* Implementation of a singleton logger class.
*/
using namespace std;
const string Logger::kLogLevelDebug = "DEBUG";
const string Logger::kLogLevelInfo = "INFO";
const string Logger::kLogLevelError = "ERROR";
const char* const Logger::kLogFileName = "log.out";
bool Logger::sInitialized = false;
ofstream Logger::sOutputStream;
void Logger::log(const string& inMessage, const string& inLogLevel)
{
    std::cout << "log1" << std::endl;
    if (!sInitialized) {
        init();
    }
    // print the message and flush the stream with endl
    sOutputStream << inLogLevel << ": " << inMessage << endl;
}

void Logger::log(const vector<string>& inMessages, const string& inLogLevel)
{
    std::cout << "log2" << std::endl;
    for (size_t i = 0; i < inMessages.size(); i++) {
        log(inMessages[i], inLogLevel);
    }
}
void Logger::teardown()
{
    if (sInitialized) {
        sOutputStream.close();
        sInitialized = false;
    }
}
void Logger::init()
{
    std::cout << "init" << std::endl;
    if (!sInitialized) {
        std::cout << "init'ing" << std::endl;
        sOutputStream.open(kLogFileName, ios_base::app);
        if (!sOutputStream.good()) {
            cerr << "Unable to initialize the Logger!" << endl;
            return;
        }
        sInitialized = true;
    }
}

int main()
{
    Logger::log("message1", "INFO");
    Logger::log("message2", "DEBUG");
}
