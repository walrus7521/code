#include <iostream>
#include <string>
#include <regex>

typedef unsigned long long u64;
typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

class i_transport {
    public:
        virtual ~i_transport() { }
        virtual u32 config_admin_queue_pair(void *dev, u32 depth, u32 intrpt_type) = 0;
        virtual u32 allocate_io_queues(void *dev, u32 intrpt_type, u32 num_queues) = 0;
        virtual u32 create_io_queues(void *dev, u32 cq, u32 sq, u32 cpu, u32 depth, u32 elem_length, u32 coalesce_time, u32 coalesce_count) = 0;
        virtual u32 destroy_io_queues(void *dev, u32 cpu) = 0;
        virtual u32 enqueue_cmd(void *dev, u32 queue_num, u32 slot, u32 slot_type, u32 tag_id, u32 cmd_len, void *cmd, u32 ring_now, 
            u8 data_transfer_direction, u64 dma_segment_length, u8 dma_buffer_alignment, u32 dma_buffer_overlap_length, u64 buffer_size, void *buffer) = 0;
        virtual u32 dequeue_cmd(void *dev, u32 status, u32 queue_num, u32 slot, u32 cmdid, u32 tag_id, void *data_out, u64 *data_out_len, u16 offset, u64 bit_mask) = 0;
        virtual u32 ring_doorbell(void *dev, u32 queue_num, u32 num_cmds, u32 ring_type, u32 safe) = 0;
        virtual u32 reset_controller(void *dev) = 0;
        virtual u32 cleanup(void *dev) = 0;
};

class base_transport : virtual public i_transport {};

class ahci_transport : public base_transport {
    public:
        ahci_transport() { std::cout << "ahci_transport(): " << std::endl; }
        ~ahci_transport() { std::cout << "~ahci_transport() " << std::endl; }
        u32 cleanup() { 
            base_transport::cleanup(nullptr);
            std::cout << "ahci_transport::cleanup: " << std::endl; 
            return 0;
        }

        u32 config_admin_queue_pair(void *dev, u32 depth, u32 intrpt_type) { return 0; }
        u32 allocate_io_queues(void *dev, u32 intrpt_type, u32 num_queues) { return 0; }
        u32 create_io_queues(void *dev, u32 cq, u32 sq, u32 cpu, u32 depth, u32 elem_length, u32 coalesce_time, u32 coalesce_count) { return 0; }
        u32 destroy_io_queues(void *dev, u32 cpu) { return 0; }
        u32 enqueue_cmd(void *dev, u32 queue_num, u32 slot, u32 slot_type, u32 tag_id, u32 cmd_len, void *cmd, u32 ring_now, 
            u8 data_transfer_direction, u64 dma_segment_length, u8 dma_buffer_alignment, u32 dma_buffer_overlap_length, u64 buffer_size, void *buffer) { return 0; }
        u32 dequeue_cmd(void *dev, u32 status, u32 queue_num, u32 slot, u32 cmdid, u32 tag_id, void *data_out, u64 *data_out_len, u16 offset, u64 bit_mask) { return 0; }
        u32 ring_doorbell(void *dev, u32 queue_num, u32 num_cmds, u32 ring_type, u32 safe) { return 0; }
        u32 reset_controller(void *dev) { return 0; }
        u32 cleanup(void *dev) { std::cout << "ahci_transport::cleanup: " << std::endl; return 0; }
    private:
        void *dev;
};

class hvt {
    public:
        hvt() {};
        //hvt(base_transport *transport) {
        hvt(i_transport *transport) {
            this->transport = transport;
        }
        //int set_transport(base_transport *transport) {
        int set_transport(i_transport *transport) {
            this->transport = transport;
            return 0;
        }
        u32 do_this_thing() {
            std::cout << "hvt::do_this_thing" << std::endl;
            transport->cleanup(nullptr);
            return 0;
        }
    private:
        //base_transport *transport;
        i_transport *transport;
};

int main ()
{
    ahci_transport *ahci = new ahci_transport();
    hvt *t = new hvt();

    t->set_transport(ahci);
    t->do_this_thing();

    std::cout << "puma: " << std::endl;
    delete ahci;
    return 0;
} 
