.PHONY:	idl
idl:
	omniidl -bcxx Account.idl
	idlj -fall Account.idl
cxx:
	g++ -c AccountSK.cc
clean:
	rm -rf Account.hh AccountSK.cc corbaAccount *.o 
