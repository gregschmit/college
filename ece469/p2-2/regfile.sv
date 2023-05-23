
module regfile(input logic clk, wr_e, [7:0] wd,
               output logic [7:0] r_addr);

  logic [7:0] r;
  assign r_addr = r;

  always_ff @(posedge clk) begin
    if (wr_e) r <= wd;
  end
endmodule
