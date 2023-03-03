module ControlVRTL 
#(
    parameter dec_in = 1, //#decoder input lines
    parameter N_SAMPLES = 1 << dec_in //#decoder output lines
)(
    input   logic recv_val,
    input   logic send_rdy,
    input   logic reset,
    input   logic clk,

    output  logic send_val,
    output  logic recv_rdy,
    output  logic [dec_in-1:0] dsel //input to decoder
);
    parameter [1:0] Init = 2'b00;
    parameter [1:0] State1 = 2'b01;
    parameter [1:0] State2 = 2'b10; 

    logic [N_SAMPLES-1:0] count; //counter
    logic [1:0] Scurr;
    logic [1:0] Snext;

    always @(recv_val, send_rdy, Scurr) begin 
       case(Scurr)
            Init: begin 
                if ((recv_val == 1) & (count != N_SAMPLES)) 
                    Snext = State1;
                else if ((recv_val == 1) & (count == N_SAMPLES)) 
                    Snext = State2;
                else 
                    Snext = Init;
                end

            State1: Snext = Init;

            State2: begin
                if (send_rdy == 1) Snext = Init; 
                else Snext = State2;
            end 

            default: Snext = 1'd0;
        endcase
    end  

    always @(Scurr) begin 
        if (Scurr == Init) begin 
            count = count;
            recv_rdy = 1'b1;
            send_val = 1'b0;
        end 

        else if (Scurr == State1) begin 
            recv_rdy = 1'b1;
            send_val = 1'b0;
            dsel = count;
            count = count + 1;
        end

        else if (Scurr == State2) begin 
            count = count;
            recv_rdy = 1'b0;
            send_val = 1'b1;
            dsel = count;
        end 

        else begin //reset
            count = 0;
            recv_rdy = 1'b1;
            send_val = 1'b0;
            dsel = 1'b0;
        end 
    end

    always @ (posedge clk) begin 
        if (reset == 1) Scurr = Init; else Scurr = Snext;
    end 

endmodule

module DecoderVRTL (
	x,
	y
);
    `ifdef USE_POWER_PINS
    inout vccd1, // User area 1 1.8V supply
    inout vssd1, // User area 1 digital ground
    `endif
	parameter m = 3;
	parameter n = 1 << m;
	input wire [m - 1:0] x;
	output reg [n - 1:0] y;
	always @(*) y = {{n - 1 {1'b0}}, 1'b1} << x;
endmodule

module RegisterV
	#(parameter BIT_WIDTH  = 32)
	(clk, reset, w, d, q);
    input logic clk;
    input logic reset;
    input  logic w;
    input logic [BIT_WIDTH-1:0] d;
    output logic [BIT_WIDTH-1:0] q;
    logic [BIT_WIDTH-1:0] regout;

    assign q = regout;

    always @(posedge clk) begin
	if (reset)
	    regout <= 0;
	else if (w)
	    regout <= d;
    end
endmodule

module ParallelVRTL
#(
	parameter dec_in = 3,					//decoder inputs
    parameter N_SAMPLES = 1 << dec_in, 	//number of outputs to decoder/#of registers
	parameter BIT_WIDTH  = 32
)(
	input logic clk, 
	input logic reset,
	input logic recv_val, 
	input logic send_rdy, 
	input logic [BIT_WIDTH - 1:0] recv_msg,

	output logic send_val, 
	output logic recv_rdy,
    output logic [BIT_WIDTH - 1:0] send_msg [N_SAMPLES - 1:0]
);
    logic [dec_in-1:0] dec_select;
    logic [N_SAMPLES-1:0] dec_out;
    //body of code
	ControlVRTL c
		(
			.recv_val(recv_val), 
			.send_rdy(send_rdy),
			.reset(reset),
			.clk(clk),
			.send_val(send_val),
			.recv_rdy(recv_rdy), 
			.dsel(dec_select)
		);

	DecoderVRTL #(.m(dec_in), .n(N_SAMPLES)) d
		(
			.x(dec_select),
			.y(dec_out)
		);  

    generate
        genvar i;
        for( i = 0; i < N_SAMPLES; i++) begin
            RegisterV #( .BIT_WIDTH(BIT_WIDTH) ) register ( .clk(clk), .reset(reset), .w(dec_select[i]), .d(recv_msg), .q(send_msg[i]) );
        end
    endgenerate

endmodule


