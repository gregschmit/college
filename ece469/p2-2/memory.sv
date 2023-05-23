
module memory(input logic clk, we,
              input logic [7:0] addr, wd,
              output logic [7:0] rd);

  logic [7:0] RAM [255:0];

  assign rd = RAM[addr];

  always_ff @(posedge clk)
    if (we) RAM[addr] <= wd;
endmodule
