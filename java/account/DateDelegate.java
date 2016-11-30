package account;

import java.util.Calendar;

import connection.Connection;
import corbaAccount.date;

public class DateDelegate {

	private DateImpl _instance;
	
	public DateDelegate() throws Exception {
		this(true);
	}

	public DateDelegate(boolean publish) throws Exception {
		_instance = new DateImpl();
		if (publish) {
			Calendar c = Calendar.getInstance();
			// We assume that two instances of date can be created on the same second. Otherwise, we could skip the milliseconds.
			String time = String.format("%02d", Integer.valueOf(c.get(Calendar.HOUR))) + ":" + 
							String.format("%02d", Integer.valueOf(c.get(Calendar.MINUTE))) + ":" + 
							String.format("%02d", Integer.valueOf(c.get(Calendar.SECOND))) +
							String.format("%02d", Integer.valueOf(c.get(Calendar.MILLISECOND)));
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Date"+_instance._toString() + "_" + time, "Date");
		}
	}	
	
	public DateDelegate(int year, int month, int day) throws Exception {
		this(year, month, day, true);
	}

	public DateDelegate(int year, int month, int day, boolean publish) throws Exception {
		_instance = new DateImpl(year,  month,  day);
		if (publish)
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Date"+_instance._toString(), "Date");
	}
	
	public String toString() {
		return _instance._toString();
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
	
	public date getCorbaInstance() {
		return _instance._this();
	}
	
}
