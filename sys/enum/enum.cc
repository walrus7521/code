#include <fstream>
#include <iostream>

struct Mount {
    std::string device;
    std::string destination;
    std::string fstype;
    std::string options;
    int dump;
    int pass;
};

std::ostream& operator<<(std::ostream& stream, const Mount& mount) {
    return stream << mount.fstype \
	<<" device \""<<mount.device<<"\", mounted on \"" \
        <<mount.destination<<"\". Options: "<<mount.options \
        <<". Dump:"<<mount.dump<<" Pass:"<<mount.pass;
}

void list() {
    system("cat sys/block > sysblock.tmp");
}

int main() {
    std::ifstream mountInfo("/proc/mounts");

    while( !mountInfo.eof() ) {
        Mount each;
        mountInfo >> each.device >> each.destination >> each.fstype >> each.options >> each.dump >> each.pass;
        if( each.device != "" )
            std::cout << each << std::endl;
    }

    return 0;
}
