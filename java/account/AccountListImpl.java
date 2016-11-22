package account;

import java.util.Vector;

import corbaAccount.Account;
import corbaAccount.AccountListPOA;

public class AccountListImpl extends AccountListPOA {

	private Vector<AccountImpl> _accounts;
	
	public AccountListImpl() {
		_accounts = new Vector<AccountImpl>();
	}
	
	@Override
	public Account[] accountsList() {
		Account[] ac = new Account[_accounts.size()];
		int pos = 0;
		for (AccountImpl account : _accounts) {
			ac[pos] = account._this();
		}
		return ac;
	}

	@Override
	public void accountsList(Account[] newAccountsList) {
		for (Account ac : newAccountsList) {
			_accounts.addElement(new AccountImpl(ac));
		}
	}

	@Override
	public void addAccount(Account ac) {
		_accounts.addElement(new AccountImpl(ac));
	}
}