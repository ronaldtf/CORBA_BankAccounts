/**
 * \file AccountListImpl.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "AccountListImpl.h"
#include <iostream>

namespace account {

connection::Connection* AccountListImpl::_connection = nullptr;

AccountListImpl::~AccountListImpl() {
	_connection->deactivateServant(this);
}

AccountListImpl::AccountListImpl(const ::corbaAccount::accountListType* a) {
	accountsList(*a);
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
};

AccountListImpl::AccountListImpl() : _accountList() {
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
	_accountList.length(0);
};

corbaAccount::accountListType* AccountListImpl::accountsList() {
	return &_accountList;
};

void AccountListImpl::accountsList(const ::corbaAccount::accountListType& _v) {
	_accountList = _v;
};

void AccountListImpl::addAccount(::corbaAccount::Account_ptr ac) {
	size_t len = _accountList.length();
	_accountList.length(len + 1);
	std::cout << len << std::endl;
	_accountList[len] = ac;
};

} /* namespace account */
