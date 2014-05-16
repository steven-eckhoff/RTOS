# ROOT=../../../
# BOARD=lm3s8962

include $(ROOT)/boards/$(BOARD)/makedefs

IPATH := $(ROOT)/drivers \
	 $(ROOT)

VAPTH := $(ROOT)/drivers

SRCS=$(shell ls *.c)

OBJS=$(SRCS:.c=.o)

liblm3s8962.a: $(OBJS)

clean:
	-rm *.[oda]
