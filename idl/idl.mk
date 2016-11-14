.PHONY:	idl
idl:
	omniidl -bcxx Account.idl
	idlj -fall Account.idl
cxx:
	g++ -c AccountSK.cc
java:
	cd corbaAccount && javac -cp . *.java
clean:
	rm -rf Account.hh AccountSK.cc corbaAccount *.o 
