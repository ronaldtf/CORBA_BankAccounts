/**
 * \file AccountImpl.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "AccountImpl.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>

namespace account {

connection::Connection* AccountImpl::_connection = nullptr;

AccountImpl::AccountImpl(corbaAccount::Account_ptr a) : _accountId(a->accountId()), _name(a->name()), _surname(a->surname()), _balance(a->balance()) {
	dateAccountCreated(a->dateAccountCreated());
	accountOperations(*a->accountOperations());
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}

AccountImpl::AccountImpl(std::string name, std::string surname, corbaAccount::date_ptr dateAccCreated, float balance, corbaAccount::accountOperationsType& accOperations) :
	_name(name), _surname(surname){
	dateAccountCreated(dateAccCreated);
	accountOperations(accOperations);

	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}


AccountImpl::AccountImpl(std::string name, std::string surname, float balance, int accountId) : _accountId(accountId), _name(name), _surname(surname),
		_balance(balance), _accountOperations(){

	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);

	_dateAccountCreated = new DateDelegate();
}

AccountImpl::AccountImpl(std::string name, std::string surname, int accountId) {
	AccountImpl(name, surname, 0.0f, accountId);
}

::CORBA::Long AccountImpl::accountId() {
	return _accountId;
}

void AccountImpl::accountId(::CORBA::Long _v) {
	_accountId = _v;
}
char* AccountImpl::name() {
	return const_cast<char*>(_name.c_str());
}

void AccountImpl::name(const char* _v) {
	_name = std::string(_v);
}

char* AccountImpl::surname() {
	return const_cast<char*>(_surname.c_str());
}

void AccountImpl::surname(const char* _v) {
	_surname = std::string(_v);
}

corbaAccount::date_ptr AccountImpl::dateAccountCreated() {
	return _dateAccountCreated->getCorbaInstance();
}

void AccountImpl::dateAccountCreated(::corbaAccount::date_ptr _v) {
	_dateAccountCreated = new DateDelegate(_v->year(), _v->month(), _v->day());
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
	for (size_t pos=0; pos < _accountOperations.length(); ++pos) {
		if (_accountOperations[pos]->type() == corbaAccount::operationType::WITHDRAW)
			_balance -= _accountOperations[pos]->amount();
		else
			_balance -= _accountOperations[pos]->amount();
	}
}

char* AccountImpl::details() {
	return const_cast<char*>((_name + " " + _surname).c_str());
};

void AccountImpl::addOperation(::corbaAccount::Operation_ptr op) {
	size_t pos = _accountOperations.length();
	_accountOperations.length(pos + 1);
	_accountOperations[pos] = op;
	if (op->type() == corbaAccount::operationType::WITHDRAW)
		_balance -= op->amount();
	else
		_balance -= op->amount();
};

char* AccountImpl::toString() {
	std::ostringstream os;
	os << std::setw(2) << std::setfill('0') << "accountId: " << _accountId << ", owner: " << _name << " " << _surname << ", balance: " <<
			_balance << ", operations: " << _accountOperations.length();
	return const_cast<char*>(os.str().c_str());
};
};

