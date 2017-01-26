/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package account;

import java.util.Calendar;

import corbaAccount.date;

import connection.Connection;

/**
 * This class implements the delegate for date.
 * @see DateImpl
 */
public class DateDelegate {

	/**
	 * This is an instance of an DateImpl, in which the class delegates
	 */
	private DateImpl _instance;
	
	/**
	 * Class constructor
	 * @throws Exception Throws an exception in case of any problem
	 */
	public DateDelegate() throws Exception {
		this(true);
	}

	/**
	 * Class constructor
	 * @param publish	Indicates whether the date needs to be added to the corba naming service
	 * @throws Exception Throws an exception in case of any problem
	 */
	public DateDelegate(boolean publish) throws Exception {
		_instance = new DateImpl();
		if (publish) {
			Calendar c = Calendar.getInstance();
			// We assume that two instances of date can be created on the same second. Otherwise, we could skip the milliseconds.
			String time = String.format("%02d", Integer.valueOf(c.get(Calendar.HOUR))) + ":" + 
							String.format("%02d", Integer.valueOf(c.get(Calendar.MINUTE))) + ":" + 
							String.format("%02d", Integer.valueOf(c.get(Calendar.SECOND))) +
							String.format("%02d", Integer.valueOf(c.get(Calendar.MILLISECOND)));
			// Appends the current time to the reference name in CORBA the naming service
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Date"+_instance._toString() + "_" + time, "Date");
		}
	}	
	
	/**
	 * Class constructor
	 * @param year	Year
	 * @param month	Month
	 * @param day	Day
	 * @throws Exception Throws an exception in case of any problem
	 */
	public DateDelegate(int year, int month, int day) throws Exception {
		this(year, month, day, true);
	}

	/**
	 * @param year	Year
	 * @param month	Month
	 * @param day	Day
	 * @param publish	Indicates whether the date needs to be added to the corba naming service
	 * @throws Exception Throws an exception in case of any problem
	 */
	public DateDelegate(int year, int month, int day, boolean publish) throws Exception {
		_instance = new DateImpl(year,  month,  day);
		if (publish)
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Date"+_instance._toString(), "Date");
	}
	
	/**
	 * Get the date in String format
	 * @return Date in String format
	 */
	public String toString() {
		return _instance._toString();
	}
	
	/**
	 * Get the year
	 * @return Year
	 */
	public int getYear() {
		return _instance.year();
	}

	/**
	 * Get the month
	 * @return Month
	 */
	public int getMonth() {
		return _instance.month();
	}
	
	/**
	 * Get the day
	 * @return Day
	 */
	public int getDay() {
		return _instance.day();
	}
	
	/**
	 * Get the CORBA instance of the date
	 * @return date CORBA instance
	 */
	public date getCorbaInstance() {
		return _instance._this();
	}
	
}
