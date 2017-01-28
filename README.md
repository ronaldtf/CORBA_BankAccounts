# CORBA_BankAccounts
This is an example of how to implement Corba interfaces in Java an C++.

The project consists of a Client and a Server which are handling bank accounts:
+ Server: A server represents a bank entity. In this case, the server creates a list of accounts and listen for clients who create and update their accounts
+ Client: A client represents the people who attend to the bank in order to create an account and perform operations.

Unlike other CORBA projects seen in Internet, the purpose of this project is to test the usage and manipulation of CORBA objects from both sides, i.e. the Client and the Server. This way, the Server creates and publishes the list of accounts but it is the Client who requests new account creation and manipulation. In fact, both entities publish their instances in the CORBA naming service so that anyone may have access to them.

The project can be improved in different ways:
+ Identifiers might be automatically generated, without needing to specify them. This has not been implemented as it is not relevant for the project.
+ Multiple account lists may be needed in a same bank entity (to distinguish between, for instance, VIP customers an normal customers). This has not been implemented in the project because the purpose was to create a simple and basic project that works in a basic scenario.
+ ... 

# Building the project
- Libraries needed:
+ omniORB: libraries for Corba in C++, e.g. http://omniorb.sourceforge.net/ (downloadable at: https://sourceforge.net/projects/omniorb/files/omniORB/omniORB-4.2.1/omniORB-4.2.1-2.tar.bz2)
+ jacORB: libraries for Corba in Java, e.g. http://www.jacorb.org/ (downloadable at http://www.jacorb.org/releases/3.8/jacorb-3.8-binary.zip)
Simply run the Makefile. It compiles the idl library for both java and C++, as well as the source code for both languages.

# Run the application
## Java
To run the java version, run the following commands (in the java folder):

1. *tnameserv -ORBInitialPort 9999*
2. Server: *make run_java_server*
3. Client: *make run_java_client*

## C++

1. *tnameserv -ORBInitialPort 9999*
2. Server: *make run_cxx_server*
3. Client: *make run_cxx_client*

# Generate the javadoc/doxygen

To generate the documentation, run:

*make doc*
