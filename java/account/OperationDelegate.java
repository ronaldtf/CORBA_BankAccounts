package account;

public class OperationDelegate {

	public enum OperationType {ADD, WITHDRAW}
	private OperationImpl instance;
	
	public OperationDelegate(float amount, OperationType type) {
		instance = new OperationImpl(Utils.convertType(type), amount);
	}
	
	public float getAmount() {
		return instance.amount();
	}
	
	public OperationType getType() {
		return Utils.convertType(instance.type());
	}
}
