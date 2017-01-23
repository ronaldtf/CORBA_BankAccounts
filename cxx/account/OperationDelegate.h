/**
 * \file OperationDelegate.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef OPERATIONDELEGATE_H_
#define OPERATIONDELEGATE_H_

#include "OperationImpl.h"
#include "../utils/Utils.h"
#include "../../idl/Account.hh"

namespace account {

class OperationDelegate {
private:
	OperationImpl* _instance = nullptr;
public:
	OperationDelegate();
	OperationDelegate(float amount, utils::Utils::OperationType type, int operationId, bool publish=true);
	float getAmount();
	utils::Utils::OperationType getType();
	corbaAccount::Operation_ptr getCorbaInstance();
	virtual ~OperationDelegate();
};

} /* namespace account */

#endif /* OPERATIONDELEGATE_H_ */
