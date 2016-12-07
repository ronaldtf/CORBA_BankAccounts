/**
 * \file AccountListImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef ACCOUNTLISTIMPL_H_
#define ACCOUNTLISTIMPL_H_

#include "../idl/Account.hh"
#include "../connection/Connection.h"
#include "AccountImpl.h"
#include <vector>

namespace account {

class AccountListImpl: public POA_corbaAccount::AccountList {
private:
	static connection::Connection* _connection;
	std::vector<AccountImpl> _accountList;
	::corbaAccount::AccountList* _al;



public:
	AccountListImpl();
	~AccountListImpl();
	AccountListImpl(::corbaAccount::accountListType& a);
	AccountListImpl(::corbaAccount::AccountList* al);
    corbaAccount::accountListType* accountsList();
    void accountsList(const ::corbaAccount::accountListType& _v);
    void addAccount(::corbaAccount::Account_ptr ac);
};

} /* namespace account */

#endif /* ACCOUNTLISTIMPL_H_ */
