/**
 * \file AccountDelegate.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "AccountDelegate.h"
#include "../connection/Connection.h"

namespace account {

AccountDelegate::AccountDelegate(std::string name, std::string surname, int accountId) {
	AccountDelegate(name, surname, accountId, true);
}

AccountDelegate::AccountDelegate(std::string name, std::string surname, int accountId, bool publish){
	_instance = new AccountImpl(name, surname, accountId);
	if (publish)
		connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "Account" + std::to_string(_instance->accountId()), "Account");
}

AccountDelegate::AccountDelegate(std::string name, std::string surname, float balance, int accountId) {
	_instance = new AccountImpl(name, surname, balance, accountId);
}

AccountDelegate::~AccountDelegate() {
	delete _instance;
}

int AccountDelegate::getAccountId() {
	return _instance->accountId();
}
std::string AccountDelegate::getName() {
	return _instance->name();
}

float AccountDelegate::getBalance() {
	return _instance->balance();
}

std::string AccountDelegate::toString() {
	return _instance->toString();
}
DateDelegate AccountDelegate::getDate() {
	return DateDelegate(_instance->dateAccountCreated());
}
std::vector<OperationDelegate> AccountDelegate::getOperations() {
	std::vector<OperationDelegate> operations;
	corbaAccount::accountOperationsType* ops = _instance->accountOperations();
	size_t len = ops->length();
	for (size_t pos=0; pos<len; ++pos) {
		operations.push_back(OperationDelegate((*ops)[pos]->amount(), utils::Utils::convertType((*ops)[pos]->type()), (*ops)[pos]->operationId()));
	}
	return operations;
}
void AccountDelegate::addOperation(OperationDelegate op) {
	_instance->addOperation(op.getCorbaInstance());
}
corbaAccount::Account_ptr AccountDelegate::getCorbaInstance() {
	return _instance->_this();
}

} /* namespace account */
