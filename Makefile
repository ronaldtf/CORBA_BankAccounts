.PHONY:	idl
all:	idl cxx java

idl:
	cd idl && make -f idl.mk idl 
	cd idl && make -f idl.mk cxx
#	cd idl && make -f idl.mk java
cxx:
	cd cxx && make -f cxx.mk build
java:	
