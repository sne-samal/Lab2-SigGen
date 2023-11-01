module sigdelay #(
    parameter   A_WIDTH = 9,
                D_WIDTH = 8
) (
    // interface signals
    input logic                     clk,
    input logic                     rst,
    input logic                     wr,
    input logic                     rd, 
    input logic     [A_WIDTH-1:0]   offset,
    input logic    [D_WIDTH-1:0]   mic_signal,
    output logic    [D_WIDTH-1:0]   delayed_signal
);
// any connecting wires
    logic           [A_WIDTH-1:0]   address;

counter addrCounter (
    .clk(clk),
    .rst(rst),
    .en(1),
    .incr(1),
    .count(address)
);

ram sigRom (
    .clk (clk),
    .wr_en(wr),
    .rd_en(rd),
    .wr_addr(address+offset),
    .rd_addr(address),
    .din(mic_signal),
    .dout(delayed_signal)
);

endmodule
