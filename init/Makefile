PART=LM3S8962

#
# Include the common make definitions.
#
include $(ROOT)/boards/$(BOARD)/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH =	$(SRCARCH)		\
	$(SRCPROC)		\
	$(SRCBOARD)		\
	$(ROOT)/boards/$(BOARD)	\
	$(ROOT)/lib		\
	$(ROOT)/kernel		

#
# Where to find header files that do not live in the source directory.
#
IPATH =	$(SRCARCH)		\
	$(SRCARCH)/include	\
	$(SRCPROC)		\
	$(SRCBOARD)		\
	$(ROOT)

#
# The default rule, which causes the hello example to be built.
#
all: linkscript main.axf

linkscript: $(BOARD).ld
	cp $(ROOT)/boards/$(BOARD)/$(BOARD).ld ./main.ld

#
# The rule to clean out all the build products.
#
clean:
	-rm *.axf
	-rm *.bin
	-rm *.[od]
#
# Rules for building the hello example.
#
main.axf: main.o
main.axf: startup.o
main.axf: kernel.a
main.axf: liblm3s8962.a
main.axf: proc.a
main.axf: kernellib.a
main.axf: main.ld

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard *.d} __dummy__
endif
