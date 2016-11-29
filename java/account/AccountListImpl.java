package account;

import connection.Connection;
import corbaAccount.Account;
import corbaAccount.AccountList;
import corbaAccount.AccountListPOA;

// Skip vector. Use the list from the superclass instead.

public class AccountListImpl extends AccountListPOA {

	private static Connection _connection;
	private Account[] _accountList = null;
	private AccountList _al = null;
	
	public AccountListImpl(Account[] a) throws Exception {
		super();
		accountsList(a);
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}

	public AccountListImpl() throws Exception {
		super();
		_connection = Connection.getInstance();
		_connection.activateServant(this);
		_accountList = new Account[0];
	}

	public AccountListImpl(AccountList al) throws Exception {
		super();
		_al = al;
		accountsList(al.accountsList());
		_connection = Connection.getInstance();
	}
	
	@Override
	public Account[] accountsList() {
		return _accountList;
	}

	@Override
	public void accountsList(Account[] newAccountsList) {
		_accountList = newAccountsList;
	}

	@Override
	public void addAccount(Account ac) {
		Account accounts[] = new Account[_accountList.length + 1];
		int pos = 0;
		for (Account a : _accountList) {
			accounts[pos++] = a;
		}
		accounts[pos] = ac;
		_accountList = accounts;
		if (_al != null)
			_al.accountsList(_accountList);
	}

}