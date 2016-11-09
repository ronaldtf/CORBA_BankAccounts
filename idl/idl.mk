.PHONY:	idl
idl:
	omniidl -bcxx Account.idl
	idlj -fall Account.idl
clean:
	rm -rf Account.hh AccountSK.cc corbaAccount 
