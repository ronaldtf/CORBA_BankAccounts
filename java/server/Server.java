package server;

import org.omg.CORBA.Object;

import account.AccountDelegate;
import account.AccountListDelegate;
import connection.Connection;
import connection.ConnectionServerInterface;

public class Server {

	public static void main(String[] args) {
		try {
			ConnectionServerInterface connection = new Connection();
			connection.referenceObject();
			
			AccountListDelegate ald = new AccountListDelegate();
			Object accountListRef = connection.activateServant(ald.getCorbaInstance());
			AccountDelegate account = new AccountDelegate("","");
			Object accountRef = connection.activateServant(account.getCorbaInstance());
			
			
			try {
				connection.bindObjectToName(accountListRef, "myContext", "accountList", "AccountList");
				connection.bindObjectToName(accountRef, "myContext", "account", "Account");
				connection.runServer();
			} catch (Exception e) {
				System.err.println("Error when binding object: " + e.getLocalizedMessage());
			}			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
}
