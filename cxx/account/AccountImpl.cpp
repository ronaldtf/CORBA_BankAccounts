/**
 * @file AccountImpl.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "AccountImpl.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace account {

std::shared_ptr<connection::Connection> AccountImpl::_connection = nullptr;

AccountImpl::~AccountImpl() {
	_connection->deactivateServant(this);
}

AccountImpl::AccountImpl(corbaAccount::Account_ptr a) : _accountId(a->accountId()), _name(a->name()), _surname(a->surname()), _balance(a->balance()) {
	dateAccountCreated(a->dateAccountCreated());
	accountOperations(*a->accountOperations());

	// Activate the CORBA object
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}

AccountImpl::AccountImpl(std::string name, std::string surname, corbaAccount::date_ptr dateAccCreated, float balance, corbaAccount::accountOperationsType& accOperations, unsigned int accountId) :
	_accountId(accountId), _name(name), _surname(surname), _balance(balance){
	dateAccountCreated(dateAccCreated);
	accountOperations(accOperations);

	// Activate the CORBA object
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}


AccountImpl::AccountImpl(std::string name, std::string surname, float balance, unsigned int accountId) : _accountId(accountId), _name(name), _surname(surname),
		_balance(balance), _accountOperations(){

	// Activate the CORBA object
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);

	// Initialize the account creation date
	_dateAccountCreated = new DateDelegate();
}

AccountImpl::AccountImpl(std::string name, std::string surname, unsigned int accountId) : _accountId(accountId), _name(name), _surname(surname), _balance(0.0f) {
	// Initializes the connection (for future references)
	_connection = connection::Connection::getInstance();
}

::CORBA::Long AccountImpl::accountId() {
	return _accountId;
}

void AccountImpl::accountId(::CORBA::Long _v) {
	_accountId = _v;
}
char* AccountImpl::name() {
	return CORBA::string_dup(_name.c_str());
}

void AccountImpl::name(const char* _v) {
	_name = CORBA::string_dup(_v);
}

char* AccountImpl::surname() {
	return CORBA::string_dup(_surname.c_str());
}

void AccountImpl::surname(const char* _v) {
	_surname = CORBA::string_dup(_v);
}

corbaAccount::date_ptr AccountImpl::dateAccountCreated() {
	return _dateAccountCreated->getCorbaInstance();
}

void AccountImpl::dateAccountCreated(::corbaAccount::date_ptr _v) {
	if (CORBA::is_nil(_v))
		_dateAccountCreated = new DateDelegate(_v->year(), _v->month(), _v->day());
	else {
		std::cerr << "Cannot set a NULL date to the account" << std::endl;
		throw std::exception();
	}
}

::CORBA::Float AccountImpl::balance() {
	return _balance;
}

void AccountImpl::balance(::CORBA::Float _v) {
	_balance = _v;
}

corbaAccount::accountOperationsType* AccountImpl::accountOperations() {
	return &_accountOperations;
};

void AccountImpl::accountOperations(const ::corbaAccount::accountOperationsType& _v) {
	_accountOperations = _v;
	// Update the account balance
	for (size_t pos=0; pos < _accountOperations.length(); ++pos) {
		if (_accountOperations[pos]->type() == corbaAccount::operationType::WITHDRAW)
			_balance -= _accountOperations[pos]->amount();
		else
			_balance -= _accountOperations[pos]->amount();
	}
}

char* AccountImpl::details() {
	return CORBA::string_dup((_name + " " + _surname).c_str());
};

void AccountImpl::addOperation(::corbaAccount::Operation_ptr op) {

	if (CORBA::is_nil(op)) {
		std::cerr << "Cannot add a NULL operation" << std::endl;
		throw std::exception();
	}

	size_t pos = _accountOperations.length();
	_accountOperations.length(pos + 1);
	_accountOperations[pos] = op;
	// Update the account balance
	if (op->type() == corbaAccount::operationType::WITHDRAW)
		_balance -= op->amount();
	else
		_balance += op->amount();
};

char* AccountImpl::toString() {
	std::ostringstream os;
	os << std::setw(2) << std::setfill('0') << "accountId: " << _accountId << ", owner: " << _name << " " << _surname << ", balance: " <<
			_balance << ", operations: " << _accountOperations.length();
	return CORBA::string_dup(os.str().c_str());
};
};

