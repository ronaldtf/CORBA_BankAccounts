package account;

import corbaAccount.Operation;

public class OperationDelegate {

	public enum OperationType {ADD, WITHDRAW}
	private OperationImpl _instance;
	
	public OperationDelegate(float amount, OperationType type) throws Exception {
		_instance = new OperationImpl(Utils.convertType(type), amount);
	}
	
	public float getAmount() {
		return _instance.amount();
	}
	
	public OperationType getType() {
		return Utils.convertType(_instance.type());
	}
	
	public Operation getCorbaInstance() {
		return _instance._this();
	}
}
