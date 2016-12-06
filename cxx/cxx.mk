FLAGS = -lomnithread -lomniORB4 -std=c++11
IDL = ./idl/*.o
build:
	g++ -std=c++11 -o account/Utils.o -c account/Utils.cpp
	g++ -std=c++11 -o connection/Connection.o -c connection/Connection.cpp
#	g++ $(FLAGS) -c AccountImpl.cpp
