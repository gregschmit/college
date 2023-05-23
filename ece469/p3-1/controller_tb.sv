`include "controller.sv"

module controller_testbench();

  // input
  logic clk, reset, zero;
  logic [5:0] op, funct;

  // output
  logic pcen, memwrite, irwrite, regwrite, alusrca, iord, memtoreg, regdst;
  logic [1:0] alusrcb, pcsrc;
  logic [2:0] alucontrol;

  // change first bracket numbers to reflect size of line
  // change second bracket numbers to reflect the number of lines
  logic [12:0] testvector[59:0];
  integer num; // used for iterating through testvector
  controller dut(clk, reset, op, funct, zero, pcen, memwrite, irwrite,
    regwrite, alusrca, iord, memtoreg, regdst, alusrcb, pcsrc, alucontrol);

  always begin
    clk <= 1; # 5; clk <= 0; # 5;
  end

  initial begin
    reset <= 1; # 22; reset <= 0;
    $readmemb("./controller.tv", testvector);
    for (num = 0; num<=60; num++) begin
      if (num == 60)
        $stop;
      {op, funct, zero} = testvector[num];#10;
      $display("testing op=%b funct=%b zero=%b", op, funct, zero);
    end
  end

endmodule
