FLAGS = -lomnithread -lomniORB4 -std=c++11
IDL = ./idl/*.o
build:
	g++ -std=c++11 -o utils/Utils.o -c utils/Utils.cpp
	g++ -std=c++11 -o connection/Connection.o -c connection/Connection.cpp
#	g++ $(FLAGS) -c AccountImpl.cpp
