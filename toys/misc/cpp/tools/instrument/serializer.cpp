#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "structs.h"

using namespace std;

class Serializer {
public:
    Serializer(string name) : output_file_name(name) {}
    ~Serializer(){}
    void Serialize_Packet(char * packet) {
    }
private:
    string output_file_name;
};

class Writer {
public:
    Writer(string name) : output_file_name(name), bytes_written(0) {}
    ~Writer(){}
    void AddSerializer(int tag, Serializer *serializer) {
        serializers.push_back(std::make_pair(tag, serializer));
    }
    void Write() {
        output_file_stream.open(output_file_name.c_str(), std::ofstream::out | std::ofstream::binary);
        // We are starting...
        std::cout << std::endl << "Serializing packets " << output_file_name << std::endl;
        int bytes_to_write = sizeof(packet_type_1);
        packet_type_1 p; // header is common_header
        p.h.tag = PACKET_TYPE_1;
        p.b.id = 0x103;
        while (bytes_to_write)
        {
            // this should be done by the serializer
            auto i = output_file_stream.tellp();
            output_file_stream.write((char *) &p, sizeof(packet_type_1));
            auto j = output_file_stream.tellp();
            int bytes_written = j - i;
            bytes_to_write -= bytes_written;
            std::cout << "bytes written " << bytes_written << std::endl;
            this->bytes_written = bytes_written;
        }
        output_file_stream.close();
        output_file_stream.clear();
      }

private:
    std::vector<std::pair<int, Serializer *> > serializers;    
    string output_file_name;
    int bytes_written;
    std::ofstream output_file_stream;
};


int main()
{
     string filename = "file.dat";
     Writer writer(filename);
     Serializer *serializer = new Serializer(filename);
     writer.AddSerializer(77, serializer);
     writer.Write();
     delete serializer;
}

