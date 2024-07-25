
// 测试ElementSelect
module NAND2X2 (A, B, Y);
input  A, B;
output Y ;

endmodule

module case01(G0, G1);
  input[1:0] G0;
  output G1;

  NAND2X2 g17(.A (G0[0]), .B (G0[1]), .Y (G1));
endmodule