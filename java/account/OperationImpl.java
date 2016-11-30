package account;

import connection.Connection;
import corbaAccount.Operation;
import corbaAccount.OperationPOA;
import corbaAccount.operationType;

public class OperationImpl extends OperationPOA {
	
	private int _operationId;
	private operationType _type;
	private float _amount;
	private Connection _connection;
	
	public OperationImpl(Operation op) throws Exception {
		super();
		type(op.type());
		amount(op.amount());
		operationId(op.operationId());
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	public OperationImpl(operationType type, float amount, int operationId) throws Exception {
		super();
		type(type);
		amount(amount);
		operationId(operationId);
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}

	@Override
	public operationType type() {
		return _type;
	}

	@Override
	public void type(operationType newType) {
		_type = newType;
	}

	@Override
	public float amount() {
		return _amount;
	}

	@Override
	public void amount(float newAmount) {
		_amount = newAmount;
	}

	@Override
	public int operationId() {
		return _operationId;
	}

	@Override
	public void operationId(int newOperationId) {
		_operationId = newOperationId;
	}
}