/*
*  main.cpp
*
*  sc_main function
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 10:04:13 Created.
*
*  Description: This file mainly instantiate the PE unit. 
*
*/
//The Test structure looks like this:
/////////////////////////////////////////////////////////////////  
//.______________________.     .__________________________.
//|  Driver              |     |  Pe_unit                 |   
//|                  clk |<-|->| clk                      |
//|           cfg_enable |--|->| cfg_enable               |
//|         cfg_data<32> |--|->| cfg_data<32>             |
//|                a<32> |--|->| i_east<32>    o_east<32> |---->|
//|                b<32> |--|->| i_west<32>    o_west<32> |---->|
//|                c<32> |--|->| i_north<32>  o_north<32> |---->|
//|                d<32> |--|->| i_south<32>  o_south<32> |---->|
//.______________________.  |  .__________________________.     |
//                          |                                   |
//                          |                                   |
//                          |     .______________________.      |
//                          |     |  Monitor             |      |
//                          |---->| clk      peout_e<32> |<-----|
//                          |---->| a<32>    peout_w<32> |<-----|
//                          |---->| b<32>    peout_n<32> |<-----|
//                          |---->| c<32>    peout_s<32> |<-----|
//                          |---->| d<32>                |<-----|
//                                .______________________.
/////////////////////////////////////////////////////////////////

#include "frame_app.h"
#include "debugger.h"
#include "initializer.h"
#include "driver.h"
#include "monitor.h"
#include "pe_unit.h"
#include "bus.h"
#include "memory.h"
#include "bus_master.h"
#include "bus_arbiter.h"
#include "topsystem.h"
#include <sys/stat.h>
#define DBG_TEST
#define TOP_TEST

FILE *fout, *fout2;

void config_parse( string );
Topsys *topsys;

