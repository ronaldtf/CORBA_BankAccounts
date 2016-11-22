package client;

import org.omg.CORBA.Object;

import account.AccountDelegate;
import account.AccountListDelegate;
import connection.Connection;
import connection.ConnectionClientInterface;
import corbaAccount.AccountList;
import corbaAccount.AccountListHelper;

public class Client {
	public static void main(String args[]) {
		try {
			ConnectionClientInterface connection = new Connection();
			Object objAccountList = connection.getClientObject("myContext", "accountList", "AccountList");
			AccountList list = AccountListHelper.narrow(objAccountList);
			AccountListDelegate ald = new AccountListDelegate(list);
			AccountDelegate ad = new AccountDelegate("MainName", "Main Surname");
			ald.addAccount(ad);
			System.out.println(ald.getAccounts().size());
		} catch (Exception e) {
			System.err.println("An error has occurred: " + e.getLocalizedMessage());
		}
	}
}
