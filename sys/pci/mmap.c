#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/pci.h>
#include <sys/io.h>
#include <sys/mman.h>

/*
 *
 * www.pcisig.com/reflector/msg04214.html
 *
[ 2076.272552] pci_hdr.ID      [00]    0x06251b21
[ 2076.272552] pci_hdr.CMD     [04]    0x0006
[ 2076.272553] pci_hdr.STS     [06]    0x0010
[ 2076.272554] pci_hdr.RID     [08]    0x01
[ 2076.272555] pci_hdr.CC.PI   [09]    0x06
[ 2076.272555] pci_hdr.CC.SCC  [09]    0x01
[ 2076.272556] pci_hdr.CC.BCC  [09]    0x10
[ 2076.272557] pci_hdr.CLS     [0C]    0x00
[ 2076.272558] pci_hdr.MLT     [0D]    0x00
[ 2076.272558] pci_hdr.HTYPE   [0E]    0x00
[ 2076.272559] pci_hdr.BIST    [0F]    0x00
[ 2076.272560] pci_hdr.BARS[i] [10]    0x00000000
[ 2076.272560] pci_hdr.BARS[i] [10]    0x00000000
[ 2076.272561] pci_hdr.BARS[i] [10]    0x00000000
[ 2076.272562] pci_hdr.BARS[i] [10]    0x00000000
[ 2076.272563] pci_hdr.BARS[i] [10]    0xe1a80000
[ 2076.272563] pci_hdr.ABAR    [24]    0x00000000
[ 2076.272564] pci_hdr.SS      [2C]    0x10601b21
[ 2076.272565] pci_hdr.EROM    [30]    0xe1a00000
[ 2076.272566] pci_hdr.CAP     [34]    0x50
[ 2076.272566] pci_hdr.INTR    [3C]    0x0000
[ 2076.272567] pci_hdr.MGNT    [3E]    0x00
[ 2076.272568] pci_hdr.MLAT    [3F]    0x00
[ 2076.272568] 
[ 2076.272569] dumping abar...
[ 2076.272576] abar.CAP:       [00]    0xeb369f2b
[ 2076.272577] abar.GHC:       [04]    0x80000000
[ 2076.272578] abar.IS:        [08]    0x00000000
[ 2076.272579] abar.PI:        [0C]    0x00000ff3
[ 2076.272579] abar.VS:        [10]    0x00010301
[ 2076.272580] abar.CCC_CTL:   [14]    0x00000000
[ 2076.272581] abar.CCC_PORTS: [18]    0x00000000
[ 2076.272582] abar.EM_LOC:    [1C]    0x00000000
[ 2076.272582] abar.EM_CTL:    [20]    0x00000000
[ 2076.272583] abar.CAP2:      [24]    0x00000000
[ 2076.272584] abar.BOHC:      [28]    0x00000000
 *
 *
 *
 *
 */

int main(int argc, char *argv[])
{
    int bus_num, dev_num, func_num;

    char *ptr_to_pci_mem;
    struct pci_access *all_devices;
    struct pci_dev *pci_device_config_space;
    unsigned int pci_mem_addr, pci_io_addr;
    
    int fd;
#if 1
    if (argc != 4) {
        printf("yo need input parms\n");
        return -1;
    } else {
        bus_num = atoi(argv[1]);
        dev_num = atoi(argv[2]);
        func_num = atoi(argv[3]);
    }
#endif
    if (iopl(3)) {
        printf("can't get IO perms (run as root)\n");
        return -1;
    }

    all_devices = pci_alloc();
    pci_init(all_devices);
    pci_scan_bus(all_devices);


    //pci_device_config_space = pci_get_device(0x1b21, 0x0625, NULL);
    pci_device_config_space = pci_get_dev(all_devices, 0, bus_num, dev_num, func_num);
 
    /* assuming BAR0 is mem type */
    pci_mem_addr = pci_read_long(pci_device_config_space, 0x24) & PCI_BASE_ADDRESS_MEM_MASK;

    /* open memory */
    fd = open("/dev/mem", O_RDWR);

    ptr_to_pci_mem = (char *) mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)pci_mem_addr);

    printf("pci addr:       %x\n", pci_mem_addr);
    printf("mem ptr:        %p\n", ptr_to_pci_mem);
    printf("pci[00]:        %lx\n", *(ptr_to_pci_mem + 0x00));
    printf("pci[04]:        %lx\n", *(ptr_to_pci_mem + 0x01));
    printf("pci[08]:        %lx\n", *(ptr_to_pci_mem + 0x02));
    printf("pci[0C]:        %lx\n", *(ptr_to_pci_mem + 0x03));
    printf("pci[10]:        %lx\n", *(ptr_to_pci_mem + 0x10));
    printf("pci[14]:        %lx\n", *(ptr_to_pci_mem + 0x14));

    munmap(ptr_to_pci_mem, 4096);

    close(fd);

    return 0;
}

