///////////////////////////////////////////////////////
//
// State machine
//
//
///////////////////////////////////////////////////////

module state_machine ( clk,
                       reset,
                       go,
                       kill,
                       done
                     );

    input   clk;
    input   reset;
    input   go;
    input   kill;
    output  done;

    reg [6:0]   count;

    // -------------- Design implementation -----------

    always @( posedge clk or posedge reset )
        begin
            if ( reset )
                out_1 <= 1'b0;
            else if ( clear == 1'b0 )
                out_1 <= 1'b0;
            else if ( enable )
                out_1 <= in_1;
        end

endmodule


