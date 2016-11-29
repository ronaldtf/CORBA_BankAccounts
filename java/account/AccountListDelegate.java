package account;

import java.util.Arrays;
import java.util.Vector;

import corbaAccount.Account;
import corbaAccount.AccountList;

public class AccountListDelegate {

	private AccountListImpl _instance;

	public AccountListDelegate() throws Exception {
		_instance = new AccountListImpl();
	}
	
	public AccountListDelegate(AccountList al) throws Exception {
		_instance = new AccountListImpl(al);
	}
	
	public void addAccount(Account account) {
		_instance.addAccount(account);
	}
	
	public Vector<Account> getAccounts() {
		return new Vector<Account>(Arrays.asList(_instance.accountsList()));
	}
	
	public AccountList getCorbaInstance() {
		return _instance._this();
	}
}
