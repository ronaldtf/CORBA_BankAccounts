/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package account;

import corbaAccount.Operation;

import connection.Connection;
import utils.Utils;

/**
 * This class implements the delegate for the account operation.
 * @see OperationImpl
 */
public class OperationDelegate {
	
	/**
	 * This is an instance of an OperationImpl, in which the class delegates
	 */
	private OperationImpl _instance;
	
	/**
	 * Class constructor
	 * @param amount		Amount involved in the operation
	 * @param type			Type of operation
	 * @param operationId	Operation identifier
	 * @param publish		Indicates whether the operation needs to be added to the corba naming service
	 * @throws Exception Throws an exception in case of any problem
	 */
	public OperationDelegate(float amount, Utils.OperationType type, int operationId, boolean publish) throws Exception {
		_instance = new OperationImpl(Utils.convertType(type), amount, operationId);
		if (publish) {
			// Appends the operationId to the reference name in CORBA the naming service (operationId is assumed to be unique)
			Connection.getInstance().bindObjectToName(_instance._this(), "myContext", "Operation"+_instance.operationId(), "Operation");
		}
	}
	
	/**
	 * Class constructor
	 * @param amount		Amount involved in the operation
	 * @param type			Type of operation
	 * @param operationId	Operation identifier
	 * @throws Exception Throws an exception in case of any problem
	 */
	public OperationDelegate(float amount, Utils.OperationType type, int operationId) throws Exception {
		this(amount, type, operationId, true);
	}
	
	/**
	 * Get the amount involved in the operation
	 * @return	Amount
	 */
	public float getAmount() {
		return _instance.amount();
	}
	
	/**
	 * Get the type of operation
	 * @return Operation type
	 */
	public Utils.OperationType getType() {
		return Utils.convertType(_instance.type());
	}
	
	/**
	 * Get the operation identifier
	 * @return Operation identifier
	 */
	public int getOperationId() {
		return _instance.operationId();
	}
	
	/**
	 * Gets the CORBA instance for the operation
	 * @return CORBA instance
	 */
	public Operation getCorbaInstance() {
		return _instance._this();
	}
}
