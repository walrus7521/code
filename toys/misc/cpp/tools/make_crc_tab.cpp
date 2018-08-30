#include <iostream>
#include <iomanip>

void make_crc_table(unsigned long crcTable[])
{
    unsigned long POLYNOMIAL = 0xEDB88320;
    unsigned long remainder;
    unsigned char b = 0;
    do{
        // Start with the data byte
        remainder = b;
        for (unsigned long bit = 8; bit > 0; --bit)
        {
            if (remainder & 1)
                remainder = (remainder >> 1) ^ POLYNOMIAL;
            else
                remainder = (remainder >> 1);
        }
        crcTable[(size_t)b] = remainder;
    } while(0 != ++b);
}

unsigned long gen_crc(unsigned char *p, size_t n, unsigned long crcTable[])
{
    unsigned long crc = 0xfffffffful;
    size_t i;
    for(i = 0; i < n; i++)
        crc = crcTable[*p++ ^ (crc&0xff)] ^ (crc>>8);
    return(~crc);
}

int main()
{
    unsigned char buffer[256] = {0};
    unsigned long crcTable[256];
    unsigned long crc;
    make_crc_table(crcTable);
    // Print the CRC table
    for (size_t i = 0; i < 256; i++)
    {
        std::cout << std::setfill('0') << std::setw(8)
                  << std::hex << crcTable[i];
        if (i % 4 == 3)
            std::cout << std::endl;
        else
            std::cout << ", ";
    }
    crc = gen_crc(buffer, 256, crcTable);
    std::cout << "crc: " << crc << std::endl;

    return 0;
}

