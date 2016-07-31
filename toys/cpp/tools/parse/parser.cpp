#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "structs.h"

// see FileReader.h
// and Parser.h
using namespace std;

class Parser {
public:
    Parser(string name) : pname(name) {}
    ~Parser(){}
    //virtual void Parse_Packet(const void * packet)
    //{
    //    Parse_Packet(reinterpret_cast<const Data_Type *>(packet));
    //}
    //void Parse_Packet(const Data_Type * packet)
    void Parse_Packet(char * buffer) {
        packet *p = (packet *) buffer;
        cout << "Parser received packet - tag: " << p->h.tag << " , id: " << p->b.id << endl;
    }

private:
    string pname;
};

class Reader {
public:
    Reader(string name) : input_file_name(name), bytes_read(0) {}
    ~Reader(){}
    void AddParser(int tag, Parser *parser) {
        parsers.push_back(std::make_pair(tag, parser));
    }
    void Read() {
        input_file_stream.open(input_file_name.c_str(), std::ifstream::in | std::ifstream::binary);
        // We are starting...
        std::cout << std::endl << "Parsing file " << input_file_name << std::endl;
        std::istream::pos_type file_size = Get_File_Size(input_file_stream);
        std::cout << std::endl << "size file " << file_size << std::endl;
        while (input_file_stream)
        {
            int bytes_to_read = 256;
            char * temp_buffer = new char[bytes_to_read];
            // Read from the file into our temp buffer.
            input_file_stream.read(temp_buffer, bytes_to_read);
            //cout << temp_buffer << endl;
            // Get the actual number of bytes read (may be different from
            // the number of bytes requested, e.g. we are at the end of the file).
            int bytes_read = static_cast<int>(input_file_stream.gcount());
            std::cout << "bytes read " << bytes_read << std::endl;
            // we need to get the header to determine the tag
            packet *p = (packet *) temp_buffer;
            //cout << "received packet - tag: " << p->h.tag << " , id: " << p->b.id << endl;
            //int tag = 77; // fake it for now, need to get this from the packet header
            // Loop through the parsers and find the right one for this packet.
            for (int i = 0; i < parsers.size(); ++i) {
                if (parsers[i].first == p->h.tag) {
                    // Let this parser parse this packet.
                    parsers[i].second->Parse_Packet(temp_buffer);
                }
            }
            delete[] temp_buffer;
            this->bytes_read += bytes_read;
        }
        // Close the file.
        input_file_stream.close();
        input_file_stream.clear();
    }

    static std::istream::pos_type Get_File_Size(std::istream & stream)
    {
        // Save the current position so we can go back later.
        std::istream::pos_type current_position = stream.tellg();
        // Go to the end of the file.
        stream.seekg(0, stream.end);
        // Get the length of the file.
        std::istream::pos_type length = stream.tellg();
        // Go back to where we started.
        stream.seekg(current_position);
        return length;
    }
private:
    std::vector<std::pair<int, Parser *> > parsers;    
    std::string input_file_name;
    int bytes_read;
    std::ifstream input_file_stream;
};

int main()
{
    string filename = "file.dat";
    Reader reader(filename);
    Parser *parser = new Parser(filename);
    reader.AddParser(77, parser);
    reader.Read();
    delete parser;
}
