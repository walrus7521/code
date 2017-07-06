#include <stdio.h>
#include <stdlib.h>

// http://codeandlife.com/2012/04/02/simple-fat-and-sd-tutorial-part-1/

typedef struct {
    unsigned char jmp[3];
    char oem[8];
    unsigned short sector_size;
    unsigned char sectors_per_cluster;
    unsigned short reserved_sectors;
    unsigned char number_of_fats;
    unsigned short root_dir_entries;
    unsigned short total_sectors_short; // if zero, later field is used
    unsigned char media_descriptor;
    unsigned short fat_size_sectors;
    unsigned short sectors_per_track;
    unsigned short number_of_heads;
    unsigned long hidden_sectors;
    unsigned long total_sectors_long;
    
    unsigned char drive_number;
    unsigned char current_head;
    unsigned char boot_signature;
    unsigned long volume_id;
    char volume_label[11];
    char fs_type[8];
    char boot_code[448];
    unsigned short boot_sector_signature;
} __attribute((packed)) Fat16BootSector;

typedef struct {
    unsigned char first_byte;
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    unsigned long start_sector;
    unsigned long length_sectors;
} __attribute((packed)) PartitionTable;

void scan(FILE * in)
{
    int i;
    PartitionTable pt[4];
    Fat16BootSector bs;
    
    fseek(in, 0x1BE, SEEK_SET); // go to partition table start
    fread(pt, sizeof(PartitionTable), 4, in); // read all four entries
    
    for(i=0; i<4; i++) {
        printf("Partition %d, type %02X\n", i, pt[i].partition_type);
        printf("  Start sector %08X, %d sectors long\n", 
                pt[i].start_sector, pt[i].length_sectors);

        fseek(in, 512 * pt[i].start_sector, SEEK_SET);
        fread(&bs, sizeof(Fat16BootSector), 1, in);
    }


}

int main() {
    FILE * in = fopen("test.img", "rb");
    unsigned int i, start_sector, length_sectors;
    
    fseek(in, 0x1BE, SEEK_SET); // go to partition table start
    
    for(i = 0; i < 4; i++) { // read all four entries
        printf("Partition entry %d: First byte %02X\n", i, fgetc(in));
        printf("  Partition start in CHS: %02X:%02X:%02X\n", fgetc(in), fgetc(in), fgetc(in));
        printf("  Partition type %02X\n", fgetc(in));
        printf("  Partition end in CHS: %02X:%02X:%02X\n", fgetc(in), fgetc(in), fgetc(in));
        
        fread(&start_sector, 4, 1, in);
        fread(&length_sectors, 4, 1, in);
        printf("  Relative LBA address %08X, %d sectors long\n", start_sector, length_sectors);
    }
    
    scan(in);

    fclose(in);
    return 0;
}
