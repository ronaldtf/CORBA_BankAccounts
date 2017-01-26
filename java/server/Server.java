/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package server;

import account.AccountListDelegate;
import connection.Connection;

public class Server {

	public static void main(String[] args) {
		Connection connection = null;
		try {
			// Create an account list (it implicitly publishes in the naming service)
			@SuppressWarnings("unused")
			AccountListDelegate ald = new AccountListDelegate();
			try {
				// Start the server
				connection = Connection.getInstance();
				connection.runServer();
			} catch (Exception e) {
				System.err.println("Error when starting server: " + e.getLocalizedMessage());
			}			
		} catch (Exception e) {
			System.out.println("Error when binding object: " + e.getLocalizedMessage());
		}
		
		// In case an exception has occurred, ensure that the connection is closed
		if (connection != null)
			connection.close();
		
	}
}
