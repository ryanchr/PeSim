/*
*  PE_Controller.cpp
*
*  A pe_controller model for output data to the PE array
*
*  Copyright (C) 2010  Ren Chen
*
*  2010-04-01 11:55:15 Created.
*
*  Description: The implementation of the pe_controller model. 
*
*/

#include "pe_controller.h"

PE_Controller::~PE_Controller(){}

void PE_Controller::signal_generate()
{
    /*initialize of the out ports*/
     Uint32 value=0,data[4];
      cfg_enable = 0;
     a=0;b=0;c=0;d=0;
     wait();
	/*Generate the configuration signal*/
     while(1)
       {
        output_finish = 0 ;
        signal_fetch(CFG_ENABLE ,&value);       //read config enable signal from bus
        if(((value)&0xfffffffe)==0)
             cfg_enable = (bool)((value)&0x1);
        cout<<"----------config enable signal =-------- "<<cfg_enable<<endl;
        wait();
        wait();
        if(cfg_finish)
            {
            if(!output_finish)
                {
                for(Uint32 i=0;i<4;i++)
                    {
                    signal_fetch (0xefffff18+i*4,&value);
                    data[i] = value;
                    }
                a = data[0];b = data[1];
                c = data[2];d = data[3];
                //cout<<"---a= "<<a<<"b = "<<b<<"c = "<<c<<"d = "<<d<<endl;
                output_finish = 1;
                wait(3,SC_NS);
                }
            }
        wait();        
        }
}

void PE_Controller::signal_fetch(Uint32 address, Uint32 *data)
{
	bus_master_port3->Read(unique_priority,data, address);   //get data by bus read
	while ((bus_master_port3->get_status(unique_priority) != BUS_OK) &&
		(bus_master_port3->get_status(unique_priority) != BUS_ERROR))
	{
	       printf("---------always waiting?????------------\n");
		 wait();
	}


	if (bus_master_port3->get_status(unique_priority) == BUS_ERROR)
	{
		printf("ERROR cannot read from %x\n", 
			sc_time_stamp(), address);
            exit(0);
	}

}

