/**
 * @file OperationDelegate.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef OPERATIONDELEGATE_H_
#define OPERATIONDELEGATE_H_

#include "../../idl/Account.hh"
#include "../utils/Utils.h"

#include "OperationImpl.h"

namespace account {

/**
 * This class implements the delegate for the account operation.
 * @see OperationImpl.h
 */
class OperationDelegate {
private:
	/**
	 * This is an instance of an OperationImpl, in which the class delegates
	 */
	std::unique_ptr<OperationImpl> _instance;
public:
	/**
	 * Class constructor
	 */
	OperationDelegate();

	/**
	 * Copy constructor
	 * @param[in] od	Operation to be copied
	 */
	OperationDelegate(const OperationDelegate& od);

	/**
	 * Class constructor
	 * @param[in] amount		Amount involved in the operation
	 * @param[in] type			Type of operation
	 * @param[in] operationId	Operation identifier
	 * @param[in] publish		Indicates whether the operation needs to be added to the corba naming service
	 */
	OperationDelegate(float amount, utils::Utils::OperationType type, int operationId, bool publish=true);

	/**
	 * Destructor of the class
	 */
	virtual ~OperationDelegate();

	/**
	 * Get the amount involved in the operation
	 * @return	Amount
	 */
	float getAmount() const;

	/**
	 * Get the type of operation
	 * @return Operation type
	 */
	utils::Utils::OperationType getType() const;

	/**
	 * Get the operation identifier
	 * @return Operation identifier
	 */
	int getOperationId() const;

	/**
	 * Gets the CORBA instance for the operation
	 * @return CORBA instance
	 */
	corbaAccount::Operation_ptr getCorbaInstance() const;

};

} /* namespace account */

#endif /* OPERATIONDELEGATE_H_ */
