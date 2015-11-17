#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <scsi/sg.h> /* take care: fetches glibc's /usr/include/scsi/sg.h */
#include <inttypes.h>

/*
   exercises sg_io_hdr interface of the SCSI generic (sg) driver

*/

#define sg_debug printf
#define sg_error printf
#define INQ_REPLY_LEN 96
#define INQ_CMD_CODE 0x12
#define INQ_CMD_LEN 6

typedef struct _sg_device_t {
    char *sg_filename;
    int sg_fd;
    unsigned int sg_flags;
} sg_device_t;

typedef struct _sg_cmd_t {
    int                 code;
    int                 cdb_opcode;
    int                 cdb_sa;
    size_t              cdb_sz;
    size_t              sense_bufsz;
    int                 out_buf_needfree;
    size_t              out_bufsz;
    uint8_t             *out_buf;
    sg_io_hdr_t         io_hdr;
} sg_cmd_t;


int
sg_handle_error(sg_cmd_t *cmd)
{
    int k;
    unsigned char *sense_buffer;

    sense_buffer = cmd->io_hdr.sbp;
    if (cmd->io_hdr.sb_len_wr > 0) {
        printf("INQUIRY sense data: ");
        for (k = 0; k < cmd->io_hdr.sb_len_wr; ++k) {
            if ((k > 0) && (0 == (k % 10)))
                printf("\n  ");
            printf("0x%02x ", sense_buffer[k]);
        }
        printf("\n");
    }
    if (cmd->io_hdr.masked_status)
        printf("INQUIRY SCSI status=0x%x\n", cmd->io_hdr.status);
    if (cmd->io_hdr.host_status)
        printf("INQUIRY host_status=0x%x\n", cmd->io_hdr.host_status);
    if (cmd->io_hdr.driver_status)
        printf("INQUIRY driver_status=0x%x\n", cmd->io_hdr.driver_status);

    return 0;
}

void dump_inquiry(char *inq)
{
    char * p = (char *)inq;
    printf("Some of the INQUIRY command's response:\n");
    printf("    %.8s  %.16s  %.4s\n", p + 8, p + 16, p + 32);
}

int send_inquiry(sg_device_t *dev)
{
    int k, rc;
    sg_cmd_t cmd;

    unsigned char inqCmdBlk[INQ_CMD_LEN] =
                    {INQ_CMD_CODE, 0, 0, 0, INQ_REPLY_LEN, 0};
/* This is a "standard" SCSI INQUIRY command. It is standard because the
 * CMDDT and EVPD bits (in the second byte) are zero. All SCSI targets
 * should respond promptly to a standard INQUIRY */
    unsigned char inqBuff[INQ_REPLY_LEN];
    unsigned char sense_buffer[32];
    sg_io_hdr_t io_hdr;

    memset(&cmd.io_hdr, 0, sizeof(sg_io_hdr_t));
    cmd.io_hdr.interface_id = 'S';
    cmd.io_hdr.cmd_len = sizeof(inqCmdBlk);
    cmd.io_hdr.mx_sb_len = sizeof(sense_buffer);
    cmd.io_hdr.dxfer_direction = SG_DXFER_FROM_DEV;
    cmd.io_hdr.dxfer_len = INQ_REPLY_LEN;
    cmd.io_hdr.dxferp = inqBuff;
    cmd.io_hdr.cmdp = inqCmdBlk;
    cmd.io_hdr.sbp = sense_buffer;
    cmd.io_hdr.timeout = 20000;     /* 20000 millisecs == 20 seconds */
    /* cmd.io_hdr.flags = 0; */     /* take defaults: indirect IO, etc */
    /* cmd.io_hdr.pack_id = 0; */
    /* cmd.io_hdr.usr_ptr = NULL; */
    /* cmd.io_hdr.iovec_count = 0; */  /* memset takes care of this */

    rc = sg_cmd_exec(dev,&cmd);
    if (rc) {
        perror("sg_simple0: Inquiry SG_IO ioctl error");
        return 1;
    }

    if ((cmd.io_hdr.info & SG_INFO_OK_MASK) == SG_INFO_OK) {
        printf("INQUIRY duration=%u millisecs, resid=%d\n",
               cmd.io_hdr.duration, cmd.io_hdr.resid);
        dump_inquiry((char *) inqBuff);
    } else {
        sg_handle_error(&cmd);
    }
}

int sg_report_target_port_group(sg_device_t *dev)
{
    unsigned char rtpgCmdBlk[MAINTENANCE_IN_CMDLEN] =
                    {MAINTENANCE_IN_CMD, REPORT_TGT_PRT_GRP_SA,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char sense_b[SENSE_BUFF_LEN];

    rtpgCmdBlk[1] |= 0x20; // extended
  
    rtpgCmdBlk[6] = (mx_resp_len >> 24) & 0xff;
    rtpgCmdBlk[7] = (mx_resp_len >> 16) & 0xff;
    rtpgCmdBlk[8] = (mx_resp_len >> 8) & 0xff;
    rtpgCmdBlk[9] = mx_resp_len & 0xff;



}

int
sg_cmd_exec(sg_device_t *dev,
                sg_cmd_t *cmd)
{
    char msg[512];
    int n, ret;
    unsigned i = 0, j;

    /* Send the SG_IO command */
    ret = ioctl(dev->sg_fd, SG_IO, &cmd->io_hdr);
    if( ret != 0 ) {
        sg_error("%s: SG_IO ioctl failed %d (%s)",
                  dev->sg_filename,
                  errno,
                  strerror(errno));
        ret = -errno;
        goto out;
    }

out:

    return( ret );

}


int main(int argc, char * argv[])
{
    int k, rc;
    sg_device_t dev;

    if (2 != argc) {
        printf("Usage: 'sg_simple0 <sg_device>'\n");
        return 1;
    }
    if ((dev.sg_fd = open(argv[1], O_RDONLY)) < 0) {
    	/* most SCSI commands require the O_RDWR flag to be set */
        perror("error opening given file name");
        return 1;
    }

    /* verify we have a sg device by trying an ioctl */
    if ((ioctl(dev.sg_fd, SG_GET_VERSION_NUM, &k) < 0) || (k < 30000)) {
        printf("%s is not an sg device, or old sg driver\n", argv[1]);
        return 1;
    }

    rc = send_inquiry(&dev);

    close(dev.sg_fd);
    return 0;
}

