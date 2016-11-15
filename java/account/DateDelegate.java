package account;

public class DateDelegate {

	private dateImpl instance;
	
	public DateDelegate() {
		instance = new dateImpl();
	}
	
	public DateDelegate(int year, int month, int day) {
		instance = new dateImpl(year,  month,  day);
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
	
	public dateImpl getCorbaInstance() {
		return instance;
	}
}
