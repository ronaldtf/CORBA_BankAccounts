package account;

import java.util.Vector;

import corbaAccount.AccountPOA;
import corbaAccount.Operation;
import corbaAccount.OperationOperations;
import corbaAccount.OperationPOA;
import corbaAccount._dateStub;
import corbaAccount.date;
import corbaAccount.dateHelper;
import corbaAccount.dateHolder;
import corbaAccount.dateOperations;
import corbaAccount.datePOA;
import corbaAccount.operationType;

class dateImpl extends datePOA {

	private int _day;
	private int _month;
	private int _year;
	
	public dateImpl(int month, int year, int day) {
		_year = year;
		_month = month;
		_day = day;
	}
	
	public dateImpl() {
		this(0,0,0);
	}
	
	@Override
	public int day() {
		return _day;
	}

	@Override
	public void day(int newDay) {
		_day = newDay;
	}

	@Override
	public int month() {
		return _month;
	}

	@Override
	public void month(int newMonth) {
		_month = newMonth;
	}

	@Override
	public int year() {
		return _year;
	}

	@Override
	public void year(int newYear) {
		_year = newYear;
	}

	@Override
	public String _toString() {
		return String.valueOf(_year) + "/" + 
				String.format("%2s",Integer.valueOf(_month)).replaceAll(" " , "0") + 
				String.format("%2s",Integer.valueOf(_day)).replaceAll(" " , "0");
	}
	
}

class OperationImpl extends OperationPOA {

	private operationType _type;
	private float _amount;
	
	public OperationImpl(operationType type, float amount) {
		_type = type;
		_amount = amount;
	}
	
	
	@Override
	public operationType type() {
		return _type;
	}

	@Override
	public void type(operationType newType) {
		_type = newType;
	}

	@Override
	public float amount() {
		return _amount;
	}

	@Override
	public void amount(float newAmount) {
		_amount = newAmount;
	}

}

public class AccountImpl extends AccountPOA {

	private int _accountId;
	private String _details;
	dateImpl _dateAccountCreated;
	private float _balance;
	private Vector<OperationImpl> _accountOperations;
	
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
		_dateAccountCreated = new dateImpl(newDateAccountCreated.year(), newDateAccountCreated.month(), newDateAccountCreated.day());
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