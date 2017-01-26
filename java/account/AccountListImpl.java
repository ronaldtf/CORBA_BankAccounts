/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package account;

import corbaAccount.Account;
import corbaAccount.AccountList;
import corbaAccount.AccountListPOA;

import connection.Connection;

/**
 * This class is an implementation of the AccountList CORBA interface
 */
public class AccountListImpl extends AccountListPOA {

	/**
	 * CORBA connection, used to publish the current instance in the naming service (if proceed)
	 */
	private static Connection _connection;
	/**
	 * CORBA AccountList reference
	 */
	private Account[] _accountList = null;
	/**
	 * CORBA object with the list of accounts
	 */
	private AccountList _al = null;
	
	/**
	 * Class constructor
	 * @param a		List of accounts
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountListImpl(Account[] a) throws Exception {
		super();
		accountsList(a);
		
		// Activate the CORBA object
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}

	/**
	 * Class constructor
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountListImpl() throws Exception {
		super();
		// Activate the CORBA object
		_connection = Connection.getInstance();
		_connection.activateServant(this);
		_accountList = new Account[0];
	}

	/**
	 * Class constructor
	 * @param al	CORBA object with the list of accounts
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountListImpl(AccountList al) throws Exception {
		super();
		_al = al;
		accountsList(al.accountsList());
		
		// Initialize the connection for future references
		_connection = Connection.getInstance();
	}
	
	/**
	 * Get the list of accounts
	 * @return Array of CORBA Accounts
	 */
	@Override
	public Account[] accountsList() {
		return _accountList;
	}

	/**
	 * Set the list of accounts
	 * @param newAccountsList List of accounts. IMPORTANT: Previous accounts will not
	 * be taken into account (removed)
	 */
	@Override
	public void accountsList(Account[] newAccountsList) {
		_accountList = newAccountsList;
	}

	/**
	 * Add and account
	 * @param ac	Account to be added
	 */
	@Override
	public void addAccount(Account ac) {
		Account accounts[] = new Account[_accountList.length + 1];
		int pos = 0;
		for (Account a : _accountList) {
			accounts[pos++] = a;
		}
		accounts[pos] = ac;
		_accountList = accounts;
		// We need to update the CORBA reference (otherwise, the account list will not be
		// updated).
		if (_al != null)
			_al.accountsList(_accountList);
	}

}