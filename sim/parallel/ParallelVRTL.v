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


module ParallelVRTL
#(
	parameter dec_in = 1,					//decoder inputs
    parameter regs = 1 << dec_in, 	//number of outputs to decoder/#of registers
	parameter N = 32
)(
	input logic clk, 
	input logic reset,
	input logic rec_val, 
	input logic send_rdy, 
	input logic [N-1:0] dta,

	output logic EN,
	output logic send_val, 
	output logic rec_rdy,
	output logic [regs-1:0] dec_out,
	output logic [dec_in-1:0] dec_select,
	output logic [N-1:0] OUTPUTA, 
	output logic [N-1:0] OUTPUTB
);
    //body of code
	ControlVRTL c
		(
			.EN(EN),
			.vin(rec_val),
			.rin(send_rdy),
			.vout(send_val),
			.rout(rec_rdy),
			.dsel(dec_select),
			.reset(reset)
		);

	DecoderVRTL #(.m(dec_in), .n(regs)) d
		(
			.x(dec_select),
			.y(dec_out)
		);      

	RegisterV #(.N(N)) a
		(
			.clk(clk),
			.reset(reset),
			.w(EN),
			.d(dta),
			.q(OUTPUTA)
		);
	
	RegisterV #(.N(N)) b
		(
			.clk(clk),
			.reset(reset),
			.w(EN),
			.d(dta),
			.q(OUTPUTB)
		);
endmodule



// generate block instantiation
// mydesign #(.dob(dobreg)) e
// 	(
// 		.clk(CLK),
// 		.reset(RESET),
// 		.w(DOUT[dobreg-1]),
// 		.d(DATA),
// 		.q(OUTPUT)
// 	);

// generate block for loop
// module my_design
// 	#(parameter dob=2)
// 	(input [dob-1:0] clk, reset, w, d
// 	 output [dob-1:0] q);

// 	genvar i;
// 	generate
// 		for(i=0; i<N; i=i+1) begin
// 			RegisterV u0(clk[i], rest[i], w[i], d[i], q[i]);
// 		end
// 	endgenerate
// endmodule hello
