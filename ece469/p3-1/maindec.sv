
module maindec(input logic clk, reset,
          input logic [5:0] op,
          output logic pcwrite, memwrite, irwrite, regwrite,
          output logic alusrca, branch, iord, memtoreg, regdst,
          output logic [1:0] alusrcb, pcsrc,
          output logic [1:0] aluop);

 parameter FETCH = 4'b0000; // State 0
 parameter DECODE = 4'b0001; // State 1
 parameter MEMADR = 4'b0010; // State 2
 parameter MEMRD = 4'b0011; // State 3
 parameter MEMWB = 4'b0100; // State 4
 parameter MEMWR = 4'b0101; // State 5
 parameter RTYPEEX = 4'b0110; // State 6
 parameter RTYPEWB = 4'b0111; // State 7
 parameter BEQEX = 4'b1000; // State 8
 parameter ADDIEX = 4'b1001; // State 9
 parameter ADDIWB = 4'b1010; // state 10
 parameter JEX = 4'b1011; // State 11

 parameter LW = 6'b100011; // Opcode for lw
 parameter SW = 6'b101011; // Opcode for sw
 parameter RTYPE = 6'b000000; // Opcode for R-type
 parameter BEQ = 6'b000100; // Opcode for beq
 parameter ADDI = 6'b001000; // Opcode for addi
 parameter J = 6'b000010; // Opcode for j

 logic [3:0] state, nextstate;
 logic [14:0] controls;


  // state register
  always_ff @(posedge clk or posedge reset)
    if(reset) state <= FETCH;
    else state <= nextstate;

  // ADD CODE HERE
  // Finish entering the next state logic below. The first
  // two states, FETCH and DECODE, have been completed for you.

  // next state logic
  always_comb begin
    case(state)
      FETCH: nextstate = DECODE;
      DECODE: case(op)
          LW: nextstate = MEMADR;
          SW: nextstate = MEMADR;
          RTYPE: nextstate = RTYPEEX;
          BEQ: nextstate = BEQEX;
          ADDI: nextstate = ADDIEX;
          J: nextstate = JEX;
          default: nextstate = 4'b0000; // should never happen
        endcase
      MEMADR: case(op)
          LW: nextstate = MEMRD;
          SW: nextstate = MEMWR;
          default: nextstate = 4'b0000;
        endcase
      MEMRD: nextstate = MEMWB;
      MEMWB: nextstate = FETCH;
      MEMWR: nextstate = FETCH;
      RTYPEEX: nextstate = RTYPEWB;
      RTYPEWB: nextstate = FETCH;
      BEQEX: nextstate = FETCH;
      ADDIEX: nextstate = ADDIWB;
      ADDIWB: nextstate = FETCH;
      JEX: nextstate = FETCH;
      default: nextstate = 4'b0000; // should never happen
    endcase
  end

 // output logic
  assign {pcwrite, memwrite, irwrite, regwrite,
          alusrca, branch, iord, memtoreg, regdst,
          alusrcb, pcsrc, aluop} = controls;

 // ADD CODE HERE
 // Finish entering the output logic below. The
 // output logic for the first two states, S0 and S1,
 // have been completed for you.

  always_comb begin
    case(state)
      FETCH: controls = 15'h5010;
      DECODE: controls = 15'h0030;
      MEMADR: controls = 15'h0420;      //NOTE: THIS HAS THE SAME COMMAND SIGNALS AS ADDIEX
      MEMRD: controls = 15'h0100;
      MEMWB : controls = 15'h0880;
      MEMWR: controls = 15'h2100;
      RTYPEEX: controls = 15'h0402;
      RTYPEWB: controls = 15'h0840;
      BEQEX: controls = 15'h0605;
      ADDIEX: controls = 15'h0420;       //NOTE: THIS HAS THE SAME COMMAND SIGNALS AS MEMADR
      ADDIWB: controls = 15'h0800;
      JEX: controls = 15'h4008;
      default: controls = 15'hxxxx; // should never happen
    endcase
  end
endmodule
