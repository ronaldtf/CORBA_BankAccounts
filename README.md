# CorbaExchange
This is an example of how to implement Corba interfaces in Java an C++.
I have used a simple example of bank accounts where there is a server with the list of accounts and clients adding 
new accounts and new operations.
The example is simple. However, the idea is to show the connection between a client and a server and see how they
exchange objects through Corba.

# Building the project
Simply run the Makefile. It compiles the idl library for both java and C++, as well as the source code for both languages.

# Run the application
## Java
To run the java version, run the following commands (in the java folder):

1. *tnameserv -ORBInitialPort 9999*
2. Server: *java server.Server*
3. Client: *java client.Client*

## C++

1. *tnameserv -ORBInitialPort 9999*
2. Server: *cd cxx && ./server/Server*
3. Client: *cd cxx && ./client/Client*
