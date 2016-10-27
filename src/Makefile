TARGET_ARCH = linux
CC     = g++
OPT    = #-O2 # -O3
DEBUG  = -g
OTHER  = -w # -Wall -Wno-deprecated
CFLAGS = $(OPT) $(OTHER)
SYSTEMC = /usr/local/systemc-2.2
INCDIR = -I$(SYSTEMC)/include\
		-I./test_bench\
		-I./rca_unit\
		-I./frame_work\
		-I./memory\
		-I./bus\
		-I./core\
		-I./config\
		-I./topsystem\
		-I./debug\
		-I./peripherals\
		-include/usr/include/errno.h
LIBDIR = -L$(SYSTEMC)/lib-$(TARGET_ARCH)
LIBS = -lsystemc

YACC    = bison
LEX     = flex
LIBLEX	= -lfl 

LDFLAGS= $(LIBLEX)

OBJDIR = $(shell pwd)/obj

APP=../pesim

SRCS=main.cpp\
	./config/config.tab.c\
	./config/config.lex.c\
	./config/initializer.cpp\
	./frame_work/frame_app.cpp\
	./frame_work/tools.cpp\
	./test_bench/monitor.cpp\
	./rca_unit/pe_fu.cpp\
	./rca_unit/pe_switchbox.cpp\
	./rca_unit/pe_switchmatrix.cpp\
	./rca_unit/pe_unit.cpp\
	./rca_unit/pe_cfgmem.cpp\
	./memory/reg_file.cpp\
	./memory/core_memory.cpp\
	./bus/bus.cpp\
	./bus/bus_arbiter.cpp\
	./bus/bus_types.cpp\
	./core/bus_master.cpp\
	./core/main.cpp\
	./core/misc.cpp\
	./core/options.cpp\
	./core/stats.cpp\
	./core/dlite.cpp\
	./core/range.cpp\
	./core/symbol.cpp\
	./core/sim-safe.cpp\
	./core/syscall.cpp\
	./core/memory.cpp\
	./core/machine.cpp\
	./core/eval.cpp\
	./core/loader.cpp\
	./core/regs.cpp\
	./core/eio.cpp\
	./core/libexo.cpp\
	./core/core_endian.cpp\
	./core/itrc.cpp\
	./peripherals/timer.cpp\
	./topsystem/topsystem.cpp\
	./debug/debugger.cpp\
	./debug/token.cpp\
	./debug/controler.cpp\
	./rca_unit/pe_controller.cpp

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all:$(OBJS)
	$(CC) -o $(APP) $(OBJS) $(LIBDIR) $(INCDIR) $(LIBS) $(CFLAGS) $(LDFLAGS)
	
./config/config.lex.c: ./config/config.lex
	$(LEX) -o$@ $<

./config/config.tab.c: ./config/config.y
	$(YACC) -o$@ -d $<
	
./core/exolex.c: ./core/exolex.l
	$(LEX) -o$@ $<
	
%.o: %.cpp
	$(CC) -c $< $(INCDIR) $(CFLAGS) -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJS)
	rm -f ./config/config.lex.c ./config/config.lex.h
	rm -f ./config/config.tab.c ./config/config.tab.h
