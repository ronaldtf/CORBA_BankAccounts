/**
 * \file OperationImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef OPERATIONIMPL_H_
#define OPERATIONIMPL_H_

#include "../idl/Account.hh"
#include "../connection/Connection.h"

namespace account {

class OperationImpl : public POA_corbaAccount::Operation {
private:
	corbaAccount::operationType _type;
	float _amount;
	int _operationId;
	static connection::Connection* _connection;
public:
	OperationImpl(corbaAccount::Operation_ptr op);
	OperationImpl(corbaAccount::operationType type, const float amount, const int operationId);
    corbaAccount::operationType type();
    void type(::corbaAccount::operationType _v);
    ::CORBA::Float amount();
    void amount(::CORBA::Float _v);
    ::CORBA::Long operationId();
    void operationId(::CORBA::Long _v);

};

} /* namespace account */

#endif /* OPERATIONIMPL_H_ */
