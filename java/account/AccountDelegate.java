package account;

import java.util.Vector;

import corbaAccount.Operation;
import corbaAccount.date;

public class AccountDelegate {

	private AccountImpl instance;
	
	public AccountDelegate(String name, String surname) {
		instance = new AccountImpl(name, surname);
	}
	
	public AccountDelegate(String name, String surname, float balance) {
		instance = new AccountImpl(name, surname, balance);
	}
	
	public int getAccountId() {
		return instance.accountId();
	}
	
	public String getName() {
		return instance.details();
	}
	
	public float getBalance() {
		return instance.balance();
	}
	
	public String toString() {
		return instance.toString();
	}
	
	public DateDelegate getDate() {
		date d = instance.dateAccountCreated();
		return new DateDelegate(d.year(), d.month(), d.day());
	}
	
	public Vector<OperationDelegate> getOperations() {
		Operation[] operations = instance.accountOperations();
		Vector<OperationDelegate> v = new Vector<OperationDelegate>();
		for (Operation op : operations) {
			v.addElement(new OperationDelegate(op.amount(), Utils.convertType(op.type())));
		}
		return v;
	}
	
	public void addOperation(OperationDelegate op) {
		instance.addOperation(new OperationImpl(Utils.convertType(op.getType()), op.getAmount())._this());
	}
	
	public AccountImpl getCorbaInstance() {
		return instance;
	}
	
}
