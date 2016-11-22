package account;

import corbaAccount.date;
import corbaAccount.datePOA;

public class DateImpl extends datePOA {

	private int _day;
	private int _month;
	private int _year;
	
	public DateImpl(date d) {
		_day = d.day();
		_month = d.month();
		_year = d.year();
	}
	
	public DateImpl(int year, int month, int day) {
		_year = year;
		_month = month;
		_day = day;
	}
	
	public DateImpl() {
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
