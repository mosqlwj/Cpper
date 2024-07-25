
// 测试RangeSelect
module M1 (A, B, Y);
input [2:0]  A;
input [1:0] B;
output Y ;

endmodule

module case02(G0, G1, G2);
  input [3:0] G0;
  input [1:0] G1;
  output G2;
  wire[0:0] n_1;

  M1 inst(.A (G0[3:1]), .B (G1), .Y (n_1[0]));
endmodule