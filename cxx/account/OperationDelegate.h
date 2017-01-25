/**
 * \file OperationDelegate.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef OPERATIONDELEGATE_H_
#define OPERATIONDELEGATE_H_

#include "../../idl/Account.hh"
#include "../utils/Utils.h"

#include "OperationImpl.h"

namespace account {

class OperationDelegate {
private:
	std::unique_ptr<OperationImpl> _instance;
public:
	OperationDelegate();
	OperationDelegate(const OperationDelegate& od);
	OperationDelegate(float amount, utils::Utils::OperationType type, int operationId, bool publish=true);
	float getAmount() const;
	utils::Utils::OperationType getType() const;
	corbaAccount::Operation_ptr getCorbaInstance() const;
	virtual ~OperationDelegate();
};

} /* namespace account */

#endif /* OPERATIONDELEGATE_H_ */
