/**
 * @file OperationImpl.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef OPERATIONIMPL_H_
#define OPERATIONIMPL_H_

#include "../../idl/Account.hh"
#include "../connection/Connection.h"

namespace account {

/**
 * This class is an implementation of the Operation CORBA interface
 */
class OperationImpl : public POA_corbaAccount::Operation {
private:
	/**
	 * Operation type
	 */
	corbaAccount::operationType _type;
	/**
	 * Amount involved in the operation
	 */
	float _amount;
	/**
	 * Operation identifier
	 */
	int _operationId;
	/**
	 * CORBA connection, used to publish the current instance in the naming service (if proceed)
	 */
	static std::shared_ptr<connection::Connection> _connection;
public:
	/**
	 * Class constructor
	 * @param[in] op	A reference to an existing operation
	 */
	OperationImpl(corbaAccount::Operation_ptr op);

	/**
	 * Class constructor
	 * @param[in] type			Operation type
	 * @param[in] amount		Amount involved in the operation
	 * @param[in] operationId	Operation identifier
	 */
	OperationImpl(corbaAccount::operationType type, const float amount, const int operationId);

	/**
	 * Class destructor
	 */
    ~OperationImpl();

    /**
     * Get the operation type
     * @return Type of the operation
     */
	corbaAccount::operationType type();

	/**
	 * Set the operation type
	 * @param[in] _v	Operation type
	 */
    void type(::corbaAccount::operationType _v);

    /**
     * Get the amount involved in the operation
     * @return Amount
     */
    ::CORBA::Float amount();

    /**
     * Set the amount involved in the operation
     * @param[in] _v	Amount
     */
    void amount(::CORBA::Float _v);

    /**
     * Get the operation id
     * @return Id of the operation
     */
    ::CORBA::Long operationId();

    /**
     * Set the operation id
     * @param[in] _v	Operation id
     */
    void operationId(::CORBA::Long _v);

};

} /* namespace account */

#endif /* OPERATIONIMPL_H_ */
