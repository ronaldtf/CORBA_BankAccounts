/**
 * @file AccountListImpl.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "AccountListImpl.h"

#include <exception>
#include <iostream>

namespace account {

std::shared_ptr<connection::Connection> AccountListImpl::_connection = nullptr;

AccountListImpl::~AccountListImpl() {
	_connection->deactivateServant(this);
}

AccountListImpl::AccountListImpl(const ::corbaAccount::accountListType* a) {
	if (a == NULL) {
		std::cerr << "Cannot set a NULL account list" << std::endl;
		throw std::exception();
	}
	accountsList(*a);

	// Activate the CORBA object
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
};

AccountListImpl::AccountListImpl() : _accountList() {

	// Activate the CORBA object
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
	_accountList.length(0);
};

corbaAccount::accountListType* AccountListImpl::accountsList() {
	// IMPORTANT: We need to create a new pointer because the remote CORBA instance
	// might be removed when we want to access to it from the outside.
	return new corbaAccount::accountListType(_accountList);
};

void AccountListImpl::accountsList(const ::corbaAccount::accountListType& _v) {
	_accountList = _v;
};

void AccountListImpl::addAccount(::corbaAccount::Account_ptr ac) {
	if (CORBA::is_nil(ac)) {
		std::cerr << "Cannot add a NULL account" << std::endl;
		throw std::exception();
	}

	size_t len = _accountList.length();
	_accountList.length(len + 1);
	_accountList[len] = ac;
};

} /* namespace account */
