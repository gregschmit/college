
/*
This is the module for a 2to1 mux
Used for 1-bit data paths
*/
module mux2to1_1bit(input wire i0,i1, op , output wire out);
  assign out = op ? i1 : i0;
endmodule

/*
This is the module for a 4to1 mux
Used for 1-bit data paths, built with three 2to1 muxes
*/
module mux4to1_1bit(input wire i0,i1,i2,i3,input wire [1:0] op , output wire out);
  //intermediate wires for mux2to1 outputs
  wire mux1out,mux2out;
  //instantiate three 2by1 muxes
  mux2to1_1bit mux1(i0,i1,op[0],mux1out);
  mux2to1_1bit mux2(i2,i3,op[0],mux2out);
  mux2to1_1bit mux3(mux1out,mux2out,op[1],out);//out is final output
endmodule


/*
module for CA2, uses eight 4to1 muxes
*/
module ca2(input wire [7:0] A, input wire [3:0] B, output wire [7:0] Y);
  //for the op input into 4to1 mux, we give {A[(i+1) % 8],A[i]} to find Y[i]
  mux4to1_1bit m0(B[0],B[1],B[2],B[3],A[1:0],Y[0]);  // i = 0 --> (i+1) % 8 = 1
  mux4to1_1bit m1(B[0],B[1],B[2],B[3],A[2:1],Y[1]);  // i = 1 --> (i+1) % 8 = 2
  mux4to1_1bit m2(B[0],B[1],B[2],B[3],A[3:2],Y[2]);  // i = 2 --> (i+1) % 8 = 3
  mux4to1_1bit m3(B[0],B[1],B[2],B[3],A[4:3],Y[3]);  // i = 3 --> (i+1) % 8 = 4
  mux4to1_1bit m4(B[0],B[1],B[2],B[3],A[5:4],Y[4]);  // i = 4 --> (i+1) % 8 = 5
  mux4to1_1bit m5(B[0],B[1],B[2],B[3],A[6:5],Y[5]);  // i = 5 --> (i+1) % 8 = 6
  mux4to1_1bit m6(B[0],B[1],B[2],B[3],A[7:6],Y[6]);  // i = 6 --> (i+1) % 8 = 7
  mux4to1_1bit m7(B[0],B[1],B[2],B[3],{A[0],A[7]},Y[7]);  // i = 7 --> (i+1) % 8 = 0
endmodule
