/**
 * \file AccountListDelegate.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "AccountListDelegate.h"
#include "../connection/Connection.h"
#include <iostream>
#include "../idl/Account.hh"

namespace account {

AccountListDelegate::AccountListDelegate(bool publish) {
	_instance = new AccountListImpl;
	if (publish) {
		try {
			connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "AccountList", "AccountList");
		} catch (std::exception& e) {
			std::cerr << "Trying to bind an AccountList which is already bound" << std::endl;
			std::cerr << "Only one AccountList is possible in the name service" << std::endl;
		}
	}
}

AccountListDelegate::~AccountListDelegate() {
	if (_instance != nullptr)
		delete _instance;
}

AccountListDelegate::AccountListDelegate(const ::corbaAccount::accountListType& al)  {
	_instance = new AccountListImpl(al);
}

void AccountListDelegate::addAccount(AccountDelegate account) {
	_instance->addAccount(account.getCorbaInstance());
}

std::vector<corbaAccount::Account_ptr> AccountListDelegate::getAccounts() {
	std::vector<corbaAccount::Account_ptr> v;
	corbaAccount::accountListType* ac = _instance->accountsList();
	for (size_t pos=0; pos<ac->length(); ++pos)
		v.push_back((*ac)[pos]);
	return v;
}

corbaAccount::AccountList_ptr AccountListDelegate::getCorbaInstance() {
	return _instance->_this();
}

std::vector<int> AccountListDelegate::getAccountIds() {
	std::vector<int> v;
	corbaAccount::accountListType* ac = _instance->accountsList();
	for (int i=0; i<ac->length(); ++i){
		v.push_back((*ac)[i]->accountId());
	}
	return v;
}

} /* namespace account */
