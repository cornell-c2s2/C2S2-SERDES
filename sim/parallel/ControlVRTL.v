module ControlVRTL 
#(
    parameter dib = 1, //#decoder input lines
    parameter dobreg = 1  //#decoder output lines
)(
    input   logic recv_val,
    input   logic send_rdy,
    input   logic reset,
    input   logic clk,

    output  logic send_val,
    output  logic recv_rdy,
    output  logic [dib-1:0] dsel //input to decoder
);
    parameter [1:0] Init = 2'b00;
    parameter [1:0] State1 = 2'b01;
    parameter [1:0] State2 = 2'b10; 

    logic [dobreg-1:0] count; //counter
    logic [1:0] Scurr;
    logic [1:0] Snext;

    always @(recv_val, send_rdy, Scurr) begin 
       case(Scurr)
            Init: begin 
                if ((recv_val == 1) & (count != dobreg)) 
                    Snext = State1;
                else if ((recv_val == 1) & (count == dobreg)) 
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
