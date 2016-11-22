package server;

import org.omg.CORBA.Object;

import account.AccountListDelegate;
import connection.Connection;
import connection.ConnectionServerInterface;

public class Server {

	public static void main(String[] args) {
		try {
			ConnectionServerInterface connection = new Connection();
			connection.referenceObject();
			
			AccountListDelegate ald = new AccountListDelegate();
			Object ref = connection.activateServant(ald.getCorbaInstance());
			
			try {
				connection.bindObjectToName(ref, "myContext", "accounts", "Object");
				connection.runServer();
			} catch (Exception e) {
				System.err.println("Error when binding object: " + e.getLocalizedMessage());
			}			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
}
