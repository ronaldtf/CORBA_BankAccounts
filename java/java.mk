build:
	javac -cp corbaAccount:. ./account/*.java
	javac ./utils/Utils.java
	javac -cp corbaAccount:./account:./utils:.:./server ./server/Server.java
	javac -cp corbaAccount:./account:./utils:.:./client ./client/Client.java

