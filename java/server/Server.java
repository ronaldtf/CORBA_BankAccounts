package server;

import org.omg.CORBA.Object;

import account.AccountListDelegate;
import account.Connection;

public class Server {

	public static void main(String[] args) {
		try {
			Connection connection = Connection.getInstance();

			AccountListDelegate ald = new AccountListDelegate();
			Object ref = connection.activate(ald.getCorbaInstance());
			
			try {
				connection.bindObjectToName(ref, "myContext", "accounts", "Object");
				connection.run();
			} catch (Exception e) {
				System.err.println("Error when binding object: " + e.getLocalizedMessage());
			}

			connection.run();
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
}
