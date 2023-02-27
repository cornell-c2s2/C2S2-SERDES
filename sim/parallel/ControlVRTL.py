# This is the PyMTL wrapper for the corresponding Verilog RTL model RegIncVRTL.

from pymtl3 import *
from pymtl3.stdlib import stream
from pymtl3.passes.backends.verilog import *

#model.apply( DefaultPassGroup(vcdwave='parallel-sim') )


class ControlVRTL( VerilogPlaceholder, Component ):

  # Constructor

  def construct( s, dib, dobreg):
    # If translated into Verilog, we use the explicit name

    s.set_metadata( VerilogTranslationPass.explicit_module_name, 'Control' )

    # Interface
    s.recv_val  = InPort(1)
    s.send_rdy  = InPort(1)
    
    s.send_val = OutPort(1)
    s.recv_rdy = OutPort(1)
    s.dsel = OutPort(dib)

Control = ControlVRTL