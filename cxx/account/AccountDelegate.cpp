/**
 * @file AccountDelegate.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "../connection/Connection.h"

#include "AccountDelegate.h"

namespace account {

AccountDelegate::AccountDelegate(std::string name, std::string surname, int accountId, bool publish) {
	_instance = std::unique_ptr<AccountImpl>(new AccountImpl(name, surname, accountId));
	if (publish) {
		// Appends the accountId to the reference name in CORBA the naming service (accountId is assumed to be unique)
		connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "Account" + std::to_string(_instance->accountId()), "Account");
	}
}

AccountDelegate::AccountDelegate(std::string name, std::string surname, float balance, int accountId) {
	_instance = std::unique_ptr<AccountImpl>(new AccountImpl(name, surname, balance, accountId));
}

AccountDelegate::AccountDelegate(const AccountDelegate& ad) {
	_instance = std::unique_ptr<AccountImpl>(new AccountImpl(ad._instance->name(), ad._instance->surname(), ad._instance->balance(), ad._instance->accountId()));
}

AccountDelegate::~AccountDelegate() {
}

int AccountDelegate::getAccountId() const{
	return _instance->accountId();
}
std::string AccountDelegate::getName()  const{
	return _instance->name();
}

float AccountDelegate::getBalance() const {
	return _instance->balance();
}

std::string AccountDelegate::toString() const {
	return _instance->toString();
}
DateDelegate AccountDelegate::getDate() const {
	corbaAccount::date_ptr date = _instance->dateAccountCreated();
	return DateDelegate(date->year(), date->month(), date->day());
}
std::vector<OperationDelegate> AccountDelegate::getOperations() const {
	std::vector<OperationDelegate> operations;
	// Convert the operations list in the CORBA format
	// to the returned vector type
	corbaAccount::accountOperationsType* ops = _instance->accountOperations();
	size_t len = ops->length();
	for (size_t pos=0; pos<len; ++pos) {
		operations.push_back(OperationDelegate((*ops)[pos]->amount(), utils::Utils::convertType((*ops)[pos]->type()), (*ops)[pos]->operationId(), false));
	}
	return operations;
}
void AccountDelegate::addOperation(OperationDelegate op) {
	_instance->addOperation(op.getCorbaInstance());
}
corbaAccount::Account_ptr AccountDelegate::getCorbaInstance() const{
	return _instance->_this();
}

} /* namespace account */
