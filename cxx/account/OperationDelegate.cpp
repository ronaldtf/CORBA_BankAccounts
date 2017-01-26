/**
 * @file OperationDelegate.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "OperationDelegate.h"

#include <string>

namespace account {

OperationDelegate::OperationDelegate(float amount, utils::Utils::OperationType type, int operationId, bool publish) {
	_instance = std::unique_ptr<OperationImpl>(new OperationImpl(utils::Utils::convertType(type), amount, operationId));
	if (publish) {
		// Appends the operationId to the reference name in CORBA the naming service (operationId is assumed to be unique)
		connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "Operation" + std::to_string(_instance->operationId()), "Operation");
	}
}

OperationDelegate::OperationDelegate(const OperationDelegate& od) {
	if (od._instance != nullptr)
		_instance = std::unique_ptr<OperationImpl>(new OperationImpl(utils::Utils::convertType(od.getType()), od.getAmount(), od._instance->operationId()));
}

OperationDelegate::~OperationDelegate() {
}

float OperationDelegate::getAmount() const {
	return _instance->amount();
}

utils::Utils::OperationType OperationDelegate::getType() const {
	return utils::Utils::convertType(_instance->type());
}

int OperationDelegate::getOperationId() const {
	return _instance->operationId();
}

corbaAccount::Operation_ptr OperationDelegate::getCorbaInstance() const {
	return _instance->_this();
}

} /* namespace account */
