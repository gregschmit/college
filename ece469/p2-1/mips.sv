
module mips(input logic clk, reset,
            output logic [31:0] pc,
            input logic [31:0] instr,
            output logic memwrite,
            output logic [31:0] aluout, writedata,
            input logic [31:0] readdata);
  logic memtoreg, alusrc, regdst, regwrite, jump, pcsrc, zero;
  logic [2:0] alucontrol;
  logic zneg;
  controller c(instr[31:26], instr[5:0], zero, zneg, memtoreg, memwrite, pcsrc,
    alusrc, regdst, regwrite, jump, alucontrol);
  datapath dp(clk, reset, memtoreg, pcsrc, alusrc, regdst, regwrite, jump,
    alucontrol, zero, zneg, pc, instr, aluout, writedata, readdata);
endmodule
