
module lfsr(input logic clk, run, seed, init_tap, [7:0] seed_data, [6:0] taps,
            output logic [7:0] q);

  logic [7:0] r;
  logic [6:0] t;

  int i = 0;
  always_ff @(posedge clk) begin
    if (seed) begin
      for (i=0; i<8; i++) begin
        r[i] = seed_data[i];
      end
    end
    if (init_tap) begin
      for (i=0; i<7; i++) begin
        t[i] = taps[i];
      end
    end
    if (!seed && run) begin
      r[7] <= r[0];
      for (i=0; i<7; i++) begin
        r[i] <= t[i] ? r[0] ^ r[i+1] : r[i+1];
      end
    end
  end

  assign q = r;

endmodule
