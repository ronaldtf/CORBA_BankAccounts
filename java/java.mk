build:
	javac -cp ../idl:. ./account/*.java
	javac -cp ../idl:. ./utils/Utils.java
	javac -cp ../idl:./account:./utils:.:./server ./server/Server.java
	javac -cp ../idl:./account:./utils:.:./client ./client/Client.java
clean:
	rm -rf utils/*.class connection/*.class account/*.class server/*.class client/*.class
