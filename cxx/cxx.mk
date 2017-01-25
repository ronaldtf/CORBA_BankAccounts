FLAGS_ALL = -lomnithread -lomniORB4 $(FLAGS) -Wall
FLAGS = -std=c++11 -Wall
IDL = ../idl/*.o
build:
	g++ $(FLAGS) -o utils/Utils.o -c utils/Utils.cpp
	g++ $(FLAGS) -o connection/Connection.o -c connection/Connection.cpp
	g++ $(FLAGS) -o account/DateImpl.o -c account/DateImpl.cpp
	g++ $(FLAGS) -o account/OperationImpl.o -c account/OperationImpl.cpp
	g++ $(FLAGS) -o account/AccountImpl.o -c account/AccountImpl.cpp
	g++ $(FLAGS) -o account/AccountListImpl.o -c account/AccountListImpl.cpp
	g++ $(FLAGS) -o account/DateDelegate.o -c account/DateDelegate.cpp
	g++ $(FLAGS) -o account/OperationDelegate.o -c account/OperationDelegate.cpp	
	g++ $(FLAGS) -o account/AccountDelegate.o -c account/AccountDelegate.cpp
	g++ $(FLAGS) -o account/AccountListDelegate.o -c account/AccountListDelegate.cpp
	g++ $(FLAGS_ALL) -o server/Server ../idl/AccountSK.o connection/Connection.o account/AccountListDelegate.o account/AccountListImpl.o account/AccountDelegate.o account/AccountImpl.o account/DateDelegate.o account/DateImpl.o account/OperationDelegate.o account/OperationImpl.o utils/Utils.o server/Server.cpp
	g++ $(FLAGS_ALL) -o client/Client ../idl/AccountSK.o connection/Connection.o account/AccountListDelegate.o account/AccountListImpl.o account/AccountDelegate.o account/AccountImpl.o account/DateDelegate.o account/DateImpl.o account/OperationDelegate.o account/OperationImpl.o utils/Utils.o client/Client.cpp
doxygen:
	doxygen conf/doxygen.conf
clean:
	rm utils/*.o connection/*.o account/*.o client/Client server/Server
