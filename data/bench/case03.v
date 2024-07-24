
// 测试concat

module M1(A, B);
    input [3:0] A;
    output B;
endmodule

module case03(G0, G1, G2, G3);
  input G0;
  input [1:0] G1;
  input [3:0] G2;
  output G3;
  wire n_1;
  M1 inst1(.A({G0, G1[0], G2[3:2]}), .B(n_1));
endmodule