Initializer *init;
int sc_main(int argc, char* argv[], char **envp)
{
	sc_report_handler::set_actions(SC_WARNING, SC_DO_NOTHING);
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	fout = fopen("pe_v1_out", "w");
	fout2 = fopen("pe_v1_out2", "w");
	cout << "CoreMain" << endl;
#ifdef TOP_TEST
	

	init = new Initializer;
	
	string conf_file = "pesim.cfg";
	// check whether a configuration file exists or not.
	struct stat buf;
	if( stat( conf_file.c_str(), &buf ) < 0 )
	{
		cout << conf_file << ": No such configuration file." << endl;
		exit(1);
	}
	config_parse( conf_file );

	
	topsys = new Topsys((sc_module_name)"top", init, argc, argv, envp);
	
	//CoreMain(argc, argv, envp, topsys);
#ifdef DBG_TEST
	cout << "debugger" << endl;

	ConsoleDebugger debugger(topsys);
	
	debugger.Run();
#endif

	delete topsys;
	delete init;
#endif

#ifdef BUS_TEST
	int en_trace = 1;
	sc_clock clock1;
	//module instances
	Bus_master *master_nb;
	Bus *bus;
	Bus_arbiter *arbiter;
	Bus_slow_mem *mem_slow;
	cout << 0 << endl;


	master_nb = new Bus_master(" ", 3, 0x80, false, 10);
	bus = new Bus("bus");
	arbiter = new Bus_arbiter("arbiter");
	mem_slow = new Bus_slow_mem("mem_slow", 0x80, 0x1ff, 1);
	//connect instance
	master_nb->clock(clock1);
	bus->clock(clock1);
	master_nb->bus_port(*bus);
	bus->arbiter_port(*arbiter);
	bus->slave_port(*mem_slow);
	mem_slow->clock(clock1);
	
	sc_trace_file *trfile = sc_create_vcd_trace_file("trace");
	((vcd_trace_file *)trfile)->sc_set_vcd_time_unit(-12); 
	if (en_trace)
	{
		sc_trace(trfile, clock1,  "CLK");
		#ifdef TRACE_BUS_INFO
		sc_trace(trfile, master_nb->raddr,  "M_RADDR");
		sc_trace(trfile, master_nb->rdata,  "M_RDATA");
		sc_trace(trfile, master_nb->waddr,  "M_WADDR");
		sc_trace(trfile, master_nb->wdata,  "M_WDATA");	
		#endif
		
	}
	
	sc_start(1000, SC_NS);
	
    if (master_nb) {delete master_nb; master_nb = 0;}
    if (mem_slow) {delete mem_slow; mem_slow = 0;}
    if (bus) {delete bus; bus = 0;}
    if (arbiter) {delete arbiter; arbiter = 0;}
	
	sc_close_vcd_trace_file(trfile);
	
#endif

#ifdef PE_TEST
	Pe_unit tstpe("pe");
	Driver tstdrv("driver");
	Monitor tstmtr("monitor");

	sc_signal<sc_int<32> > tstin[4], tstout[4];
	sc_signal<sc_uint<32> > tstcfgdata;
	sc_signal<bool> tstcfgeable;
	sc_clock clock1("clk1", 2, SC_NS, 0.5);
	
	tstpe.in[EAST](tstin[EAST]);
	tstpe.in[WEST](tstin[WEST]);
	tstpe.in[NORTH](tstin[NORTH]);
	tstpe.in[SOUTH](tstin[SOUTH]);
	tstpe.out[EAST](tstout[EAST]);
	tstpe.out[WEST](tstout[WEST]);
	tstpe.out[NORTH](tstout[NORTH]);
	tstpe.out[SOUTH](tstout[SOUTH]);
	tstpe.cfg_data(tstcfgdata);
	tstpe.cfg_enable(tstcfgeable);
	tstpe.clk(clock1);

	tstdrv.a(tstin[EAST]);
	tstdrv.b(tstin[WEST]);
	tstdrv.c(tstin[NORTH]);
	tstdrv.d(tstin[SOUTH]);
	tstdrv.cfg_data(tstcfgdata);
	tstdrv.cfg_enable(tstcfgeable);
	tstdrv.clk(clock1);

	tstmtr.a(tstin[EAST]);
	tstmtr.b(tstin[WEST]);
	tstmtr.c(tstin[NORTH]);
	tstmtr.d(tstin[SOUTH]);
	tstmtr.peout_e(tstout[EAST]);
	tstmtr.peout_w(tstout[WEST]);
	tstmtr.peout_n(tstout[NORTH]);
	tstmtr.peout_s(tstout[SOUTH]);
	tstmtr.clk(clock1);

	sc_trace_file *tf;
	tf = sc_create_vcd_trace_file("Wave");
	sc_trace(tf, clock1, "Clk");
	sc_trace(tf, tstcfgdata, "cfgdata");
	sc_trace(tf, tstcfgeable, "cfgenable");
	sc_trace(tf, tstin[EAST], "in.east");
	sc_trace(tf, tstin[WEST], "in.west");
	sc_trace(tf, tstin[NORTH], "in.north");
	sc_trace(tf, tstin[SOUTH], "in.south");
	sc_trace(tf, tstout[EAST], "out.east");
	sc_trace(tf, tstout[WEST], "out.west");
	sc_trace(tf, tstout[NORTH], "out.north");
	sc_trace(tf, tstout[SOUTH], "out.south");
	sc_start(60, SC_NS);
	sc_close_vcd_trace_file(tf);
#endif

#ifdef PE_ARRAY_TEST
	Pe_unit pe1("pe");
	Pe_unit pe2("pe");
	Pe_unit pe3("pe");
	Pe_unit pe4("pe");
	sc_signal<sc_int<32> > h_a_1, h_a_2, h_a_3, h_a_4;
	sc_signal<sc_int<32> > h_b_1, h_b_2, h_b_3, h_b_4;
	sc_signal<sc_int<32> > v_a_1, v_a_2, v_a_3, v_a_4;
	sc_signal<sc_int<32> > v_b_1, v_b_2, v_b_3, v_b_4;
	/************************************************************************/
	/* 1-2水平内部互联                                                      */
	/************************************************************************/
	pe1.in[EAST](h_a_1);
	pe1.out[EAST](h_b_1);
	pe2.out[WEST](h_a_1);
	pe2.in[WEST](h_b_1);
	/************************************************************************/
	/* 1-2水平外部互联                                                      */
	/************************************************************************/
	pe1.in[WEST](h_a_2);
	pe1.out[WEST](h_b_2);
	pe2.out[EAST](h_a_2);
	pe2.in[EAST](h_b_2);
	/************************************************************************/
	/* 3-4水平内部互联                                                      */
	/************************************************************************/
	pe3.in[EAST](h_a_3);
	pe3.out[EAST](h_b_3);
	pe4.out[WEST](h_a_3);
	pe4.in[WEST](h_b_3);
	/************************************************************************/
	/* 3-4水平外部互联                                                      */
	/************************************************************************/
	pe3.in[WEST](h_a_4);
	pe3.out[WEST](h_b_4);
	pe4.out[EAST](h_a_4);
	pe4.in[EAST](h_b_4);
	/************************************************************************/
	/* 1-3垂直内部互联                                                      */
	/************************************************************************/
	pe1.in[SOUTH](v_a_1);
	pe1.out[SOUTH](v_b_1);
	pe3.out[NORTH](v_a_1);
	pe3.in[NORTH](v_b_1);
	/************************************************************************/
	/* 2-4垂直内部互联                                                      */
	/************************************************************************/
	pe2.in[SOUTH](v_a_3);
	pe2.out[SOUTH](v_b_3);
	pe4.out[NORTH](v_a_3);
	pe4.in[NORTH](v_b_3);
	/************************************************************************/
	/* 1-3垂直外部互联                                                      */
	/************************************************************************/
	pe1.in[NORTH](v_a_2);
	pe1.out[NORTH](v_b_2);
	pe3.out[SOUTH](v_a_2);
	pe3.in[SOUTH](v_b_2);
	/************************************************************************/
	/* 2-4垂直外部互联                                                      */
	/************************************************************************/
	pe2.in[NORTH](v_a_4);
	pe2.out[NORTH](v_b_4);
	pe4.out[SOUTH](v_a_4);
	pe4.in[SOUTH](v_b_4);	
#endif

	fclose(fout);
	fclose(fout2);
	return 0;
}