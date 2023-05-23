
module decoder(input logic clk, reset,
               input logic [10:0] instr,
               output logic reg_wr, add, lfsr_seed, lfsr_tap, lfsr_lmem,
               output logic lfsr_run, mem_wr, halt,
               output logic [7:0] immi, [6:0] lfsr_taps);

  // dict
  logic [7:0] controls;
  logic [2:0] op;
  assign op = instr[10:8];

  // easy output calc
  assign lfsr_taps = instr[6:0];
  assign immi = instr[7:0];

  assign {reg_wr, add, lfsr_seed, lfsr_tap, lfsr_lmem, lfsr_run, mem_wr, halt} = controls;

  //always_ff @(posedge clk) begin
  //  if (op == 3'b111)
  //    halt <= 1;
  //  else
  //    halt <= 0;
  //end

  always_comb begin
    if (!reset) begin
      case(op)
        3'b000:
          controls <= 8'b01000010; // st
        3'b001:
          controls <= 8'b01101000; // ld
        3'b010:
          controls <= 8'b10000000; // init_addr
        3'b011:
          controls <= 8'b11000000; // add_addr
        3'b100:
          controls <= 8'b00010000; // config
        3'b101:
          controls <= 8'b00100000; // init_L
        3'b110:
          controls <= 8'b00000100; // run
        3'b111:
          controls <= 8'b00000001; // halt
      endcase
    end else begin
      controls <= 8'b00000000; // reset
    end
  end

endmodule
