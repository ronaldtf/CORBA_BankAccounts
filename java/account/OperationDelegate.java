package account;

import connection.Connection;
import corbaAccount.Operation;

public class OperationDelegate {

	public enum OperationType {ADD, WITHDRAW}
	private OperationImpl _instance;
	
	public OperationDelegate(float amount, OperationType type, int operationId, boolean publish) throws Exception {
		_instance = new OperationImpl(Utils.convertType(type), amount, operationId);
		if (publish) {
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Operation"+_instance.operationId(), "Operation");
		}
	}
	
	public OperationDelegate(float amount, OperationType type, int operationId) throws Exception {
		this(amount, type, operationId, true);
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
	
	public int getOperationId() {
		return _instance.operationId();
	}
}
