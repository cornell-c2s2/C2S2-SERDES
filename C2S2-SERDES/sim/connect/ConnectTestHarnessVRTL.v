`include "./ConnectVRTL.v"

module ConnectTestHarnessVRTL
    #(
        BIT_WIDTH  = 32,
        N_SAMPLES  = 8
    )
    (
        input  logic [BIT_WIDTH * N_SAMPLES - 1:0] recv_msg, // [BIT_WIDTH - 1:0]
        input  logic                   recv_val,
        output logic                   recv_rdy,

        output logic [BIT_WIDTH * N_SAMPLES - 1:0] send_msg, 
        input  logic                   send_rdy, 
        output logic                   send_val,

        input  logic                   reset,
        input  logic                   clk
    );
    
    logic [BIT_WIDTH - 1:0] recv_msg_intermediate [N_SAMPLES - 1:0];
    logic [BIT_WIDTH - 1:0] send_msg_intermediate [N_SAMPLES - 1:0];

    always @(*) begin
        int i;
        for(i = 0; i < N_SAMPLES; i = i + 1) begin
            recv_msg_intermediate [i][BIT_WIDTH - 1:0]        = recv_msg[BIT_WIDTH * i +: BIT_WIDTH];
            send_msg   [BIT_WIDTH * i +: BIT_WIDTH] = send_msg_intermediate [i][BIT_WIDTH - 1:0]; // deserializer side

        end
    end

    ConnectVRTL #(.N_SAMPLES(N_SAMPLES), .BIT_WIDTH(BIT_WIDTH)) connect
    (
        .recv_msg(recv_msg_intermediate),
        .recv_val(recv_val),
        .recv_rdy(recv_rdy),

        .send_msg(send_msg_intermediate),
        .send_val(send_val),
        .send_rdy(send_rdy),

        .reset(reset),
        .clk(clk)
    );

endmodule