FLAGS = -lomnithread -lomniORB4 -std=c++11
IDL = ../idl/*.o
build:
	g++ -std=c++11 -o utils/Utils.o -c utils/Utils.cpp
	g++ -std=c++11 -o connection/Connection.o -c connection/Connection.cpp
	g++ -std=c++11 -o account/DateImpl.o -c account/DateImpl.cpp
	g++ -std=c++11 -o account/OperationImpl.o -c account/OperationImpl.cpp
	g++ -std=c++11 -o account/AccountImpl.o -c account/AccountImpl.cpp
	g++ -std=c++11 -o account/AccountListImpl.o -c account/AccountListImpl.cpp
	g++ -std=c++11 -o account/DateDelegate.o -c account/DateDelegate.cpp
	g++ -std=c++11 -o account/OperationDelegate.o -c account/OperationDelegate.cpp	
	g++ -std=c++11 -o account/AccountDelegate.o -c account/AccountDelegate.cpp
	g++ -std=c++11 -o account/AccountListDelegate.o -c account/AccountListDelegate.cpp
	g++ $(FLAGS) -o server/Server ../idl/AccountSK.o connection/Connection.o account/AccountListDelegate.o account/AccountListImpl.o account/AccountDelegate.o account/AccountImpl.o account/DateDelegate.o account/DateImpl.o account/OperationDelegate.o account/OperationImpl.o utils/Utils.o server/Server.cpp
	g++ $(FLAGS) -o client/Client ../idl/AccountSK.o connection/Connection.o account/AccountListDelegate.o account/AccountListImpl.o account/AccountDelegate.o account/AccountImpl.o account/DateDelegate.o account/DateImpl.o account/OperationDelegate.o account/OperationImpl.o utils/Utils.o client/Client.cpp
clean:
	rm utils/*.o connection/*.o account/*.o client/Client server/Server
