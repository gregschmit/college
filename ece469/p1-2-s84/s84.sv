`include "ca2.sv"
`include "serial1s.sv"

/*
main s84 module
test vector lines will look like A_B_op_fLoc_fType_Yexpected_Zexpected
*/
module s84(input wire [7:0] A,
           input wire [3:0] B,
           input wire op,
           input wire [2:0] f_loc,
           input wire [1:0] f_type,
           output wire [7:0] Cout,
           output wire [7:0] Y,
           output wire [3:0] Z);

  wire [7:0] ca2Out;
  wire [7:0] sqmOut;
  wire [3:0] c1sOut;

  ca2 ca2Device(A,B,ca2Out);
  sqm sqmDevice(A, B, f_loc, f_type, Cout, sqmOut);
  serial1s c1sDevice(Y,c1sOut);

  assign Y = op ? ca2Out : sqmOut;
  assign Z = c1sOut;
endmodule


/*
sqm module which can compute 'normal'sqm or contain specified faults
*/
module sqm(input wire [7:0] A,
           input wire [3:0] B,
           input wire [2:0] f_loc,
           input wire [1:0] f_type,
           output wire [7:0] Cout,
           output wire [7:0] out);

  //f_loc goes into decoder that produces 8bit string with only one 1
  //each bit of C(=Bsqrd) goes into 4to1 mux e.g. (C,0,1,C_not) controlled by f_type
  //this 4to1 mux output goes into 2to1 mux containing (C,4to1muxout) controlled by the f_loc_decoder output

  wire [7:0] loc;//output of a decoder, used to determine which bit to change.
  wire [7:0] m41out; //output of 8 separate 4to1 muxes
  wire [7:0] C; // intermediate, equal to B*B
  wire [7:0] m21out;// output of 8 separate 2to1 muxes

  square multB(B,C);
  decoder dec_loc(f_loc,loc);

  mux4to1_1bit m41_0(C[0],1'b0,1'b1,~C[0],f_type,m41out[0]);
  mux4to1_1bit m41_1(C[1],1'b0,1'b1,~C[1],f_type,m41out[1]);
  mux4to1_1bit m41_2(C[2],1'b0,1'b1,~C[2],f_type,m41out[2]);
  mux4to1_1bit m41_3(C[3],1'b0,1'b1,~C[3],f_type,m41out[3]);
  mux4to1_1bit m41_4(C[4],1'b0,1'b1,~C[4],f_type,m41out[4]);
  mux4to1_1bit m41_5(C[5],1'b0,1'b1,~C[5],f_type,m41out[5]);
  mux4to1_1bit m41_6(C[6],1'b0,1'b1,~C[6],f_type,m41out[6]);
  mux4to1_1bit m41_7(C[7],1'b0,1'b1,~C[7],f_type,m41out[7]);

  mux2to1_1bit m21_0(C[0],m41out[0],loc[0],m21out[0]);
  mux2to1_1bit m21_1(C[1],m41out[1],loc[1],m21out[1]);
  mux2to1_1bit m21_2(C[2],m41out[2],loc[2],m21out[2]);
  mux2to1_1bit m21_3(C[3],m41out[3],loc[3],m21out[3]);
  mux2to1_1bit m21_4(C[4],m41out[4],loc[4],m21out[4]);
  mux2to1_1bit m21_5(C[5],m41out[5],loc[5],m21out[5]);
  mux2to1_1bit m21_6(C[6],m41out[6],loc[6],m21out[6]);

  assign Cout = m21out;
  assign out = m21out % A;

endmodule



module square(input wire [3:0] B, output wire [7:0] C);
  assign C = B*B;
endmodule


module decoder(input wire [2:0] loc, output wire [7:0] out);

  assign out[0] = ~loc[0] & ~loc[1] & ~loc[2];
  assign out[1] = loc[0] & ~loc[1] & ~loc[2];
  assign out[2] = ~loc[0] & loc[1] & ~loc[2];
  assign out[3] = loc[0] & loc[1] & ~loc[2];
  assign out[4] = ~loc[0] & ~loc[1] & loc[2];
  assign out[5] = loc[0] & ~loc[1] & loc[2];
  assign out[6] = ~loc[0] & loc[1] & loc[2];
  assign out[7] = loc[0] & loc[1] & loc[2];
endmodule
