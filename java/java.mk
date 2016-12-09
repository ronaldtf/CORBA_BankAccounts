build:
	javac -cp corbaAccount:. ./account/*.java
	javac ./utils/Utils.java
	javac -cp corbaAccount:./account:./utils:.:./server ./server/Server.java
	javac -cp corbaAccount:./account:./utils:.:./client ./client/Client.java
clean:
	rm -rf utils/*.class connection/*.class account/*.class server/*.class client/*.class
