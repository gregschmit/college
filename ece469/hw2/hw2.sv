
module clear_highest_1(input logic[3:0] D,
                       output logic[3:0] Y,
                       output logic[1:0] Z);
  assign Y[3] = 0;
  assign Y[2] = D[2] & D[3];
  assign Y[1] = D[1] & (D[2] | D[3]);
  assign Y[0] = D[0] & (D[1] | D[2] | D[3]);
  assign Z[0] = (Y[2] ^ Y[3]) & ~(Y[0] ^ Y[1]) | (Y[0] ^ Y[1]) & ~(Y[2] ^ Y[3]);
  assign Z[1] = (Y[0] | Y[1]) & (Y[0] | Y[2] | Y[3]) & (Y[1] | Y[2] | Y[3]);

endmodule
