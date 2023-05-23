`include "alu.sv"
module alu_testbench();

  logic [31:0] a;
  logic [31:0] b;
  logic [3:0] f;
  logic [31:0] y;  //actual y value
  logic [31:0] expected_y; //expected y value
  logic z;
  logic [3:0]expected_z;//expected zero value

  //change first bracket numbers to reflect size of line
  //change second bracket numbers to reflect the number of lines
  logic [103:0] testvector[20:0];
  integer num; // used for iterating through testvector
  alu dut(a,b,f[2:0],y,z); //please make sure I/Os are in correct order

  initial
  begin
  $readmemh("./alu.tv",testvector);
  for (num = 0; num <21;num = num + 1)
    begin

    {a,b,f,expected_y,expected_z} = testvector[num];#10;
    //use num + 1 since file lines start at 1
    $display("num=%d  a=%h b=%h f=%h",num+1,a,b,f);
    $display("exp_y=%h y=%h exp_z=%h z=%h",expected_y,y,expected_z,z);
    if (expected_y !=y | expected_z != z)
      $display("Incorrect y or z line:%d---------------",num+1);
    end
  end

endmodule
