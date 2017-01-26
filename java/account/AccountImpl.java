/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package account;

import corbaAccount.Account;
import corbaAccount.AccountPOA;
import corbaAccount.Operation;
import corbaAccount.date;
import corbaAccount.operationType;

import connection.Connection;

/**
 * This class is an implementation of the Account CORBA interface
 */
class AccountImpl extends AccountPOA {

	/**
	 * Account identifier
	 */
	private int _accountId;
	/**
	 * Account owner name
	 */
	private String _name;
	/**
	 * Account owner surname
	 */
	private String _surname;
	/**
	 * Account creation date
	 */
	date _dateAccountCreated;
	/**
	 * Updated account balance
	 */
	private float _balance;
	/**
	 * Operations performed in the account
	 */
	private Operation[] _accountOperations = null;
	/**
	 * CORBA connection, used to publish the current instance in the naming service (if proceed)
	 */
	private Connection _connection;
	
	/** 
	 * Class constructor
	 * @param a		Account to be copied
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountImpl(Account a) throws Exception {
		super();
		accountId(a.accountId());
		name(a.name());
		surname(a.surname());
		dateAccountCreated(a.dateAccountCreated());
		balance(a.balance());
		accountOperations(a.accountOperations());
		
		// Activate the CORBA object
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	/** 
	 * Class constructor
	 * @param name 				Account owner name
	 * @param surname			Account owner surname
	 * @param dateCreated		Account creation date
	 * @param balance			Initial account balance
	 * @param accOperations		Operations performed in the account
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountImpl(String name, String surname, date dateCreated, float balance, Operation[] accOperations) throws Exception {
		name(name);
		surname(surname);
		dateAccountCreated(dateCreated);
		balance(balance);
		accountOperations(accOperations);
		
		// Activate the CORBA object
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	/** 
	 * Class constructor
	 * @param name 				Account owner name
	 * @param surname			Account owner surname
	 * @param balance			Initial account balance
	 * @param accountId			Account identifier
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountImpl(String name, String surname, float balance, int accountId) throws Exception {
		super();
		accountId(accountId);
		name(name);
		surname(surname);
		balance(balance);
		accountOperations(new Operation[0]);
		
		// Activate the CORBA object
		_connection = Connection.getInstance();
		_connection.activateServant(this);
		
		DateDelegate dd = new DateDelegate();
		_dateAccountCreated = dd.getCorbaInstance();
	}
		
	/** 
	 * Class constructor
	 * @param name 				Account owner name
	 * @param surname			Account owner surname
	 * @param accountId			Account identifier
	 * @throws Exception Throws an exception in case of any problem
	 */
	public AccountImpl(String name, String surname, int accountId) throws Exception {
		this(name, surname, 0.0f, accountId);
	}
	
	/**
	 * Get the accountId
	 * @return accountId
	 */
	@Override
	public int accountId() {
		return _accountId;
	}

	/**
	 * Set the accountId
	 * @param	newAccountId	New accountId
	 */
	@Override
	public void accountId(int newAccountId) {
		_accountId = newAccountId;
	}

	/**
	 * Get the account owner name
	 * @return Owner name
	 */
	@Override
	public String name() {
		return _name;
	}

	/**
	 * Set the account owner name
	 * @param	newName	New owner name
	 */
	@Override
	public void name(String newName) {
		_name = newName;	
	}

	/**
	 * Get the account owner surnamed
	 * @return Owner surname
	 */
	@Override
	public String surname() {
		return _surname;
	}

	/**
	 * Set the account owner surname
	 * @param	newSurname	New owner surname
	 */
	@Override
	public void surname(String newSurname) {
		_surname = newSurname;	
	}

	/**
	 * Get the account creation date
	 * @return Account creation date
	 */
	@Override
	public date dateAccountCreated() {
		return _dateAccountCreated;
	}

	/**
	 * Set the account creation date
	 * @param	newDateAccountCreated	Updated creation date
	 */
	@Override
	public void dateAccountCreated(date newDateAccountCreated) {
		_dateAccountCreated = newDateAccountCreated;
	}

	/**
	 * Get the account balance
	 * @return balance
	 */
	@Override
	public float balance() {
		return _balance;
	}

	/**
	 * Set the account balance
	 * @param	newBalance	Account balance
	 */
	@Override
	public void balance(float newBalance) {
		_balance = newBalance;
	}

	/**
	 * Get the list of account operations in the account
	 * @return Array of accountOperations
	 */
	@Override
	public Operation[] accountOperations() {
		return _accountOperations;
	}

	/**
	 * Set the list of operations performed in the account.
	 * NNOTE: This overrides the existing accounts in case they exist!
	 * @param	newAccountOperations	List of account operations
	 */
	@Override
	public void accountOperations(Operation[] newAccountOperations) {
		_accountOperations = newAccountOperations;
		// Update the account balance
		for (Operation op : newAccountOperations) {
			if (op.type() == operationType.WITHDRAW)
				_balance -= op.amount();
			else
				_balance += op.amount();
		}
	}

	/**
	 * Get the account owner full name
	 * @return Concatenation os name and surname
	 */
	@Override
	public String details() {
		return _name + " " + _surname;
	}

	/**
	 * Add an operation and update the account balance
	 * @param	op	Operation to be added
	 */
	@Override
	public void addOperation(Operation op) {
		Operation[] tmp = new Operation[_accountOperations.length + 1];
		int pos = 0;
		// Update the operations performed in the account
		for (Operation o : _accountOperations) {
			tmp[pos++] = o;
		}
		tmp[pos] = op;
		_accountOperations = tmp;
		
		// Update balance
		if (op.type() == operationType.WITHDRAW)
			_balance -= op.amount();
		else
			_balance += op.amount();
	}

	/**
	 * Get a summary of the account
	 * @return String with the details of the account
	 */
	@Override
	public String _toString() {
		return "accountId: " + String.format("%2s",Integer.valueOf(_accountId)).replaceAll(" " , "0") + 
				", owner: " + _name + " " + _surname + ", balance: " + _balance + ", operations: " + _accountOperations.length;
	}
	
	/**
	 * Get the CORBA instance associated to this account
	 * @return Account CORBA instance
	 */
	public Account getCorbaInstance() {
		return _this();
	}
	
}

