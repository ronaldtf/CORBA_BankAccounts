/**
 * \file OperationImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef OPERATIONIMPL_H_
#define OPERATIONIMPL_H_

namespace account {

class OperationImpl: public corbaAccount::Operation {
public:
	OperationImpl();
	virtual ~OperationImpl();
};

} /* namespace account */

#endif /* OPERATIONIMPL_H_ */
