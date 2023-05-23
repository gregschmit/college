
module mem(input logic clk, we,
           input logic [31:0] a, wd,
           output logic [31:0] rd);

           logic [31:0] RAM[63:0];

 // initialize memory with instructions

 initial
  begin
    $readmemh("./test.tv",RAM);
      // "memfile.dat" contains your instructions in hex
      // you must create this file
  end

 assign rd = RAM[a[31:2]]; // word aligned

 always_ff @(posedge clk)
  if (we)
    RAM[a[31:2]] <= wd;
endmodule

module top(input logic clk, reset,
           output logic [31:0] writedata, adr,
           output logic memwrite);

 logic [31:0] readdata;

 // microprocessor (control & datapath)
 mips mips(clk, reset, adr, writedata, memwrite, readdata);

 // memory
 mem mem(clk, memwrite, adr, writedata, readdata);
endmodule

module mips_tb();
  logic clk;
  logic reset;
  logic [31:0] writedata, dataadr;
  logic memwrite;

  // instantiate device to be tested
  top dut (clk, reset, writedata, dataadr, memwrite);

  // initialize test
  initial begin
    reset <= 1; # 22; reset <= 0;
  end

  // generate clock to sequence tests
  always begin
    clk <= 1; # 5; clk <= 0; # 5;
  end

  // check results
  always @(negedge clk) begin
    if (memwrite) begin
      if (dataadr===84 && writedata===15) begin
        $display("Simulation succeeded");
        $stop;
      end else if (dataadr !== 80) begin
        $display("Simulation failed");
        $stop;
      end
    end
  end
endmodule
