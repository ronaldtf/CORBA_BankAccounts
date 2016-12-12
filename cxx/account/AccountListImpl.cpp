/**
 * \file AccountListImpl.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "AccountListImpl.h"

namespace account {

connection::Connection* AccountListImpl::_connection = nullptr;

AccountListImpl::~AccountListImpl() {
}

AccountListImpl::AccountListImpl(const ::corbaAccount::accountListType& a) {
	accountsList(a);
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
};

AccountListImpl::AccountListImpl() : _accountList() {
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
	_accountList.length(0);
};

corbaAccount::accountListType* AccountListImpl::accountsList() {
	corbaAccount::accountListType* acc  = new corbaAccount::accountListType;
	acc->length(_accountList.length());
	for (size_t pos = 0; pos < _accountList.length(); ++pos)
		(*acc)[pos] = _accountList[pos];
	return acc;
};

void AccountListImpl::accountsList(const ::corbaAccount::accountListType& _v) {
	_accountList = _v;
};

void AccountListImpl::addAccount(::corbaAccount::Account_ptr ac) {
	size_t len = _accountList.length();
	_accountList.length(len + 1);
	_accountList[len] = ac;
};

} /* namespace account */
