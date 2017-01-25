package account;

import corbaAccount.Account;
import corbaAccount.AccountPOA;
import corbaAccount.Operation;
import corbaAccount.date;
import corbaAccount.operationType;

import connection.Connection;

class AccountImpl extends AccountPOA {

	private int _accountId;
	private String _name;
	private String _surname;
	date _dateAccountCreated;
	private float _balance;
	private Operation[] _accountOperations = null;
	private Connection _connection;
	
	public AccountImpl(Account a) throws Exception {
		super();
		accountId(a.accountId());
		name(a.name());
		surname(a.surname());
		dateAccountCreated(a.dateAccountCreated());
		balance(a.balance());
		accountOperations(a.accountOperations());
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	public AccountImpl(String name, String surname, date dateCreated, float balance, Operation[] accOperations) throws Exception {
		name(name);
		surname(surname);
		dateAccountCreated(dateCreated);
		balance(balance);
		accountOperations(accOperations);
		
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	public AccountImpl(String name, String surname, float balance, int accountId) throws Exception {
		super();
		accountId(accountId);
		name(name);
		surname(surname);
		balance(balance);
		accountOperations(new Operation[0]);
		_connection = Connection.getInstance();
		_connection.activateServant(this);
		
		DateDelegate dd = new DateDelegate();
		_dateAccountCreated = dd.getCorbaInstance();
	}
		
	public AccountImpl(String name, String surname, int accountId) throws Exception {
		this(name, surname, 0.0f, accountId);
	}
	
	@Override
	public int accountId() {
		return _accountId;
	}

	@Override
	public void accountId(int newAccountId) {
		_accountId = newAccountId;
	}

	@Override
	public String name() {
		return _name;
	}

	@Override
	public void name(String newName) {
		_name = newName;	
	}

	@Override
	public String surname() {
		return _surname;
	}

	@Override
	public void surname(String newSurname) {
		_surname = newSurname;	
	}

	@Override
	public date dateAccountCreated() {
		return _dateAccountCreated;
	}

	@Override
	public void dateAccountCreated(date newDateAccountCreated) {
		_dateAccountCreated = newDateAccountCreated;
	}

	@Override
	public float balance() {
		return _balance;
	}

	@Override
	public void balance(float newBalance) {
		_balance = newBalance;
	}

	@Override
	public Operation[] accountOperations() {
		return _accountOperations;
	}

	@Override
	public void accountOperations(Operation[] newAccountOperations) {
		_accountOperations = newAccountOperations;
		for (Operation op : newAccountOperations) {
			if (op.type() == operationType.WITHDRAW)
				_balance -= op.amount();
			else
				_balance += op.amount();
		}
	}

	@Override
	public String details() {
		return _name + " " + _surname;
	}

	@Override
	public void addOperation(Operation op) {
		Operation[] tmp = new Operation[_accountOperations.length + 1];
		int pos = 0;
		for (Operation o : _accountOperations) {
			tmp[pos++] = o;
		}
		tmp[pos] = op;
		_accountOperations = tmp;
		
		if (op.type() == operationType.WITHDRAW)
			_balance -= op.amount();
		else
			_balance += op.amount();
	}

	@Override
	public String _toString() {
		return "accountId: " + String.format("%2s",Integer.valueOf(_accountId)).replaceAll(" " , "0") + 
				", owner: " + _name + " " + _surname + ", balance: " + _balance + ", operations: " + _accountOperations.length;
	}
	
	public Account getCorbaInstance() {
		return _this();
	}
	
}

