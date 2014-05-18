# ROOT = ../

IPATH := $(ROOT)		\
         $(SRCARCH)		\
         $(SRCPROC)		\
         $(SRCBOARD)		\
	 $(SRCARCH)/include

VPATH := $(ROOT)	\
         $(SRCARCH)	\
         $(SRCPROC)	\
	 $(SRCBOARD)

# BOARD = lm3s8962

include $(ROOT)/boards/$(BOARD)/makedefs

SRCS_C = $(wildcard *.c)
SRCS_S = $(wildcard *.S)

OBJS = $(SRCS_C:.c=.o)
OBJS += $(SRCS_S:.S=.o)

kernellib.a: $(OBJS)

clean:
	-rm *.[oda]
