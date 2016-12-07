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

AccountListImpl::AccountListImpl(::corbaAccount::accountListType& a) : _accountList() {
	accountsList(a);
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
};

AccountListImpl::AccountListImpl() : _accountList() {
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
};

AccountListImpl::AccountListImpl(::corbaAccount::AccountList* al) {
	_al = al;
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}

corbaAccount::accountListType* AccountListImpl::accountsList() {
	corbaAccount::accountListType* accounts = new corbaAccount::accountListType;
	accounts->length(_accountList.size());
	unsigned int pos = 0;
	for (AccountImpl ac : _accountList) {
		(*accounts)[pos]->name(ac.name());
		(*accounts)[pos]->surname(ac.surname());
		(*accounts)[pos]->dateAccountCreated(ac.dateAccountCreated());
		(*accounts)[pos]->balance(ac.balance());
		(*accounts)[pos++]->accountOperations(*ac.accountOperations());
	}
	return accounts;
};

void AccountListImpl::accountsList(const ::corbaAccount::accountListType& _v) {
	_accountList.clear();
	size_t len = _v.length();
	for (size_t pos=0; pos < len; ++pos)
		_accountList.push_back(AccountImpl(_v[pos]->name(), _v[pos]->surname(), _v[pos]->dateAccountCreated(), _v[pos]->balance(), *_v[pos]->accountOperations()));
};

void AccountListImpl::addAccount(::corbaAccount::Account_ptr ac) {
	_accountList.push_back(AccountImpl(ac->name(), ac->surname(), ac->dateAccountCreated(), ac->balance(), *ac->accountOperations()));

	if (_al != nullptr) {
		// TODO: update _al
	}
};

} /* namespace account */
