#include <map>
#include <string>
#include <vector>

class Option;

class OptionParser
{
  public:
    OptionParser(const std::string& usage, const std::string& description);
    ~OptionParser();
    void add(const std::string& name, std::string& value, const std::string& description = std::string());
    void add(const std::string& name, int& value, const std::string& description = std::string());
    void add(const std::string& name, bool& value, const std::string& description = std::string());
    void add(const std::string& name, std::vector<std::string>& value, const std::string& description = std::string());
    bool parse(int argc, char** argv);
    void error(const std::string& message);
    std::vector<std::string>& getArguments();
  private:
    typedef std::vector<Option*> Options;

    const std::string summary;
    const std::string description;
    bool help;
    Options options;
    std::vector<std::string> arguments;

    void add(Option*);
    Option* getOption(const std::string& argument);
};

