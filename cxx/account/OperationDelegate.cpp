/**
 * \file OperationDelegate.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "OperationDelegate.h"
#include <string>

namespace account {

OperationDelegate::OperationDelegate(float amount, utils::Utils::OperationType type, int operationId, bool publish) {
	_instance = new OperationImpl(utils::Utils::convertType(type), amount, operationId);
	if (publish) {
		connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "Operation" + std::to_string(_instance->operationId()), "Operation");
	}
}

OperationDelegate::~OperationDelegate() {
	delete _instance;
}

float OperationDelegate::getAmount() {
	return _instance->amount();
}

utils::Utils::OperationType OperationDelegate::getType() {
	return utils::Utils::convertType(_instance->type());
}

corbaAccount::Operation_ptr OperationDelegate::getCorbaInstance() {
	return _instance->_this();
}

} /* namespace account */
