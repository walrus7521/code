///////////////////////////////////////////////////////
//
// 2-input bus mux
//
//
///////////////////////////////////////////////////////

module std_mux
    // Port list
            (
                // Inputs
                in_1,
                in_2,
                in_3,
                // Outputs
                out_1,
            );

    // Port I/O declarations

    input   [3:0]   in_1;
    input   [3:0]   in_2;
    input           in_3;

    output  [3:0]   out_1;

    // -------------- Design implementation -----------

    assign out_1 = in_3_bus ? in_1 : in_2;

endmodule

