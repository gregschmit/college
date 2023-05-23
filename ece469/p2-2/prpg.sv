
module prpg(input logic clk, reset,
            output logic [7:0] pc,
            input logic [10:0] instr,
            output logic reg_wr, add, lfsr_seed, lfsr_tap, lfsr_lmem, lfsr_run, mem_wr, halt);


  // pc
  always_ff @(posedge clk, posedge reset) begin
    if (reset) begin
      pc <= 0;
    end else if (instr[10:8] != 3'b111)
      pc <= pc + 1;
  end

  // decoder
  logic [7:0] immi;
  logic [6:0] lfsr_taps;
  decoder dec(clk, reset, instr, reg_wr, add, lfsr_seed, lfsr_tap, lfsr_lmem, lfsr_run, mem_wr, halt, immi, lfsr_taps);

  // r_addr
  logic [7:0] r_addr;
  logic [7:0] aluout;
  regfile mainreg(clk, reg_wr, aluout, r_addr);

  // alu
  logic [7:0] a;
  assign a = add ? r_addr : 0;
  alu ad(a, immi, aluout);

  // memory
  logic [7:0] lfsr_out, memout;
  memory m(clk, mem_wr, aluout, lfsr_out, memout);

  // lfsr
  logic [7:0] seed_data;
  assign seed_data = lfsr_lmem ? memout : immi;
  lfsr l(clk, lfsr_run, lfsr_seed, lfsr_tap, seed_data, lfsr_taps, lfsr_out);

endmodule
