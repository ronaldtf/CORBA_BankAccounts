package account;

import java.util.Calendar;

import connection.Connection;
import corbaAccount.date;
import corbaAccount.datePOA;

public class DateImpl extends datePOA {

	private int _day;
	private int _month;
	private int _year;
	private Connection _connection;

	public DateImpl(date d) throws Exception {
		super();
		day(d.day());
		month(d.month());
		year(d.year());
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	public DateImpl(int year, int month, int day) throws Exception {
		super();
		day(day);
		month(month);
		year(year);
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	public DateImpl() throws Exception {
		this(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH));
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
				String.format("%2s",Integer.valueOf(_month)).replaceAll(" " , "0") + "/" +
				String.format("%2s",Integer.valueOf(_day)).replaceAll(" " , "0");
	}
	
}
