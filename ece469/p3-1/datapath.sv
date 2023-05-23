module datapath(input logic clk, reset,
                input logic pcen, irwrite, regwrite,
                input logic alusrca, iord, memtoreg, regdst,
                input logic [1:0] alusrcb, pcsrc,
                input logic [2:0] alucontrol,
                output logic [5:0] op, funct,
                output logic zero,
                output logic [31:0] adr, writedata,
                input logic [31:0] readdata);

  // Below are the internal signals of the datapath module.

  logic [4:0] writereg;
  logic [31:0] pcnext, pc;
  logic [31:0] instr, data, srca, srcb;
  logic [31:0] a;
  logic [31:0] aluresult, aluout;
  logic [31:0] signimm; // the sign-extended immediate
  logic [31:0] signimmsh; // the sign-extended immediate shifted left by 2
  logic [31:0] wd3, rd1, rd2;

  // op and funct fields to controller
  assign op = instr[31:26];
  assign funct = instr[5:0];

  // Your datapath hardware goes below. Instantiate each of the submodules
  // that you need. Remember that alu's, mux's and various other
  // versions of parameterizable modules are available in textbook 7.6

  // Here, parameterizable 3:1 and 4:1 muxes are provided below for your use.

  // Remember to give your instantiated modules applicable names
  // such as pcreg (PC register), wdmux (Write Data Mux), etc.
  // so it's easier to understand.

  // IF
  always_ff @(posedge clk, posedge reset) begin
    if (reset) pc <= 0;
    else pc <= pcnext;
  end
  assign adr = iord ? aluout : pc;

  // ID/R
  always_ff @(posedge clk) begin
    if (irwrite) instr <= readdata;
    data <= readdata;
  end
  assign writereg = regdst ? instr[15:11] : instr[20:16];
  logic [31:0] result;
  assign result = memtoreg ? data : aluout;
  logic [31:0] rd_a, rd_b;
  regfile rf(clk, regwrite, instr[25:21], instr[20:16], writereg, result,
    rd_a, rd_b);
  always_ff @(posedge clk) begin
    a <= rd_a;
    writedata <= rd_b;
  end

  // EX
  assign srca = alusrca ? a : pc;
  assign signimmsh = signimm << 2;
  signext se(instr[15:0], signimm);
  mux4 #(32) srcbmux(writedata, 4, signimm, signimmsh, alusrcb, srcb);
  alu alu(srca, srcb, alucontrol, aluresult, zero);
  always_ff @(posedge clk) begin
    aluout <= aluresult;
  end
  logic [27:0] jumpshift;
  assign jumpshift = {2'b00, instr[25:0]} << 2;
  logic [31:0] pcjump;
  assign pcjump = {pc[31:28], jumpshift};
  mux3 #(32) pcmux(aluresult, aluout, pcjump, pcsrc, pcnext);

  // datapath
endmodule
