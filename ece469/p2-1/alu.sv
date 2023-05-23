
module mux2to1_32bit(input wire [31:0] i0, i1,
                     input wire s,
                     output wire [31:0] out);
  assign out = s ? i1 : i0;
endmodule

module mux4to1_32bit(input wire [31:0] i0, i1, i2, i3,
                input wire [1:0] s,
                output wire [31:0] out);
  wire [31:0] m1_out, m2_out;
  mux2to1_32bit m1(i0, i1, s[0], m1_out);
  mux2to1_32bit m2(i2, i3, s[0], m2_out);
  mux2to1_32bit m3(m1_out, m2_out, s[1], out);
endmodule

module adder_32bit(input wire [31:0] a, b,
                    input wire op,
                    output wire [31:0] y);
  //assign s = op ? A - B : A + B;
  //How to get Cout??? A + B is over 33 bits max , so we do the following
  assign y = op ? a + b + 1 : a + b;
  //op equal to 1 implies b is inverted
  // cout concatenated with s is over 33 bits
endmodule

module zero_extender(input wire a, output wire [31:0] aex);
  assign aex[0] = a;
  assign aex[31:1] = 30'b0;
endmodule

module alu(input logic [31:0] a, b,
           input logic [2:0] f,
           input logic zero_negate,
           output logic [31:0] y,
           output logic zero);
  wire [31:0] bb;
  wire [31:0] s;
  wire cout;
  wire [31:0] zeroex;

  mux2to1_32bit bbmux(b, ~b, f[2], bb);
  adder_32bit adder(a, bb, f[2], s);
  zero_extender ze(s[31], zeroex);
  mux4to1_32bit ymux(a & bb, a | bb, s, zeroex, f[1:0], y);

  assign zero = (~(|y)) ^ zero_negate;
endmodule
