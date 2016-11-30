package account;

import java.util.Arrays;
import java.util.Vector;

import connection.Connection;
import corbaAccount.Account;
import corbaAccount.Operation;
import corbaAccount.date;

public class AccountDelegate {

	private AccountImpl _instance;
	
	public AccountDelegate(String name, String surname, int accountId) throws Exception {
		this(name, surname, accountId, true);
	}

	public AccountDelegate(String name, String surname, int accountId, boolean publish) throws Exception {
		_instance = new AccountImpl(name, surname, accountId);
		if (publish)
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Account"+_instance.accountId(), "Account");
	}
	
	public AccountDelegate(String name, String surname, float balance, int accountId) throws Exception {
		_instance = new AccountImpl(name, surname, balance, accountId);
	}
	
	public int getAccountId() {
		return _instance.accountId();
	}
	
	public String getName() {
		return _instance.name();
	}
	
	public float getBalance() {
		return _instance.balance();
	}
	
	public String toString() {
		return _instance.toString();
	}
	
	public DateDelegate getDate() throws Exception {
		date d = _instance.dateAccountCreated();
		return new DateDelegate(d.year(), d.month(), d.day());
	}
	
	public Vector<Operation> getOperations() {
		return new Vector<Operation>(Arrays.asList(_instance.accountOperations()));
	}
	
	public void addOperation(OperationDelegate op) {
		_instance.addOperation(op.getCorbaInstance());
	}
	
	public Account getCorbaInstance() {
		return _instance.getCorbaInstance();
	}
		
}
