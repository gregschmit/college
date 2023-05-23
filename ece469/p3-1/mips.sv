
module mux3 #(parameter WIDTH = 8)
            (input logic [WIDTH-1:0] d0, d1, d2,
             input logic [1:0] s,
             output logic [WIDTH-1:0] y);
  assign #1 y = s[1] ? d2 : (s[0] ? d1 : d0);
endmodule

module mux4 #(parameter WIDTH = 8)
            (input logic [WIDTH-1:0] d0, d1, d2, d3,
             input logic [1:0] s,
             output logic [WIDTH-1:0] y);

     always_comb
        case(s)
            2'b00: y = d0;
            2'b01: y = d1;
            2'b10: y = d2;
            2'b11: y = d3;
          endcase
endmodule

module mips(input logic clk, reset,
    output logic [31:0] adr, writedata,
    output logic memwrite,
    input logic [31:0] readdata);

 logic         zero, pcen, irwrite, regwrite,
               alusrca, iord, memtoreg, regdst;
 logic [1:0]   alusrcb, pcsrc;
 logic [2:0]   alucontrol;
 logic [5:0]   op, funct;

 controller c(clk, reset, op, funct, zero,
              pcen, memwrite, irwrite, regwrite,
              alusrca, iord, memtoreg, regdst,
              alusrcb, pcsrc, alucontrol);
 datapath dp(clk, reset,
             pcen, irwrite, regwrite,
             alusrca, iord, memtoreg, regdst,
             alusrcb, pcsrc, alucontrol,
             op, funct, zero,
             adr, writedata, readdata);
endmodule
