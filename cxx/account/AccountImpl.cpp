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

AccountImpl::AccountImpl(std::string name, std::string surname, corbaAccount::date_ptr dateAccCreated, float balance, corbaAccount::accountOperationsType& accOperations) :
	_name(name), _surname(surname){
	dateAccountCreated(dateAccCreated);
	accountOperations(accOperations);

	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}


AccountImpl::AccountImpl(std::string name, std::string surname, float balance) : _name(name), _surname(surname), _balance(balance),
		_accountOperations() {
	static unsigned int id;
	_accountId = ++id;

	std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(timepoint);
	struct tm* tmp = localtime(&t);
	_dateAccountCreated = DateImpl(tmp->tm_year, tmp->tm_mon, tmp->tm_mday);
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}


AccountImpl::AccountImpl(std::string name, std::string surname, float balance, int accountId) : _accountId(accountId), _name(name), _surname(surname),
		_balance(balance), _accountOperations(){

	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);

	_dateAccountCreated = DateImpl();
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
	corbaAccount::date_ptr d = corbaAccount::date_ptr();
	d->year(_dateAccountCreated.year());
	d->month(_dateAccountCreated.month());
	d->day(_dateAccountCreated.day());
	return d;
}

void AccountImpl::dateAccountCreated(::corbaAccount::date_ptr _v) {
	_dateAccountCreated = DateImpl(_v->year(), _v->month(), _v->day());
}


::CORBA::Float AccountImpl::balance() {
	return _balance;
}

void AccountImpl::balance(::CORBA::Float _v) {
	_balance = _v;
}

corbaAccount::accountOperationsType* AccountImpl::accountOperations() {
	corbaAccount::accountOperationsType* ops = new corbaAccount::accountOperationsType;
	ops->length(_accountOperations.size());
	unsigned int pos = 0;
	for (OperationImpl op : _accountOperations) {
		(*ops)[pos]->type(op.type());
		(*ops)[pos++]->amount(op.amount());
	}
	return ops;
};

void AccountImpl::accountOperations(const ::corbaAccount::accountOperationsType& _v) {
	_accountOperations.clear();
	size_t len = _v.length();
	for (size_t pos=0; pos<len; ++pos) {
		_accountOperations.push_back(OperationImpl(_v[pos]->type(), _v[pos]->amount(), _v[pos]->operationId()));
	}
}

char* AccountImpl::details() {
	return const_cast<char*>((_name + " " + _surname).c_str());
};

void AccountImpl::addOperation(::corbaAccount::Operation_ptr op) {
	_accountOperations.push_back(OperationImpl(op->type(), op->amount(), op->operationId()));
};

char* AccountImpl::toString() {
	std::ostringstream os;
	os << std::setw(2) << std::setfill('0') << "accountId: " << _accountId << ", owner: " << _name << " " << _surname << ", balance: " <<
			_balance << ", operations: " << _accountOperations.size();
	return const_cast<char*>(os.str().c_str());
};
};

