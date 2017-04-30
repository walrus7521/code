#include <tuple>
#include <string>
#include <vector>

typedef std::tuple<unsigned long, unsigned short, std::string> field_type;

class Blob {
    public:
        Blob(const std::vector<field_type>& fmt) {
            fields = fmt;
        }
        std::vector<field_type> fields;
    private:
        int nfields;
};

