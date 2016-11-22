package account;

import java.util.Vector;

import corbaAccount.Account;
import corbaAccount.AccountPOA;
import corbaAccount.Operation;
import corbaAccount.date;

class AccountImpl extends AccountPOA {

	private int _accountId;
	private String _details;
	DateImpl _dateAccountCreated;
	private float _balance;
	private Vector<OperationImpl> _accountOperations;
	
	public AccountImpl(Account a) {
		_accountId = a.accountId();
		_details = a.details();
		_dateAccountCreated = new DateImpl(a.dateAccountCreated());
		_balance = a.balance();
		for (Operation op : a.accountOperations()) {
			_accountOperations.add(new OperationImpl(op));
		}
	}
	
	public AccountImpl(String name, String surname, float balance) {
			_details = name + " " + surname;
			_balance = balance;
			_accountOperations = new Vector<OperationImpl>();
	}
	
	public AccountImpl(String name, String surname) {
		this(name, surname, 0.0f);
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
		throw new RuntimeException("Method not implemented");
	}

	@Override
	public void name(String newName) {
		throw new RuntimeException("Method not implemented");		
	}

	@Override
	public String surname() {
		throw new RuntimeException("Method not implemented");
	}

	@Override
	public void surname(String newSurname) {
		throw new RuntimeException("Method not implemented");		
	}

	@Override
	public date dateAccountCreated() {
		return _dateAccountCreated._this();
	}

	@Override
	public void dateAccountCreated(date newDateAccountCreated) {
		_dateAccountCreated = new DateImpl(newDateAccountCreated.year(), newDateAccountCreated.month(), newDateAccountCreated.day());
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
		Operation op[] = new Operation[_accountOperations.size()];
		int pos = 0;
		for (OperationImpl opImpl : _accountOperations) {
			op[pos].amount(opImpl.amount());
			op[pos++].type(opImpl.type());
		}
		return op;
	}

	@Override
	public void accountOperations(Operation[] newAccountOperations) {
		Operation[] operations = new Operation[newAccountOperations.length];
		for (Operation op : operations) {
			_accountOperations.addElement(new OperationImpl(op.type(), op.amount()));
		}
	}

	@Override
	public String details() {
		return _details;
	}

	@Override
	public void addOperation(Operation op) {
		_accountOperations.addElement(new OperationImpl(op.type(), op.amount()));
	}

	@Override
	public String _toString() {
		return "accountId: " + String.format("%2s",Integer.valueOf(_accountId)).replaceAll(" " , "0") + 
				", owner: " + _details + ", balance: " + _balance + ", operations: " + _accountOperations.size();
	}
}

