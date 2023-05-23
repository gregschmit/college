
module serial1s(input logic [7:0] a,
                output logic [3:0] y);
  int count;
  int found;
  logic [7:0] im[7];
  always_comb begin
    im[0] = a & (a << 1);
    im[1] = im[0] & (im[0] << 1);
    im[2] = im[1] & (im[1] << 1);
    im[3] = im[2] & (im[2] << 1);
    im[4] = im[3] & (im[3] << 1);
    im[5] = im[4] & (im[4] << 1);
    im[6] = im[5] & (im[5] << 1);

    if (a == 0)
      y = 0;
    else if (im[0] == 0)
      y = 1;
    else if (im[1] == 0)
      y = 2;
    else if (im[2] == 0)
      y = 3;
    else if (im[3] == 0)
      y = 4;
    else if (im[4] == 0)
      y = 5;
    else if (im[5] == 0)
      y = 6;
    else if (im[6] == 0)
      y = 7;
    else
      y = 8;
  end

endmodule
