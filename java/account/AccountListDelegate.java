package account;

import java.util.Vector;

import corbaAccount.Account;
import corbaAccount.AccountList;

public class AccountListDelegate {

	private AccountListImpl _instance;

	public AccountListDelegate() {
		_instance = new AccountListImpl();
	}

	public AccountListDelegate(AccountList al) {
		_instance = new AccountListImpl(al);
	}
	
	public void addAccount(AccountDelegate account) {
		_instance.addAccount(account.getCorbaInstance()._this());
	}
	
	public Vector<AccountDelegate> getAccounts() {
		Vector<AccountDelegate> acDelegate = new Vector<AccountDelegate>(_instance.accountsList().length);
		for (Account a : _instance.accountsList()) {
			acDelegate.add(new AccountDelegate(a.name(), a.surname(), a.balance()));
		}
		return acDelegate;
	}
	
	public AccountListImpl getCorbaInstance() {
		return _instance;
	}
}
