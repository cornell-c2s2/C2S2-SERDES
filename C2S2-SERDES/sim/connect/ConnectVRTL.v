`include "../../../C2S2-Module-Library/lib/sim/nbitregister/RegisterV_Reset.v"
/////////////////////////////////// Serializer
module SerializerControl
    #(
        N_SAMPLES = 8
    )
    (
        input  logic                           recv_val,
        output logic                           recv_rdy,

        output logic                           send_val,
        input  logic                           send_rdy,

        output logic [$clog2(N_SAMPLES) - 1:0] mux_sel,
        output logic                           reg_en,

        input logic                            clk,
        input logic                            reset
    );

    localparam INIT  = 0;
    localparam OUTPUT_START = 1;
    localparam ADD   = 2;

    logic next_state;
    logic state;

    logic [$clog2(N_SAMPLES):0] mux_sel_next;

    always @(*) begin
        case(state)
            INIT:
                begin
                    if(reset == 1) next_state = INIT;
                    if(recv_val == 1) next_state = OUTPUT_START; 
                    else next_state = INIT;
                end
            OUTPUT_START:
                begin
                    if(mux_sel_next!= N_SAMPLES) next_state = OUTPUT_START;
                    else next_state = INIT;
                end
            default:
                next_state = INIT;
        endcase
    end

    always @(*) begin
        case(state)
            INIT:
                begin
                    reg_en       = 1;
                    send_val     = 0;
                    recv_rdy     = 1;
                    mux_sel_next = 0;
                end
            OUTPUT_START:
                begin
                    reg_en   = 0;
                    send_val = 1;
                    recv_rdy = 0;
                    if(send_rdy == 1) mux_sel_next = mux_sel + 1;
                    else              mux_sel_next = mux_sel;
                end
        
        endcase
    end

    always @(posedge clk) begin
        if(reset) begin
            state <= INIT;
        end else begin
            mux_sel <= mux_sel_next;
            state   <= next_state;
        end
    end
endmodule

module SerializerVRTL
   #(
        BIT_WIDTH  = 32,
        N_SAMPLES  = 8
    )
    (
        input  logic [BIT_WIDTH - 1:0] recv_msg [N_SAMPLES - 1:0],
        input  logic                   recv_val                  ,
        output logic                   recv_rdy                  ,

        output logic [BIT_WIDTH - 1:0] send_msg,
        output logic                   send_val                  ,
        input  logic                   send_rdy                  ,

        input  logic                   reset                     ,
        input  logic                   clk
    );

    logic [$clog2(N_SAMPLES) - 1:0] mux_sel;
    logic reg_en;
    logic [BIT_WIDTH - 1:0] reg_out [N_SAMPLES - 1:0];
    
    generate
        genvar i;
        for( i = 0; i < N_SAMPLES; i++) begin
            RegisterV_Reset #( .N(BIT_WIDTH) ) register ( .clk(clk), .reset(reset), .w(reg_en), .d(recv_msg[i]), .q(reg_out[i]) );
        end
    endgenerate

    always @(*) begin
        send_msg = reg_out[mux_sel];
    end

    SerializerControl #(.N_SAMPLES(N_SAMPLES)) ctrl ( .clk(clk), .reset(reset), .recv_val(recv_val), .recv_rdy(recv_rdy), .send_val(send_val), .send_rdy(send_rdy), .mux_sel(mux_sel), .reg_en(reg_en));     

endmodule

/////////////////////////////////// Deserializer
module ControlVRTL 
#(
    parameter N_SAMPLES = 8
)(
    input   logic recv_val,
    input   logic send_rdy,


    output  logic send_val,
    output  logic recv_rdy,

    output  logic [N_SAMPLES - 1:0] en_sel,

    input   logic reset,
    input   logic clk
);
    localparam [1:0] INIT =   2'b00;
    localparam [1:0] STATE1 = 2'b01;
    localparam [1:0] STATE2 = 2'b10; 

    logic [$clog2(N_SAMPLES) + 1:0] count; //counter
    logic [$clog2(N_SAMPLES) + 1:0] count_next;

    logic [1:0] next_state;
    logic [1:0] state;

    DecoderVRTL #( .BIT_WIDTH( $clog2(N_SAMPLES) ) ) decoder ( .in(count), .out(en_sel));

    always @(*) begin 
       case(state)
            INIT: begin 

                if (count_next == N_SAMPLES) begin
                    next_state = STATE1;
                end 
                else begin
                    next_state = INIT;
                end

                end

            STATE1: begin
                if(send_rdy == 1) begin
                    next_state = INIT;
                end else begin
                    next_state = STATE1;
                end
            end

            default: next_state = INIT;
        endcase
    end  

    always @(*) begin 

        case(state)
            INIT: begin 
                if(recv_val == 1) begin
                    count_next = count + 1;
                end else begin
                    count_next = count;
                end

                recv_rdy = 1'b1;
                send_val = 1'b0;
            end

            STATE1: begin
            count_next = 0;
            recv_rdy = 1'b0;
            send_val = 1'b1;
            end

            default: begin
                count_next = 0;
                recv_rdy = 1'b1;
                send_val = 1'b0;
            end

        endcase

    end

    always @ (posedge clk) begin 
        if(reset) begin
            count <= 0;
            state <= INIT;
        end else begin
            count <= count_next;
            state <= next_state;
        end
    end 

endmodule

module DecoderVRTL #(
    parameter BIT_WIDTH = 3
)(
	input  logic [BIT_WIDTH - 1:0] in,
	output logic [(1 << BIT_WIDTH) - 1:0] out
);

	always @(*) out = {{1 << BIT_WIDTH - 1 {1'b0}}, 1'b1} << in;
endmodule

module DeserializerVRTL
#(
    parameter N_SAMPLES = 8,
	parameter BIT_WIDTH  = 32
)(
	
	input  logic recv_val,
    output logic recv_rdy, 	 
	input  logic [BIT_WIDTH - 1:0] recv_msg,

	output logic send_val, 
    input  logic send_rdy,
    output logic [BIT_WIDTH - 1:0] send_msg [N_SAMPLES - 1:0],

    input logic clk, 
	input logic reset
);
    
    logic [N_SAMPLES - 1:0] en_sel;

    //body of code
	ControlVRTL #(.N_SAMPLES(N_SAMPLES)) c
		(
			.recv_val(recv_val), 
			.send_rdy(send_rdy),
			
			.send_val(send_val),
			.recv_rdy(recv_rdy), 

            .reset(reset),
			.clk(clk),

			.en_sel(en_sel)
		);

    generate
        genvar i;
        for( i = 0; i < N_SAMPLES; i++) begin
            RegisterV_Reset #( .N(BIT_WIDTH) ) register ( .clk(clk), .reset(reset), .w(en_sel[i]), .d(recv_msg), .q(send_msg[i]) );
        end
    endgenerate

endmodule

//////////////////////////////////
module ConnectVRTL
   #(
        BIT_WIDTH  = 32,
        N_SAMPLES  = 8
    )(  
        // serializer inputs & outputs
        input  logic [BIT_WIDTH - 1:0] recv_msg  [N_SAMPLES - 1:0], 
        input  logic                   recv_val                  ,
        output logic                   recv_rdy                  ,

	    output logic send_val                                   , 
        input  logic send_rdy                                   ,
        output logic [BIT_WIDTH - 1:0] send_msg  [N_SAMPLES - 1:0],

        // clk and reset signals
        input  logic                   reset                     ,
        input  logic                   clk
    );
        logic recv_rdys; // serializer rdy
        logic send_vals;
        logic send_rdys;
        logic [BIT_WIDTH - 1:0] send_msgi;


        SerializerVRTL #(.N_SAMPLES(N_SAMPLES), .BIT_WIDTH(BIT_WIDTH)) serializer
        (
            .recv_val(recv_val), 
            .recv_rdy(recv_rdys), 	 
            .recv_msg(recv_msg),
            .send_val(send_vals), 
            .send_rdy(send_rdys),
            .send_msg(send_msgi),
            .clk(clk), 
            .reset(reset)
        );

        DeserializerVRTL #(.N_SAMPLES(N_SAMPLES), .BIT_WIDTH(BIT_WIDTH)) deserializer
        (
            .recv_val(send_vals),   // output of serializer
            .recv_rdy(recv_rdy),  //deserializer ready to recieve
            .recv_msg(send_msgi), // output of serializer
            .send_val(send_val), 
            .send_rdy(send_rdy),
            .send_msg(send_msg),
            .clk(clk), 
            .reset(reset)
        );

endmodule
        