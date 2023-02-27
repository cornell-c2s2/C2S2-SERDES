// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VPARALLEL_H_
#define _VPARALLEL_H_  // guard

#include "verilated.h"

//==========

class VParallel__Syms;

//----------

VL_MODULE(VParallel) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_OUT8(EN,0,0);
    VL_OUT8(OUTPUTA,1,0);
    VL_OUT8(OUTPUTB,1,0);
    VL_OUT8(dec_out,1,0);
    VL_OUT8(dec_select,0,0);
    VL_OUT8(rec_rdy,0,0);
    VL_IN8(rec_val,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(send_rdy,0,0);
    VL_OUT8(send_val,0,0);
    VL_IN(dta,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*1:0*/ Parallel__DOT__v__DOT__c__DOT__count;
    IData/*31:0*/ Parallel__DOT__v__DOT__a__DOT__regout;
    IData/*31:0*/ Parallel__DOT__v__DOT__b__DOT__regout;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*1:0*/ __Vchglast__TOP__Parallel__DOT__v__DOT__c__DOT__count;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    VParallel__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(VParallel);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    VParallel(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~VParallel();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VParallel__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VParallel__Syms* symsp, bool first);
  private:
    static QData _change_request(VParallel__Syms* __restrict vlSymsp);
    static QData _change_request_1(VParallel__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(VParallel__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(VParallel__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(VParallel__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(VParallel__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__3(VParallel__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(VParallel__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
