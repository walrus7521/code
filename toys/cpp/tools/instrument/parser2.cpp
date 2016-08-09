#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "structs.h"

using namespace std;

typedef uint8_t crc;
crc crcTable[256];
#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))
#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */

void
crcInit(void)
{
    crc  remainder;
    /* Compute the remainder of each possible dividend.
     */
    for (int dividend = 0; dividend < 256; ++dividend) {
        /* Start with the dividend followed by zeros.
         */
        remainder = dividend << (WIDTH - 8);
        /* Perform modulo-2 division, a bit at a time.
         */
        for (uint8_t bit = 8; bit > 0; --bit) {
            /* Try to divide the current data bit.
             */			
            if (remainder & TOPBIT) {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            } else {
                remainder = (remainder << 1);
            }
        }
        /* Store the result into the table.
         */
        crcTable[dividend] = remainder;
    }
}

crc
//crcFast(uint8_t const message[], int nBytes)
crcFast(char *message, int nBytes)
{
    uint8_t data;
    crc remainder = 0;
    /* Divide the message by the polynomial, a byte at a time.
     */
    for (int byte = 0; byte < nBytes; ++byte) {
        data = message[byte] ^ (remainder >> (WIDTH - 8));
        remainder = crcTable[data] ^ (remainder << 8);
    }
    /* The final remainder is the CRC.
     */
    return (remainder);

}



class Parser_Alias
{
public:
    virtual ~Parser_Alias(){}
    virtual void Parse_Packet(void *packet) = 0;
protected:
    Parser_Alias(){}
};

template <class Data_Type> class Parser : public Parser_Alias {
public:
    Parser(string name) : pname(name){}
    ~Parser(){}
    void Parse_Packet(void * pkt) {
        Data_Type *p = (Data_Type *) pkt;
        body_type_1 *b = (body_type_1 *) pkt;
        cout << "Parser received packet - id: " << b->id << endl;
    }
private:
    string pname;
};

class Reader {
public:
    Reader(string name) : input_file_name(name), bytes_read(0){}
    ~Reader(){}
    void AddParser(int tag, Parser_Alias *parser_alias) {
        parsers.push_back(std::make_pair(tag, parser_alias));
    }
    void Read() {
        input_file_stream.open(input_file_name.c_str(), std::ifstream::in | std::ifstream::binary);
        std::cout << std::endl << "Parsing file " << input_file_name << std::endl;
        std::istream::pos_type file_size = Get_File_Size(input_file_stream);
        std::cout << std::endl << "size file " << file_size << std::endl;
        while (input_file_stream)
        {
            int bytes_to_read = sizeof(common_header); // just read the header
            char * hdr_buffer = new char[bytes_to_read];
            // Read from the file into our temp buffer.
            input_file_stream.read(hdr_buffer, bytes_to_read);
            //cout << hdr_buffer << endl;
            // Get the actual number of bytes read (may be different from
            // the number of bytes requested, e.g. we are at the end of the file).
            int bytes_read = static_cast<int>(input_file_stream.gcount());
            //std::cout << "bytes read " << bytes_read << std::endl;
            // we need to get the header to determine the tag and size of payload
            common_header *h = (common_header *) hdr_buffer;
            //cout << "received packet - tag: " << h->tag << " , size: " << h->size << endl;
            bytes_to_read = h->size;
            char * payload_buffer = new char[bytes_to_read];
            input_file_stream.read(payload_buffer, bytes_to_read);
            crc c = crcFast(payload_buffer, h->size);
            printf("parsed crc: %x\n", c);
            if (c == h->crc) {
                cout << "crc's match" << endl;
            } else {
                cout << "crc's don't match" << endl;
            }
            // Loop through the parsers and find the right one for this packet.
            for (int i = 0; i < parsers.size(); ++i) {
                if (parsers[i].first == h->tag) {
                    // Let this parser parse this packet.
                    parsers[i].second->Parse_Packet(payload_buffer);
                }
            }
            delete[] hdr_buffer;
            delete[] payload_buffer;
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
    std::vector<std::pair<int, Parser_Alias *> > parsers;    
    std::string input_file_name;
    int bytes_read;
    std::ifstream input_file_stream;
};

// a little factory
template<typename T>
Parser_Alias *CreateParser2(const string& filename) {
    Parser<T> *parser = new Parser<T>(filename);
    return parser;
}

int main()
{
    crcInit();
    string filename = "file.dat";
    Reader reader(filename);
    Parser_Alias *parser = CreateParser2<packet_type_1>(filename);
    reader.AddParser(PACKET_TYPE_1, parser);
    reader.Read();
    delete parser;
}
