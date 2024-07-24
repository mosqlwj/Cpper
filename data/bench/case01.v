
// 测试blackbox
module INVX1 (A, Y);
input  A ;
output Y ;

endmodule

module case01(G0, G1, G2);
  input G0, G1;
  output G2;
  wire n_1;

  INVX1 g81(.A (G0), .Y (n_1));
  NAND2X2 g17(.A (G1), .B (n_1), .Y (G2));
endmodule