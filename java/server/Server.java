package server;

import account.AccountListDelegate;
import connection.Connection;

public class Server {

	public static void main(String[] args) {
		try {
			AccountListDelegate ald = new AccountListDelegate();
			try {
				Connection connection = Connection.getInstance();
				connection.bindObjectToName(ald.getCorbaInstance(), "myContext", "AccountList0", "AccountList");
				connection.runServer();
			} catch (Exception e) {
				System.err.println("Error when starting server: " + e.getLocalizedMessage());
			}			
		} catch (Exception e) {
			System.out.println("Error when binding object: " + e.getLocalizedMessage());
		}
		
	}
}
