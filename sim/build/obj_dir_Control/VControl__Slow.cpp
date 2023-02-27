// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VControl.h for the primary calling header

#include "VControl.h"
#include "VControl__Syms.h"

//==========
CData/*1:0*/ VControl::__Vtable1_Control__DOT__v__DOT__Snext[64];

VL_CTOR_IMP(VControl) {
    VControl__Syms* __restrict vlSymsp = __VlSymsp = new VControl__Syms(this, name());
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void VControl::__Vconfigure(VControl__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

VControl::~VControl() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void VControl::_settle__TOP__2(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_settle__TOP__2\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->recv_rdy = ((0U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                        | ((1U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                           | (2U != (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))));
    vlTOPp->send_val = ((0U != (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                        & ((1U != (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                           & (2U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))));
    if ((0U != (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))) {
        if ((1U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))) {
            vlTOPp->dsel = (1U & (IData)(vlTOPp->Control__DOT__v__DOT__count));
            vlTOPp->Control__DOT__v__DOT__count = (3U 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->Control__DOT__v__DOT__count)));
        } else {
            if ((2U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))) {
                vlTOPp->dsel = (1U & (IData)(vlTOPp->Control__DOT__v__DOT__count));
            } else {
                vlTOPp->Control__DOT__v__DOT__count = 0U;
                vlTOPp->dsel = 0U;
            }
        }
    }
    vlTOPp->__Vtableidx1 = (((IData)(vlTOPp->send_rdy) 
                             << 5U) | (((IData)(vlTOPp->Control__DOT__v__DOT__count) 
                                        << 3U) | (((IData)(vlTOPp->recv_val) 
                                                   << 2U) 
                                                  | (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))));
    vlTOPp->Control__DOT__v__DOT__Snext = vlTOPp->__Vtable1_Control__DOT__v__DOT__Snext
        [vlTOPp->__Vtableidx1];
}

void VControl::_eval_initial(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_eval_initial\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void VControl::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::final\n"); );
    // Variables
    VControl__Syms* __restrict vlSymsp = this->__VlSymsp;
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VControl::_eval_settle(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_eval_settle\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void VControl::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    dsel = VL_RAND_RESET_I(1);
    recv_rdy = VL_RAND_RESET_I(1);
    recv_val = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    send_rdy = VL_RAND_RESET_I(1);
    send_val = VL_RAND_RESET_I(1);
    Control__DOT__v__DOT__count = VL_RAND_RESET_I(2);
    Control__DOT__v__DOT__Scurr = VL_RAND_RESET_I(2);
    Control__DOT__v__DOT__Snext = VL_RAND_RESET_I(2);
    __Vtableidx1 = 0;
    __Vtable1_Control__DOT__v__DOT__Snext[0] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[1] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[2] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[3] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[4] = 1U;
    __Vtable1_Control__DOT__v__DOT__Snext[5] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[6] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[7] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[8] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[9] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[10] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[11] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[12] = 1U;
    __Vtable1_Control__DOT__v__DOT__Snext[13] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[14] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[15] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[16] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[17] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[18] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[19] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[20] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[21] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[22] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[23] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[24] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[25] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[26] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[27] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[28] = 1U;
    __Vtable1_Control__DOT__v__DOT__Snext[29] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[30] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[31] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[32] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[33] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[34] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[35] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[36] = 1U;
    __Vtable1_Control__DOT__v__DOT__Snext[37] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[38] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[39] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[40] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[41] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[42] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[43] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[44] = 1U;
    __Vtable1_Control__DOT__v__DOT__Snext[45] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[46] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[47] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[48] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[49] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[50] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[51] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[52] = 2U;
    __Vtable1_Control__DOT__v__DOT__Snext[53] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[54] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[55] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[56] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[57] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[58] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[59] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[60] = 1U;
    __Vtable1_Control__DOT__v__DOT__Snext[61] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[62] = 0U;
    __Vtable1_Control__DOT__v__DOT__Snext[63] = 0U;
    __Vchglast__TOP__Control__DOT__v__DOT__count = VL_RAND_RESET_I(2);
}
