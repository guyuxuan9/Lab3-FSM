module f1_light(
    input logic     N,
    input logic     en,
    input logic     rst,
    input logic     clk,
    output logic    [7:0] data_out
);

logic tick;

clktick Clocktick(
    .N(N),
    .en(en),
    .rst(rst),
    .clk(clk),
    .tick(tick)
);

f1_fsm fsm(
    .rst(rst),
    .en(tick),
    .clk(clk),
    .data_out(data_out)
);
endmodule
