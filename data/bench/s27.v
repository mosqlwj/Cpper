module INVX1 (A, Y);
input  A ;
output Y ;
   not I0(Y, A);
endmodule

module NAND2X2 (A, B, Y);
input  A, B ;
output Y ;
wire I0_out;
   and I0(I0_out, A, B);
   not I1(Y, I0_out);
endmodule

module s27(G0, G1, G2);
  input G0, G1;
  output G2;
  wire n_1;

  INVX1 g81(.A (G0), .Y (n_1));
  NAND2X2 g17(.A (G1), .B (n_1), .Y (G2));
endmodule