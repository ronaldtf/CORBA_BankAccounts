package account;

import corbaAccount.Operation;
import corbaAccount.OperationPOA;
import corbaAccount.operationType;

public class OperationImpl extends OperationPOA {

	private operationType _type;
	private float _amount;
	
	public OperationImpl(Operation op) {
		_type = op.type();
		_amount = op.amount();
	}
	
	public OperationImpl(operationType type, float amount) {
		_type = type;
		_amount = amount;
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

}