package account;

import corbaAccount.date;

public class DateDelegate {

	private DateImpl _instance;
	
	public DateDelegate() throws Exception {
		_instance = new DateImpl();
	}
	
	public DateDelegate(int year, int month, int day) throws Exception {
		_instance = new DateImpl(year,  month,  day);
	}

	public String toString() {
		return _instance.toString();
	}
	
	public int getYear() {
		return _instance.year();
	}
	
	public int getMonth() {
		return _instance.month();
	}
	
	public int getDay() {
		return _instance.day();
	}
	
	public date getCorba_instance() {
		return _instance._this();
	}
	
}
