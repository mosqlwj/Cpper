// 测试assign
// 当前网表仅支持单比特assign，不支持复杂表达式assign，如concat

module case04(G0, G1, G2);
  input G0;
  input [1:0] G1;
  output [2:0] G2;
  wire n_1;

  assign G2[0] = G1[0];
  assign G2[1] = G1[1];
  assign G2[2] = G0;
  assign n_1 = 1'b0;

endmodule