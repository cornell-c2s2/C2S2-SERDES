// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VParallel.h for the primary calling header

#include "VParallel.h"
#include "VParallel__Syms.h"

//==========

VL_CTOR_IMP(VParallel) {
    VParallel__Syms* __restrict vlSymsp = __VlSymsp = new VParallel__Syms(this, name());
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void VParallel::__Vconfigure(VParallel__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

VParallel::~VParallel() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void VParallel::_settle__TOP__2(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_settle__TOP__2\n"); );
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->rec_val) & (0U != (IData)(vlTOPp->Parallel__DOT__v__DOT__c__DOT__count)))) {
        vlTOPp->Parallel__DOT__v__DOT__c__DOT__count 
            = (3U & ((IData)(1U) + (IData)(vlTOPp->Parallel__DOT__v__DOT__c__DOT__count)));
        vlTOPp->EN = 1U;
        vlTOPp->rec_rdy = 1U;
        vlTOPp->send_val = 0U;
    } else {
        if (((IData)(vlTOPp->rec_val) & (0U == (IData)(vlTOPp->Parallel__DOT__v__DOT__c__DOT__count)))) {
            vlTOPp->Parallel__DOT__v__DOT__c__DOT__count = 0U;
            vlTOPp->EN = 0U;
            vlTOPp->rec_rdy = 0U;
            vlTOPp->send_val = 1U;
        } else {
            vlTOPp->EN = 0U;
            vlTOPp->rec_rdy = 1U;
            vlTOPp->send_val = 0U;
        }
    }
    vlTOPp->dec_out = (3U & ((IData)(1U) << (IData)(vlTOPp->dec_select)));
    vlTOPp->OUTPUTB = (3U & vlTOPp->Parallel__DOT__v__DOT__b__DOT__regout);
    vlTOPp->OUTPUTA = (3U & vlTOPp->Parallel__DOT__v__DOT__a__DOT__regout);
}

void VParallel::_eval_initial(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_eval_initial\n"); );
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void VParallel::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::final\n"); );
    // Variables
    VParallel__Syms* __restrict vlSymsp = this->__VlSymsp;
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VParallel::_eval_settle(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_eval_settle\n"); );
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void VParallel::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_ctor_var_reset\n"); );
    // Body
    EN = VL_RAND_RESET_I(1);
    OUTPUTA = VL_RAND_RESET_I(2);
    OUTPUTB = VL_RAND_RESET_I(2);
    clk = VL_RAND_RESET_I(1);
    dec_out = VL_RAND_RESET_I(2);
    dec_select = VL_RAND_RESET_I(1);
    dta = VL_RAND_RESET_I(32);
    rec_rdy = VL_RAND_RESET_I(1);
    rec_val = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    send_rdy = VL_RAND_RESET_I(1);
    send_val = VL_RAND_RESET_I(1);
    Parallel__DOT__v__DOT__c__DOT__count = VL_RAND_RESET_I(2);
    Parallel__DOT__v__DOT__a__DOT__regout = VL_RAND_RESET_I(32);
    Parallel__DOT__v__DOT__b__DOT__regout = VL_RAND_RESET_I(32);
    __Vchglast__TOP__Parallel__DOT__v__DOT__c__DOT__count = VL_RAND_RESET_I(2);
}
