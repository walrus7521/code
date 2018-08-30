module test_traffic_lights;
  wire red;
  wire yellow;
  wire green;
  
  reg clk,rst;
  reg [2:0] timer;
  reg [3:0] state;
  reg [3:0] next_state;
  
  parameter RED=4'b0000;
  parameter YELLOW_1=4'b0001;
  parameter YELLOW_2=4'b0010;
  parameter GREEN=4'b0100;
  
  traffic tl(.red(red), .yellow(yellow), .green(green), .clk(clk), .rst(rst));
  
  initial begin    
    $monitor("At time %t, value = %h (%0d)", $time, clk, clk);
    rst=0;
    state=RED;
    
    #400 $finish;
    
  end
  
  always #5 clk=~clk;
  always #1 begin
    $monitor("monitor a:%h b:%h @ %0t", clk, rst, $time);
  end
endmodule
