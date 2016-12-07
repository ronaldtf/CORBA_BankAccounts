FLAGS = -lomnithread -lomniORB4 -std=c++11
IDL = ./idl/*.o
build:
	g++ -std=c++11 -o utils/Utils.o -c utils/Utils.cpp
	g++ -std=c++11 -o connection/Connection.o -c connection/Connection.cpp
	g++ -std=c++11 -o account/DateImpl.o -c account/DateImpl.cpp
	g++ -std=c++11 -o account/OperationImpl.o -c account/OperationImpl.cpp
	g++ -std=c++11 -o account/AccountImpl.o -c account/AccountImpl.cpp
	g++ -std=c++11 -o account/AccountListImpl.o -c account/AccountListImpl.cpp
