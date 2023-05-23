
module sqm(input logic [7:0] a,
           input logic [3:0] b,
           output logic [7:0] c,
           output logic [7:0] y);
  assign c = (b * b);
  assign y = c % a;
endmodule
