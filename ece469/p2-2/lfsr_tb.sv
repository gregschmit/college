
`include "lfsr.sv"

module lfsr_testbench();

  // dict
  int i;
  int fails = 0;
  logic clk, run, seed, init_tap;
  logic [6:0] taps;
  logic [7:0] seed_data;
  logic [7:0] q;
  lfsr dut(clk, run, seed, init_tap, seed_data, taps, q);

  always begin
    clk <= 1; # 5; clk <= 0; # 5;
  end

  logic [17:0] data [4] = {
    {3'b011, 8'b11111111, 7'b0100101},
    {3'b100, 8'b11111111, 7'b0100101},
    {3'b100, 8'b11111111, 7'b0100101},
    {3'b001, 8'b11100111, 7'b0111101}
  };
  always @(negedge clk) begin
    if (i < 5) begin
      if (i == 4) $stop;
      {run, seed, init_tap, seed_data, taps} = data[i];
    end
    i++;
  end
endmodule
