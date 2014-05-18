# ROOT = ../

IPATH := $(ROOT)		\
         $(SRCARCH)		\
         $(SRCPROC)		\
         $(SRCBOARD)		\
	 $(SRCARCH)/include

VPATH := $(ROOT)/kernel

#	 $(ROOT)	\
         $(SRCARCH)	\
         $(SRCPROC)	\
	 $(SRCBOARD)	\
	 $(ROOT)/lib

# BOARD = lm3s8962

include $(ROOT)/boards/$(BOARD)/makedefs

SRCS_C = $(wildcard *.c)
SRCS_S = $(wildcard *.S)

OBJS = $(SRCS_C:.c=.o)
OBJS += $(SRCS_S:.S=.o)

kernel.a: $(OBJS)

clean:
	-rm *.[oda]
