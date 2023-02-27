// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VControl.h for the primary calling header

#include "VControl.h"
#include "VControl__Syms.h"

//==========

void VControl::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VControl::eval\n"); );
    VControl__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("ControlVRTL.v", 88, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void VControl::_eval_initial_loop(VControl__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("ControlVRTL.v", 88, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void VControl::_sequent__TOP__1(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_sequent__TOP__1\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->Control__DOT__v__DOT__Scurr = ((IData)(vlTOPp->reset)
                                            ? 0U : (IData)(vlTOPp->Control__DOT__v__DOT__Snext));
    vlTOPp->recv_rdy = ((0U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                        | ((1U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                           | (2U != (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))));
    vlTOPp->send_val = ((0U != (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                        & ((1U != (IData)(vlTOPp->Control__DOT__v__DOT__Scurr)) 
                           & (2U == (IData)(vlTOPp->Control__DOT__v__DOT__Scurr))));
}

VL_INLINE_OPT void VControl::_combo__TOP__3(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_combo__TOP__3\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
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

void VControl::_eval(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_eval\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    vlTOPp->_combo__TOP__3(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

VL_INLINE_OPT QData VControl::_change_request(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_change_request\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData VControl::_change_request_1(VControl__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_change_request_1\n"); );
    VControl* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->Control__DOT__v__DOT__count ^ vlTOPp->__Vchglast__TOP__Control__DOT__v__DOT__count));
    VL_DEBUG_IF( if(__req && ((vlTOPp->Control__DOT__v__DOT__count ^ vlTOPp->__Vchglast__TOP__Control__DOT__v__DOT__count))) VL_DBG_MSGF("        CHANGE: ControlVRTL.v:19: Control.v.count\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__Control__DOT__v__DOT__count 
        = vlTOPp->Control__DOT__v__DOT__count;
    return __req;
}

#ifdef VL_DEBUG
void VControl::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VControl::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((recv_val & 0xfeU))) {
        Verilated::overWidthError("recv_val");}
    if (VL_UNLIKELY((reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((send_rdy & 0xfeU))) {
        Verilated::overWidthError("send_rdy");}
}
#endif  // VL_DEBUG
