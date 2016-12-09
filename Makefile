.PHONY:	idl cxx java
all:	idl cxx java

idl:
	cd idl && make -f idl.mk idl 
	cd idl && make -f idl.mk cxx
	cd idl && make -f idl.mk java
cxx:
	cd cxx && make -f cxx.mk build
java:	
	cd java && make -f java.mk build
clean:
	cd idl && make -f idl.mk clean
	cd cxx && make -f cxx.mk clean
	cd java && make -f java.mk clean
