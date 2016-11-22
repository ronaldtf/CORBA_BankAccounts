package account;

public class DateDelegate {

	private DateImpl instance;
	
	public DateDelegate() {
		instance = new DateImpl();
	}
	
	public DateDelegate(int year, int month, int day) {
		instance = new DateImpl(year,  month,  day);
	}
	
	public String toString() {
		return instance.toString();
	}
	
	public int getYear() {
		return instance.year();
	}
	
	public int getMonth() {
		return instance.month();
	}
	
	public int getDay() {
		return instance.day();
	}
	
	public DateImpl getCorbaInstance() {
		return instance;
	}
}
