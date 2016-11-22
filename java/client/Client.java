package client;

import org.omg.CORBA.Object;

import account.AccountListDelegate;
import connection.Connection;
import connection.ConnectionClientInterface;
import corbaAccount.AccountList;
import corbaAccount.AccountListHelper;

public class Client {
	public static void main(String args[]) {
		try {
			ConnectionClientInterface connection = new Connection();
			Object obj = connection.getClientObject("myContext", "accounts", "Object");
			AccountList list = AccountListHelper.narrow(obj);
			AccountListDelegate ald = new AccountListDelegate(list);
			System.out.println(ald.getAccounts().size());
		} catch (Exception e) {
			System.err.println("An error has occurred: " + e.getLocalizedMessage());
		}
	}
}
