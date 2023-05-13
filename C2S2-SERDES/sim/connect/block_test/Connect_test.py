
#=========================================================================
# IntMulFixedLatRTL_test
#=========================================================================

import pytest
import random

random.seed(0xdeadbeef)

from pymtl3 import *
from pymtl3.stdlib import stream
from pymtl3.stdlib.test_utils import mk_test_case_table, run_sim
from connect.ConnectTestHarnessRTL import ConnectTestHarnessVRTL
from fxpmath import Fxp
import numpy as np
import math


#-------------------------------------------------------------------------
# TestHarness
#-------------------------------------------------------------------------


class TestHarness( Component ):

  def construct( s, connect, BIT_WIDTH = 32, N_SAMPLES = 8):

    # Instantiate models

    s.src  = stream.SourceRTL( mk_bits(BIT_WIDTH * N_SAMPLES) ) # input  = multiple smaller msgs
    s.sink = stream.SinkRTL  ( mk_bits(BIT_WIDTH * N_SAMPLES) ) # output = multiple smaller msgs
    s.connect = connect

    # Connect

    s.src.send  //= s.connect.recv 
    s.connect.send //= s.sink.recv

  def done( s ):
    return s.src.done() and s.sink.done()

  def line_trace( s ):
    return s.src.line_trace() + " > " + s.connect.line_trace() + " > " + s.sink.line_trace()

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
    return [0x00000008, 0x00000007, 0x00000006, 0x00000005, 0x00000004, 0x00000003, 0x00000002, 0x00000001,  # input to serializer   
            0x00000008, 0x00000007, 0x00000006, 0x00000005, 0x00000004, 0x00000003, 0x00000002, 0x00000001]  # output to deserializer

def sixteen_point(): # test 16 point 
    return [0x00000008, 0x00000007, 0x00000006, 0x00000005, 0x00000004, 0x00000003, 0x00000002, 0x00000001, # input to serializer   
            0x00000008, 0x00000007, 0x00000006, 0x00000005, 0x00000004, 0x00000003, 0x00000002, 0x00000001,
            0x00000008, 0x00000007, 0x00000006, 0x00000005, 0x00000004, 0x00000003, 0x00000002, 0x00000001, # output to deserializer
            0x00000008, 0x00000007, 0x00000006, 0x00000005, 0x00000004, 0x00000003, 0x00000002, 0x00000001]

def thirtytwo_point(): # test 32 point 
    return [0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,#
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01
            ] 
           
def sixtyfour_point(): # test 64 point 
    return [0x08, 0x00, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0xAA, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
            0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
            0x08, 0x07, 0xFF, 0x05, 0x04, 0x03, 0x02, 0x01,
           0x0102030405FF0708_0102030405060708_0102030405060708_0102030405060708_010203AA05060708_0102030405060708_0102030405060708_0102030405060008]

def hundredtwentyeight_point(): # test 128 point 
    return [0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 
            0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1,
            0x12345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678]
def twofiftysix(): # test 256 points 
    return [  0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b0, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
              0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 
              0b1, 0b1, 0b1, 0b1, 0b0, 0b1, 0b1, 0b1,
              #0b1234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678]
              0b1110111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110111111111111]

test_case_table = mk_test_case_table([
  (                                   "msgs                                       src_delay sink_delay BIT_WIDTH N_SAMPLES"),
  [ "eight_point",                     eight_point,                               0,        0,         32,       8         ],
  # [ "sixteen_point",                   sixteen_point,                             0,        0,         32,       16        ], 
  # [ "thirtytwo_point",                 thirtytwo_point,                           0,        0,         8,        32        ], 
  # [ "sixtyfour_point",                 sixtyfour_point,                           0,        0,         8,        64        ], 
  # [ "hundredtwentyeight_point",        hundredtwentyeight_point,                  0,        0,         4,        128       ], 
  # [ "twofiftysix",                     twofiftysix,                               0,        0,         1,        256       ],
])

def separate_transactions(array, N_SAMPLES, input = True):
  
  if(not input): 
    
    return array[N_SAMPLES::N_SAMPLES + 1]

  newarray = []
  if (input): 
    for i in range(0, len(array)):
      if(i % (N_SAMPLES + 1) != N_SAMPLES):
        newarray.append(array[i])
    print(newarray)
    return newarray
  
#-------------------------------------------------------------------------
# TestHarness
#-------------------------------------------------------------------------

@pytest.mark.parametrize( **test_case_table )
def test( test_params, cmdline_opts ):

  th = TestHarness( ConnectTestHarnessVRTL(test_params.BIT_WIDTH, test_params.N_SAMPLES), test_params.BIT_WIDTH, test_params.N_SAMPLES )

  msgs = test_params.msgs()

  th.set_param("top.src.construct",
    msgs=separate_transactions(msgs, test_params.N_SAMPLES, True),
    initial_delay=test_params.src_delay+3,
    interval_delay=test_params.src_delay )

  th.set_param("top.sink.construct",
    msgs=separate_transactions(msgs, test_params.N_SAMPLES, False),
    initial_delay=test_params.sink_delay+3,
    interval_delay=test_params.sink_delay )

  run_sim( th, cmdline_opts, duts=['connect'] )