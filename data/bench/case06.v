
// 测试Const
module NAND2X2 (A, B, Y);
input  A, B;
output Y ;

endmodule

module case01(G1);
  output G1;

  NAND2X2 g17(.A (1'b0), .B (1'b1), .Y (G1));
endmodule