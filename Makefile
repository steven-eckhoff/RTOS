
ROOT := $(shell pwd)

# Default
ifeq (x$(BOARD), x)
	BOARD = lm3s8962
endif
########## Add new boards here ##########
ifeq ($(BOARD), lm3s8962)
	SRCARCH := $(ROOT)/arch/arm
	SRCPROC := $(ROOT)/arch/arm/cortexM3
	SRCBOARD := $(ROOT)/arch/arm/lm3s8962
	ARCH = arm
	PROC = cortexM3
endif
########### End boards ##########

dirs = 	$(SRCARCH)	\
	$(SRCPROC)	\
	$(SRCBOARD)	\
	lib		\
	kernel		\
	init

export ROOT ARCH PROC BOARD SRCARCH SRCPROC SRCBOARD

all:
	@for i in $(dirs);				\
	do						\
		if [ -f $${i}/Makefile ];		\
		then					\
			make -C $${i} || exit $${?};	\
		fi;					\
	done

clean:
	@for i in $(dirs);				\
	do						\
		if [ -f $${i}/Makefile ];		\
		then					\
			make -C $${i} clean;		\
		fi;					\
	done
