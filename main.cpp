#include "stim.h"
#include "filter.h"
#define CLOCK_PERIOD 1.0

using namespace sc_dt;
using namespace sc_core;

int sc_main(int argc, char *argv[]) {
  //Create modules and signals
  stim testbench("testbench");
  adder dut("dut", 1);
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");

  //Create sc_signal channels
  sc_signal<sc_ufixed_fast<5, 0> > s_i_x_msg;
  sc_signal<bool> s_i_x_rdy;
  sc_signal<bool> s_i_x_vld;
  sc_signal<sc_ufixed_fast<8, 3> > s_o_y_msg;
  sc_signal<bool> s_o_y_rdy;
  sc_signal<bool> s_o_y_vld;

  //Connect FIFO channels with modules
  testbench.i_clk(clk);
  testbench.o_rst(rst);
  dut.i_clk(clk);
  dut.i_rst(rst);
  testbench.o_x.msg(s_i_x_msg);
  testbench.o_x.vld(s_i_x_vld);
  testbench.o_x.rdy(s_i_x_rdy);
  testbench.i_y.msg(s_o_y_msg);
  testbench.i_y.vld(s_o_y_vld);
  testbench.i_y.rdy(s_o_y_rdy);
  dut.i_x_port.msg(s_i_x_msg);
  dut.i_x_port.vld(s_i_x_vld);
  dut.i_x_port.rdy(s_i_x_rdy);
  dut.o_y_port.msg(s_o_y_msg);
  dut.o_y_port.vld(s_o_y_vld);
  dut.o_y_port.rdy(s_o_y_rdy);

  sc_start(100, SC_NS);
  return 0;
}
