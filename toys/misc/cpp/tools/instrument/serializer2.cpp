#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
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

class Serializer_Alias
{
public:
    virtual ~Serializer_Alias(){}
    virtual void Serialize_Packet(std::ofstream& os, void *packet) = 0;
protected:
    Serializer_Alias(){}
};

template <class Data_Type> class Serializer : public Serializer_Alias {
public:
    Serializer(string name) : output_file_name(name) {}
    ~Serializer(){}
    void Serialize_Packet(std::ofstream& os, void * packet) {
        Data_Type *t = (Data_Type *) packet;
        cout << hex << t->h.tag << " : " << t->b.id << endl;
        int bytes_to_write = sizeof(packet_type_1);
        while (bytes_to_write)
        {
            auto i = os.tellp();
            os.write((char *) t, sizeof(packet_type_1));
            auto j = os.tellp();
            int bytes_written = j - i;
            bytes_to_write -= bytes_written;
            std::cout << "bytes written " << bytes_written << std::endl;
            this->bytes_written = bytes_written;
        }
    }
private:
    string output_file_name;
    int bytes_written;

};

class Writer {
public:
    Writer(string name) : output_file_name(name), bytes_written(0) {}
    ~Writer(){}
    void AddSerializer(int tag, Serializer_Alias *serializer) {
        serializers.push_back(std::make_pair(tag, serializer));
    }

    void Write(int tag) {
        output_file_stream.open(output_file_name.c_str(), std::ofstream::out | std::ofstream::binary);
        for (int i = 0; i < serializers.size(); ++i) {
            if (serializers[i].first == tag) {
                for (int j = 0; j < queue.size(); ++j) {
                    serializers[i].second->Serialize_Packet(output_file_stream, queue[j]);
                    //packet_type_1 *p = (packet_type_1 *) queue[i];
                    //cout << hex << ' ' << p->h.tag << endl;
                }
            }
        }
        output_file_stream.close();
        output_file_stream.clear();
    }
    void Queue(vector<void *> pv) {
        queue = pv;
    }

    void Show() {
        vector<void *>::iterator it;
        for (it = queue.begin() ; it != queue.end(); ++it) {
            packet_type_1 *p = (packet_type_1 *) *it;
            cout << hex << ' ' << p->h.tag << endl;
        }
    }

private:
    std::vector<std::pair<int, Serializer_Alias *> > serializers;    
    std::vector<void *> queue;
    string output_file_name;
    int bytes_written;
    std::ofstream output_file_stream;
};


int main()
{
    string filename = "file.dat";
    crcInit();
    Writer writer(filename);
    Serializer<packet_type_1> *serializer = new Serializer<packet_type_1>(filename);
    writer.AddSerializer(PACKET_TYPE_1, serializer);

    // generate packets
    vector<packet_type_1 *> pp;
    for (int i = 0; i < 4; ++i) {
        packet_type_1 *p = (packet_type_1 *) malloc(sizeof(packet_type_1)); // header is common_header
        p->h.tag = PACKET_TYPE_1;
        p->h.size = sizeof(body_type_1);
        p->b.id = i;
        crc c = crcFast((char *) &p->b, sizeof(body_type_1));
        p->h.crc = c;
        printf("serialized crc: %x\n", c);
        pp.push_back(p);
    }

    // queue packets
    vector<void *> pv(pp.begin(), pp.end());
    writer.Queue(pv);

    //writer.Show();
    writer.Write(PACKET_TYPE_1);
    delete serializer;
}

