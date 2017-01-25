.PHONY:	client server
build:
	javac -cp ../idl:. ./account/*.java
	javac -cp ../idl:. ./utils/Utils.java
	javac -cp ../idl:./account:./utils:.:./server ./server/Server.java
	javac -cp ../idl:./account:./utils:.:./client ./client/Client.java
clean:
	rm -rf utils/*.class connection/*.class account/*.class server/*.class client/*.class
client:
	java -cp ../idl:. client.Client
server:
	java -cp ../idl:. server.Server
javadoc:
	mkdir -p ../doc/javadoc
	rm -rf ../doc/javadoc/*
	javadoc -author -version -use -private -linksource -d ../doc/javadoc -cp ../idl:./account:./utils:.:./client:./server client server utils connection account
