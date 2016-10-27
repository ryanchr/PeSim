/*
*  pe_unit.cpp
*
*  Reconfigurable unit Module implementation
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-18 10:32:20 Created.
*
*  Description: This file mainly implements the reconfigurable unit Module. 
*
*/
#include "pe_unit.h"


//void Pe_unit::config(sc_uint<32> cfwords)
 Pe_unit:: ~Pe_unit(){}


void Pe_unit::fetchdata(Uint32 address, Uint32 *data)
{
	bus_master_port->Read(unique_priority,data, address);   //get data by bus read
	while ((bus_master_port->get_status(unique_priority) != BUS_OK) &&
		(bus_master_port->get_status(unique_priority) != BUS_ERROR))
	{
		wait();
	}


	if (bus_master_port->get_status(unique_priority) == BUS_ERROR)
	{
		printf("ERROR cannot read from %x\n", 
			sc_time_stamp(), address);
            exit(0);
	}

}

void Pe_unit::in_switchbox()
{

#ifdef ENABLE_DEBUG
	cout << "********************************************************" << endl;
	cout << "void Pe_unit::in_switchbox()	at time" << sc_time_stamp() << endl;
	cout << "in[n] = " << in[0] 
	<< "	in[e] = " << in[1] 
	<< "	in[w] = " << in[2]
	<< "	in[s] = " << in[3]
	<< endl;
#endif

	int i;
	for (i = 0; i < FROM_NEIGHBOR_NUM; i++)
	{
		pe_swichbox.from_neighbor[i] = in[i];
	}
	pe_swichbox.sw_neighbor_in();
}

void Pe_unit::out_switchbox()
{
	pe_swichbox.sw_neighbor_out();
	int i;
	for(i = 0; i < TO_NEIGHBOR_NUM; i++)
	{
		out[i] = pe_swichbox.to_neighbor[i];
	}
}

void Pe_unit::in_fu()
{

#ifdef ENALBE_DEBUG
	cout << "********************************************************" << endl;
	cout << "void Pe_unit::in_fu()	  at time " << sc_time_stamp << endl;
#endif

	int i;
	for(i = 0; i < TO_FU_NUM; i++)
	{
#ifdef ENALBE_DEBUG
		cout << "pe_fu.from_switchbox[" << i << "] = " << pe_fu.from_switchbox[i] << endl; 
#endif
		pe_fu.from_switchbox[i] = pe_swichbox.to_fu[i];
	}
}

void Pe_unit::out_fu()
{
	int i;
	for(i = 0; i < FROM_FU_NUM; i++)
	{
		pe_swichbox.from_fu[i] = pe_fu.to_switchbox[i];
	}
}

void Pe_unit::do_compute()
{
	pe_fu.compute(&pe_fu);
}



void Pe_unit::config()
{
    Uint32 data=0;
    while(1)
    {
    cfg_finish = 0;
    if(cfg_enable)
	    { 
		cout << "pe start config at time-----------\n " << sc_time_stamp() << endl;
             pe_cfgmem->Read(CFG_DATA ,&data);
		sc_uint<32> cfwords = (Uint32)(data);
            printf("-----+++++++++----config data = 0x%x-----++++++++----\n" , data);
		pe_swichbox.config(cfwords);
		pe_fu.config(cfwords);
             cfg_finish = 1;
             wait(3,SC_NS);
	    }
    wait();
    }
}



void Pe_unit::main()
{
      Uint32  outvalue;
      while(1)
      {
        	if ((!cfg_enable)/*&&input_finish*/)
        	{
        		cout << "pe start compute at time " << sc_time_stamp() << endl;
        		this->in_switchbox();
        		this->in_fu();
        		this->do_compute();
        		this->out_fu();
        		this->out_switchbox();
                
                for (int i=0;i<TO_NEIGHBOR_NUM;i++)
                {
                    outvalue = (Uint32)out[i].read();
                    pe_cfgmem->Write(OUTPUT_DATA,&outvalue);
                    cout<<"-------------out--------"<<outvalue<<endl;
                }
        	}
            
        wait();
      }
}


