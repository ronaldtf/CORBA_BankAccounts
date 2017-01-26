/**
 * @file AccountListDelegate.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "../../idl/Account.hh"
#include "../connection/Connection.h"

#include "AccountListDelegate.h"

#include <iostream>

namespace account {

AccountListDelegate::AccountListDelegate(bool publish) {
	_instance = std::unique_ptr<AccountListImpl>(new AccountListImpl);
	if (publish) {
		try {
			// Publish the object in the CORBA naming service.
			// IMPORTANT: 	As the object name is fix, there will be only one account list (only bank entity would exist).
			//				In case of multiple AccountsLists (multiple entities), we would need to add something that
			//				differentiates one object to the others (for instance, add an accountListId or bankAccountName
			//				to the CORBA object name when publishing it in the naming service).
			connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "AccountList", "AccountList");
		} catch (std::exception& e) {
			std::cerr << "Trying to bind an AccountList which is already bound" << std::endl;
			std::cerr << "Only one AccountList is possible in the name service" << std::endl;
		}
	}
}

AccountListDelegate::AccountListDelegate(const AccountListDelegate& ald) {
	_instance = std::unique_ptr<AccountListImpl>(new AccountListImpl());
	if (ald._instance != nullptr) {
		corbaAccount::accountListType* l =  ald._instance->accountsList();
		for (int i=0; i<l->length(); ++i)
			_instance->addAccount((*l)[i]);
	}
}

AccountListDelegate::~AccountListDelegate() {
}

AccountListDelegate::AccountListDelegate(const ::corbaAccount::accountListType* al)  {
	_instance = std::unique_ptr<AccountListImpl>(new AccountListImpl(al));
}

void AccountListDelegate::addAccount(AccountDelegate& account) {
	_instance->addAccount(account.getCorbaInstance());
}

std::vector<corbaAccount::Account_ptr> AccountListDelegate::getAccounts() const {
	std::vector<corbaAccount::Account_ptr> v;
	// We need to do the conversion between the corbaAccount::accountListType CORBA
	// object and the vector returned here
	corbaAccount::accountListType* ac = _instance->accountsList();
	for (size_t pos=0; pos<ac->length(); ++pos)
		v.push_back((*ac)[pos]);
	return v;
}

corbaAccount::AccountList_ptr AccountListDelegate::getCorbaInstance() const {
	return _instance->_this();
}

std::vector<int> AccountListDelegate::getAccountIds() const {
	std::vector<int> v;
	corbaAccount::accountListType* ac = _instance->accountsList();
	for (int i=0; i<ac->length(); ++i){
		v.push_back((*ac)[i]->accountId());
	}
	return v;
}

} /* namespace account */
