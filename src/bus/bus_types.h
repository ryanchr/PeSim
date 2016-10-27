#ifndef ME_BUS_TYPES_H
#define ME_BUS_TYPES_H

#include <stdio.h>
#include <systemc.h>
#include "types.h"

enum bus_status { BUS_OK = 0
, BUS_REQUEST
, BUS_WAIT
, BUS_ERROR };

// needed for more readable debug output
extern char bus_status_str[4][20]; 

struct Bus_request;
typedef sc_pvector<Bus_request *> bus_request_vec;

/*----------------------------------------------------------------------------
  --- Enumeration type for the read/write opterion specification.
  ---------------------------------------------------------------------------*/

typedef enum {
    BUS_RD = 0,
    BUS_WR = 1
} ahb_hwrite;

/*----------------------------------------------------------------------------
  --- Enumeration type for the HREADY signal.
  ---------------------------------------------------------------------------*/

typedef enum {
    DATA_READY = 1,
    DATA_BUSY = 0
} ahb_hready;

#endif
