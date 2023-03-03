
#=========================================================================
# IntMulFixedLatRTL_test
#=========================================================================

import pytest
import random

random.seed(0xdeadbeef)

from pymtl3 import *
from pymtl3.stdlib import stream
from pymtl3.stdlib.test_utils import mk_test_case_table, run_sim
from parallel.ParallelTestHarnessRTL import ParallelTestHarnessVRTL
from fxpmath import Fxp
import numpy as np
import math


#-------------------------------------------------------------------------
# TestHarness
#-------------------------------------------------------------------------


class TestHarness( Component ):

  def construct( s, parallel, BIT_WIDTH = 32, N_SAMPLES = 8):

    # Instantiate models

    s.src  = stream.SourceRTL( mk_bits(BIT_WIDTH) )
    s.sink = stream.SinkRTL  ( mk_bits(BIT_WIDTH * N_SAMPLES) )
    s.parallel = parallel

    # Connect

    s.src.send  //= s.parallel.recv
    s.parallel.send //= s.sink.recv

  def done( s ):
    return s.src.done() and s.sink.done()

  def line_trace( s ):
    return s.src.line_trace() + " > " + s.parallel.line_trace() + " > " + s.sink.line_trace()

def packed_msg(array, bitwidth, size): #Array of ints
  input = Bits(1)
  bit_convert = mk_bits(bitwidth)
  output = input
  for i in range(len(array)):

    output = concat( bit_convert(array[i]), output )
  
  output = output[1:bitwidth * fft_size + 1]
  
  return output

#----------------------------------------------------------------------
# Test Case Table
#----------------------------------------------------------------------

def eight_point():
    return [0x00000008, 0x00000007, 0x00000006, 0x00000005, 0x00000004, 0x00000003, 0x00000002, 0x00000001,
            0x0000000100000002000000030000000400000005000000060000000700000008]

test_case_table = mk_test_case_table([
  (                                   "msgs                                       src_delay sink_delay BIT_WIDTH N_SAMPLES"),
  [ "eight_point",                     eight_point,                               0,        0,         32,       8         ],

])

#-------------------------------------------------------------------------
# TestHarness
#-------------------------------------------------------------------------

@pytest.mark.parametrize( **test_case_table )
def test( test_params, cmdline_opts ):

  th = TestHarness( ParallelTestHarnessVRTL(test_params.BIT_WIDTH, test_params.N_SAMPLES), test_params.BIT_WIDTH, test_params.N_SAMPLES )

  msgs = test_params.msgs()

  th.set_param("top.src.construct",
    msgs=[msgs[0]],
    initial_delay=test_params.src_delay+3,
    interval_delay=test_params.src_delay )

  th.set_param("top.sink.construct",
    msgs=msgs[1:],
    initial_delay=test_params.sink_delay+3,
    interval_delay=test_params.sink_delay )

  run_sim( th, cmdline_opts, duts=['parallel'] )