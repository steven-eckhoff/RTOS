


all:
	@for i in $(DIRS);				\
	 do 						\
	 	if [ -f $${i}/Makefile ];		\
		then					\
			make -C $${i} || exit $${?};	\
		fi					\
	done
