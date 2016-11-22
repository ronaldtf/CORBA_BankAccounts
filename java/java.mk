build:
	javac -cp corbaAccount:. ./account/*.java
	javac -cp corbaAccount:./account:.:./server ./server/Server.java
	javac -cp corbaAccount:./account:.:./client ./client/Client.java

