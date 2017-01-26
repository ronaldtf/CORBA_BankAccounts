/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package account;

import java.nio.channels.AlreadyBoundException;
import java.util.Arrays;
import java.util.Vector;

import corbaAccount.Account;
import corbaAccount.AccountList;

import connection.Connection;

/**
 * This class implements the delegate for the list of accounts in a bank entity.
 * @see AccountListImpl
 */
public class AccountListDelegate {

	/**
	 * This is an instance of an AccountListImpl, in which the class delegates
	 */
	private AccountListImpl _instance;

	/**
	 * Create a list of accounts
	 * @param publish	Indicates whether the account needs to be added to the corba naming service
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountListDelegate(boolean publish) throws Exception {
		_instance = new AccountListImpl();
		if (publish) {
			try {
				// Publish the object in the CORBA naming service.
				// IMPORTANT: 	As the object name is fix, there will be only one account list (only bank entity would exist).
				//				In case of multiple AccountsLists (multiple entities), we would need to add something that
				//				differentiates one object to the others (for instance, add an accountListId or bankAccountName
				//				to the CORBA object name when publishing it in the naming service).
				Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "AccountList", "AccountList");
			} catch (AlreadyBoundException abe) {
				System.err.println("Trying to bind an AccountList which is already bound");
				System.err.println("Only one AccountList is possible in the name service");
			}
		}
	}
	
	/**
	 * Create an account list and publish it in the CORBA naming service
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountListDelegate() throws Exception {
		this(true);
	}
	
	/**
	 * Class constructor
	 * @param al	List of accounts to be included here
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountListDelegate(AccountList al) throws Exception {
		// In this case, we can assume that the AccountList is already in the naming service.
		// Otherwise, we would have to create a constructor with the publish parameter to
		// indicate whether the AccountList needs to be published or not
		_instance = new AccountListImpl(al);
	}
	
	/**
	 * Add an account to the list
	 * @param account	Account to be added to the list
	 */
	public void addAccount(AccountDelegate account) {
		_instance.addAccount(account.getCorbaInstance());
	}
	
	/**
	 * Get the accounts from the list
	 * @return List of accounts
	 */
	public Vector<Account> getAccounts() {
		return new Vector<Account>(Arrays.asList(_instance.accountsList()));
	}
	
	/**
	 * Get the CORBA instance for the account list
	 * @return CORBA instance
	 */
	public AccountList getCorbaInstance() {
		return _instance._this();
	}
	
    /**
     * Get the ids of the accounts in the list
     * @return Vector of account ids
     */
	public Vector<Integer> getAccountIds() {
		Vector<Integer> v = new Vector<Integer>();
		for (Account a : _instance.accountsList()) {
			v.addElement(Integer.valueOf(a.accountId()));
		}
		return v;
	}
}
