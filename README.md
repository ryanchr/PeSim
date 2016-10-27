# Simulator of CPU + 2D Systolic Array based system
This project is meant to create a simulator of system integrating an ARM cpu and a 2D systolic array consisting of processing elements. 

**Introduction to the top system**
Console: PeSim User's command
Config File: user's configuration file for the 2D systolic array
Debugger: for debugging the code running on the system
Profiler: performance profiling
System: 
1) Core: ARM processor (SimpleScalar)
2) Pe Array: a 2D systolic array consisting of processing elements (PE)
3) AHB: bus connecting ARM, the 2D Pe Array, and the memory
4) Memory: main memory for storing data and instructions


**Simulator**
//The simulator structure looks like this:
/////////////////////////////////////////////////////////////////  
//.______________________.     .__________________________.
//|  Driver              |     |  Pe_Array                |   
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

**Files**
1. pesim.cfg: configuration files of the ARM processor
2. systemc.h: systemC header file

**How to Run**
1. make sure SystemC has been installed on your computer
2. compile the files and run the generated executable file






 
