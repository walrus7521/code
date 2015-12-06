`timescale 10ns/1ns
module RS_FF(Q, Qbar, R, S);
    output Q, Qbar;
    input R, S;

    nand #1 (Q, R, Qbar);
    nand #1 (Qbar, S, Q);
endmodule


module Test;
    reg TS, TR;
    wire TQ, TQb;

    RS_FF NSTA (.Q(TQ), .S(TS), .R(TR), .Qbar(TQb));

    initial 
        begin
            TR = 0;
            TS = 0;
            #5 TS = 1;
            #5 TS = 0;
            TR = 1;
            #5 TS = 1;
            TR = 0;
            #5 TS = 0;
            #5 TR = 1;
        end

    initial
         $dumpfile("simple.vcd");
         $monitor ("At time %t,", $time,
                " TR=%b, TS=%b, TQ=%b, TQb=%b", TR, TS, TQ, TQb);
endmodule

