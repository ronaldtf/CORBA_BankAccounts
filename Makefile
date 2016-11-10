.PHONY:	idl
all:	idl

idl:
	cd idl && make -f idl.mk idl 
	cd idl && make -f idl.mk cxx 
cxx:
	cd cxx && make -f cxx.mk build
java:	
