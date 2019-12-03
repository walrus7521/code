///////////////////////////////////////////////////////
//
// Bus Breakout
//
//
///////////////////////////////////////////////////////

module bus_breakout
            (
                // Inputs
                in_1,
                in_2,
                // Outputs
                out_1,
            );

    // Port definitions
    input   [3:0]   in_1;
    input   [3:0]   in_2;
    output  [5:0]   out_1;

    // -------------- Design implementation -----------

    // concatenation
    assign out_1 = { in_2[3:2],
                     (in_1[3] & in_2[1]),
                     (in_1[2] & in_2[0]),
                     in_1(1:0)
                   };

endmodule

