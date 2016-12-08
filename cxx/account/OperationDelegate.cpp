/**
 * \file OperationDelegate.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "OperationDelegate.h"

namespace account {

OperationDelegate::OperationDelegate() {

}

OperationDelegate::~OperationDelegate() {

}

OperationDelegate::OperationDelegate(float amount, utils::Utils::OperationType type, int operationId, bool publish)  {
		_instance = new OperationImpl(utils::Utils::convertType(type), amount, operationId);
		if (publish) {
			connection::Connection::getInstance()->bindObjectToName(_instance._this(), "myContext", "Operation"+_instance.operationId(), "Operation");
		}
	}

corbaAccount::Operation_ptr OperationDelegate::getCorbaInstance() {
	return _instance->this();
}

} /* namespace account */
