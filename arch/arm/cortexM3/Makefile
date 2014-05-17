
IPATH := $(ROOT)

include $(ROOT)/boards/$(BOARD)/makedefs

SRCS_C = $(wildcard *.c)
SRCS_S = $(wildcard *.S)

OBJS = $(SRCS_C:.c=.o)
OBJS += $(SRCS_S:.S=.o)

proc.a: $(OBJS)

clean:
	-rm *.[oda]
