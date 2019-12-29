//-----------------------------------------------------
// stimulus
//
// http://www.referencedesigner.com/tutorials/verilog/verilog_09.php
//
// iverilog -ostimulus.vvp stimulus.v
// vvp stimulus.vvp
// VCD info: dumpfile dump.vcd opened for output.
//    At time                    0, x=0, y=0, z=0
//    At time                   20, x=1, y=0, z=0
//    At time                   40, x=1, y=1, z=0
//    At time                   60, x=1, y=0, z=0
//    At time                  100, x=1, y=1, z=1
//    ** VVP Stop(0) **
//    ** Flushing output streams.
//    ** Current simulation time is 200 ticks.
//    > cont
//    ** Continue **
//-----------------------------------------------------
module stimulus;

    reg x;
    reg y;
    reg z;

    initial begin
        $dumpvars(0, stimulus);
        x = 0;
        y = 0;
        z = 0;
        #20 x = 1;
        #20 y = 1;
        #20 y = 0;
        #20 x = 1;
        #20 z = 1;
        #100 $stop;
    end

    initial
        $monitor("At time %t, x=%d, y=%d, z=%d", $time, x, y, z);

endmodule // stimulus

