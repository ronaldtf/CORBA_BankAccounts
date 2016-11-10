FLAGS = -lomnithread -lomniORB4 -std=c++11
IDL = ../idl/*.o
build:
	g++ $(FLAGS) -c AccountImpl.cpp
