/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @mail ronaldtfernandez@gmail.com
 * @version 1.0
 */
package account;

import java.util.Vector;

import account.OperationDelegate;
import utils.Utils;
import connection.Connection;
import corbaAccount.Account;
import corbaAccount.Operation;
import corbaAccount.date;

/**
 * This class implements the delegate for the user bank account
 */
public class AccountDelegate {

	private AccountImpl _instance;
	
	/**
	 * Constructor of the class
	 * @param name		Account owner name
	 * @param surname 	Account owner surname
	 * @param accountId	Account identifier
	 */
	public AccountDelegate(String name, String surname, int accountId) throws Exception {
		this(name, surname, accountId, true);
	}

	/**
	 * Constructor of the class
	 * @param name		Account owner name
	 * @param surname 	Account owner surname
	 * @param accountId	Account identifier
	 * @param publish	Indicates whether the account needs to be added to the corba naming service
	 */
	public AccountDelegate(String name, String surname, int accountId, boolean publish) throws Exception {
		_instance = new AccountImpl(name, surname, accountId);
		if (publish)
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Account"+_instance.accountId(), "Account");
	}
	
	/**
	 * Constructor of the class
	 * @param name		Account owner name
	 * @param surname 	Account owner surname
	 * @param balance	Account initial balance
	 * @param accountId	Account identifier
	 */
	public AccountDelegate(String name, String surname, float balance, int accountId) throws Exception {
		_instance = new AccountImpl(name, surname, balance, accountId);
	}
	
	/**
	 * Obtain the account identifier
	 * @return accountId
	 */
	public int getAccountId() {
		return _instance.accountId();
	}
	
	/**
	 * Obtain the account owner name
	 * @return	Owner name
	 */
	public String getName() {
		return _instance.name();
	}
	
	/**
	 * Obtain the current acccount balance
	 * @return Up-to-date account balance
	 */
	public float getBalance() {
		return _instance.balance();
	}
	
	/**
	 * Show the account details
	 * @return String with a summary of the account
	 */
	public String toString() {
		return _instance.toString();
	}
	
	/**
	 * Get the account creation date
	 * @return Account creation date
	 */
	public DateDelegate getDate() throws Exception {
		date d = _instance.dateAccountCreated();
		return new DateDelegate(d.year(), d.month(), d.day());
	}
	
	/**
	 * Get the operations performed in the account
	 * @return List of operations
	 */
	public Vector<OperationDelegate> getOperations() throws Exception {
		Vector<OperationDelegate> v = new Vector<OperationDelegate>();
		for(Operation op : _instance.accountOperations()) {
			v.addElement(new OperationDelegate(op.amount(), Utils.convertType(op.type()), op.operationId(), false));
		}
		return v;
	}
	
	/**
	 * Add an operation to the current account
	 * @param op	Operation to be added to the current account
	 */
	public void addOperation(OperationDelegate op) {
		_instance.addOperation(op.getCorbaInstance());
	}
	
	/**
	 * Gets the CORBA instance for the account
	 * @return CORBA instance
	 */
	public Account getCorbaInstance() {
		return _instance.getCorbaInstance();
	}
		
}
