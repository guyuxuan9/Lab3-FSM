module lfsr4(
    input logic clk,
    input logic rst,
    input logic en,
    output logic [4:1] data_out
);

logic [4:1]     sreg; // shift register
always_ff @(posedge clk) 
    if (rst)
        sreg <= 4'b1;
    else if (en)
        sreg <= {sreg[3:1],sreg[3] ^ sreg[4]};

assign data_out = sreg;
endmodule
