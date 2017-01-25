package account;

import java.nio.channels.AlreadyBoundException;
import java.util.Arrays;
import java.util.Vector;

import corbaAccount.Account;
import corbaAccount.AccountList;

import connection.Connection;

public class AccountListDelegate {

	private AccountListImpl _instance;

	public AccountListDelegate(boolean publish) throws Exception {
		_instance = new AccountListImpl();
		if (publish) {
			try {
				Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "AccountList", "AccountList");
			} catch (AlreadyBoundException abe) {
				System.err.println("Trying to bind an AccountList which is already bound");
				System.err.println("Only one AccountList is possible in the name service");
			}
		}
	}
	
	public AccountListDelegate() throws Exception {
		this(true);
	}
	
	public AccountListDelegate(AccountList al) throws Exception {
		// In this case, we can assume that the AccountList is already in the naming service.
		// Otherwise, we would have to create a constructor with the publish parameter to
		// indicate whether the AccountList needs to be published or not
		_instance = new AccountListImpl(al);
	}
	
	public void addAccount(AccountDelegate account) {
		_instance.addAccount(account.getCorbaInstance());
	}
	
	public Vector<Account> getAccounts() {
		return new Vector<Account>(Arrays.asList(_instance.accountsList()));
	}
	
	public AccountList getCorbaInstance() {
		return _instance._this();
	}
	
	public Vector<Integer> getAccountIds() {
		Vector<Integer> v = new Vector<Integer>();
		for (Account a : _instance.accountsList()) {
			v.addElement(Integer.valueOf(a.accountId()));
		}
		return v;
	}
}
