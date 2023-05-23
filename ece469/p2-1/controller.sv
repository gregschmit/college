
module controller(input logic [5:0] op, funct,
                  input logic zero,
                  output logic zneg,
                  output logic memtoreg, memwrite, pcsrc, alusrc, regdst,
                  output logic regwrite, jump,
                  output logic [2:0] alucontrol);
  logic [1:0] aluop;
  logic branch;
  maindec md(op, memtoreg, memwrite, branch, zneg, alusrc, regdst, regwrite, jump,
    aluop);
  aludec ad(funct, aluop, alucontrol);

  assign pcsrc = branch & zero;
endmodule
