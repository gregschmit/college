
`include "serial1s.sv"

module serial1s_testbench();

  // testbench dict
  parameter int debug = 2; /**< debug info level (0=summary, 1=lines, 2=full) */
  parameter int bits = 12;
  parameter int lines = 4;
  logic [bits-1:0] testvector[lines-1:0];

  // device dict
  logic [7:0] a;
  logic [3:0] y;
  serial1s dut(a, y);
  logic [3:0] exp_y;

  // test bench
  int i;
  int fails = 0;
  initial begin
    $readmemb("./serial1s.tv", testvector);
    for (i=0; i<lines; i++) begin
      // parse vector data and wait for signal propogation
      {a, exp_y} = testvector[i];
      #10;
      if (debug >= 2)
        $display("%2d: (a=%b) :: y=%b:%b", i+1, a, exp_y, y);
      if (exp_y != y) begin
        if (debug >= 1)
          $display("Failure on line %0d", i+1);
        fails++;
      end
    end
    $display("%2d failures out of %0d tests", fails, lines);
  end

endmodule
