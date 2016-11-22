package account;

import java.util.Vector;

import corbaAccount.Account;

public class AccountListDelegate {

	private AccountListImpl _accounts;

	public AccountListDelegate() {
		_accounts = new AccountListImpl();
	}
	
	public void addAccount(AccountDelegate account) {
		_accounts.addAccount(account.getCorbaInstance()._this());
	}
	
	public Vector<AccountDelegate> getAccounts() {
		Vector<AccountDelegate> acDelegate = new Vector<AccountDelegate>(_accounts.accountsList().length);
		for (Account a : _accounts.accountsList()) {
			acDelegate.add(new AccountDelegate(a.name(), a.surname(), a.balance()));
		}
		return acDelegate;
	}
	
	public AccountListImpl getCorbaInstance() {
		return _accounts;
	}
}
