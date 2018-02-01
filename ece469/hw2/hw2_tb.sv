
`timescale 1ns/1ns

module testbench_ch1();

  logic [3:0] D;
  logic [3:0] Y;
  logic [1:0] Z;

  clear_highest_1 dut(D, Y, Z);

  initial begin
    int i;
    for (i=0; i<16; i++) begin
	    D = i; #10;
    end
  end
endmodule
