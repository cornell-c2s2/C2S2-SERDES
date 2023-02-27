// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VParallel.h for the primary calling header

#include "VParallel.h"
#include "VParallel__Syms.h"

//==========

void VParallel::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VParallel::eval\n"); );
    VParallel__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("ParallelVRTL.v", 209, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void VParallel::_eval_initial_loop(VParallel__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("ParallelVRTL.v", 209, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void VParallel::_combo__TOP__1(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_combo__TOP__1\n"); );
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
}

VL_INLINE_OPT void VParallel::_sequent__TOP__3(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_sequent__TOP__3\n"); );
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((2U & (IData)(vlTOPp->dec_out))) {
        vlTOPp->Parallel__DOT__v__DOT__b__DOT__regout 
            = vlTOPp->dta;
    }
    if (((1U & (IData)(vlTOPp->dec_out)) ? 0U : 1U)) {
        vlTOPp->Parallel__DOT__v__DOT__a__DOT__regout 
            = vlTOPp->dta;
    }
    vlTOPp->OUTPUTB = (3U & vlTOPp->Parallel__DOT__v__DOT__b__DOT__regout);
    vlTOPp->OUTPUTA = (3U & vlTOPp->Parallel__DOT__v__DOT__a__DOT__regout);
}

void VParallel::_eval(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_eval\n"); );
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

VL_INLINE_OPT QData VParallel::_change_request(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_change_request\n"); );
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData VParallel::_change_request_1(VParallel__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_change_request_1\n"); );
    VParallel* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->Parallel__DOT__v__DOT__c__DOT__count ^ vlTOPp->__Vchglast__TOP__Parallel__DOT__v__DOT__c__DOT__count));
    VL_DEBUG_IF( if(__req && ((vlTOPp->Parallel__DOT__v__DOT__c__DOT__count ^ vlTOPp->__Vchglast__TOP__Parallel__DOT__v__DOT__c__DOT__count))) VL_DBG_MSGF("        CHANGE: ParallelVRTL.v:59: Parallel.v.c.count\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__Parallel__DOT__v__DOT__c__DOT__count 
        = vlTOPp->Parallel__DOT__v__DOT__c__DOT__count;
    return __req;
}

#ifdef VL_DEBUG
void VParallel::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VParallel::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rec_val & 0xfeU))) {
        Verilated::overWidthError("rec_val");}
    if (VL_UNLIKELY((reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((send_rdy & 0xfeU))) {
        Verilated::overWidthError("send_rdy");}
}
#endif  // VL_DEBUG
