
module maindec(input logic [5:0] op,
               output logic memtoreg, memwrite, branch, zneg, alusrc, regdst,
               output logic regwrite, jump,
               output logic [1:0] aluop);
  logic [9:0] controls;

  assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, jump, aluop, zneg} = controls;

  always_comb begin
    case(op)
      6'b000000:
        controls <= 10'b1100000100; // RTYPE
      6'b100011:
        controls <= 10'b1010010000; // LW
      6'b101011:
        controls <= 10'b0010100000; // SW
      6'b000100:
        controls <= 10'b0001000010; // BEQ
      6'b001000:
        controls <= 10'b1010000000; // ADDI
      6'b000010:
        controls <= 10'b0000001000; // J
      6'b001101:
        controls <= 10'b1010000110; // ORI
      6'b000101:
        controls <= 10'b0001000011; // BNE
      default:
        controls <= 10'bxxxxxxxxxx; // illegal op
    endcase
  end

endmodule
