/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package account;

import corbaAccount.Operation;
import corbaAccount.OperationPOA;
import corbaAccount.operationType;

import connection.Connection;

/**
 * This class is an implementation of the Operation CORBA interface
 */
public class OperationImpl extends OperationPOA {
	
	/**
	 * Operation identifier
	 */
	private int _operationId;
	/**
	 * Operation type
	 */
	private operationType _type;
	/**
	 * Amount involved in the operation
	 */
	private float _amount;
	/**
	 * CORBA connection, used to publish the current instance in the naming service (if proceed)
	 */
	private Connection _connection;
	
	/**
	 * Class constructor
	 * @param op	A reference to an existing operation
	 * @throws Exception Throws an exception in case of any problem
	 */
	public OperationImpl(Operation op) throws Exception {
		super();
		type(op.type());
		amount(op.amount());
		operationId(op.operationId());
		
		// Activate the CORBA object
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}
	
	/**
	 * Class constructor
	 * @param type			Operation type
	 * @param amount		Amount involved in the operation
	 * @param operationId	Operation identifier
	 * @throws Exception Throws an exception in case of any problem
	 */
	public OperationImpl(operationType type, float amount, int operationId) throws Exception {
		super();
		type(type);
		amount(amount);
		operationId(operationId);
		
		// Activate the CORBA object
		_connection = Connection.getInstance();
		_connection.activateServant(this);
	}

    /**
     * Get the operation type
     * @return Type of the operation
     */
	@Override
	public operationType type() {
		return _type;
	}
	
	/**
	 * Set the operation type
	 * @param newType	Operation type
	 */
	@Override
	public void type(operationType newType) {
		_type = newType;
	}

    /**
     * Get the amount involved in the operation
     * @return Amount
     */
	@Override
	public float amount() {
		return _amount;
	}

    /**
     * Set the amount involved in the operation
     * @param newAmount	Amount
     */
	@Override
	public void amount(float newAmount) {
		_amount = newAmount;
	}

    /**
     * Get the operation id
     * @return Id of the operation
     */
	@Override
	public int operationId() {
		return _operationId;
	}

    /**
     * Set the operation id
     * @param newOperationId	Operation id
     */
	@Override
	public void operationId(int newOperationId) {
		_operationId = newOperationId;
	}
}