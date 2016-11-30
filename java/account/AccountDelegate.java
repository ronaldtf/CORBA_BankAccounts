package account;

import java.util.Arrays;
import java.util.Vector;

import corbaAccount.Account;
import corbaAccount.Operation;
import corbaAccount.date;

public class AccountDelegate {

	private AccountImpl _instance;
	
	public AccountDelegate(String name, String surname, int accountId) throws Exception {
		_instance = new AccountImpl(name, surname, accountId);
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
	
	public void addOperation(Operation op) {
		_instance.addOperation(op);
	}
	
	public Account getCorbaInstance() {
		return _instance.getCorbaInstance();
	}
		
}
