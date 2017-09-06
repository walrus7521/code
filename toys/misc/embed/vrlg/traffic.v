module traffic(red,yellow,green, clk,rst);
  output reg red,yellow,green;
  input clk,rst;
  
  reg [2:0] timer;
  reg [3:0] state;
  reg [3:0] next_state;
  
  parameter RED=4'b0000;
  parameter YELLOW_1=4'b0001;
  parameter YELLOW_2=4'b0010;
  parameter GREEN=4'b0100;
  
  
  always @(posedge clk) begin
    $monitor("homi a:%h b:%h @ %0t", clk, rst, $time);
    case(state)
      RED: begin
        if(timer<3'b101) begin
          next_state<=RED;
          timer<=timer+1;
        end
        else begin
          next_state<=YELLOW_1;
          timer<=0;
        end
      end
      
      YELLOW_1: begin
        if(timer<3'b001) begin
          next_state<=YELLOW_1;
          timer<=timer+1;
        end
        else begin
          next_state<=GREEN;
          timer<=0;
        end
      end
      
      GREEN: begin
        if(timer<3'b101) begin
          next_state<=GREEN;
          timer<=timer+1;
        end
        else begin
          next_state<=YELLOW_2;
          timer<=0;
        end
      end
      
      YELLOW_2: begin
        if(timer<3'b001) begin
          next_state<=YELLOW_2;
          timer<=timer+1;
        end
        else begin
          next_state<=RED;
          timer<=0;
        end
      end
      
      default: begin state<=RED; end
    endcase
  end
    
  always @(posedge clk) begin
    $monitor("wusup a:%h b:%h @ %0t", clk, rst, $time);
    if(rst==0) state<=next_state;
    else state<=RED;
  end
    
  always @(posedge clk) begin
    $monitor("dude a:%h b:%h @ %0t", clk, rst, $time);
    case(state)
      RED: 		begin red=1; yellow=0; green=0; end
      YELLOW_1: begin red=0; yellow=1; green=0; end
      YELLOW_2: begin red=0; yellow=1; green=0; end
      GREEN: 	begin red=0; yellow=0; green=1; end
      default:  begin red=1; yellow=0; green=0; end
    endcase
  end
  
endmodule

