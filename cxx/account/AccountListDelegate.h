/**
 * \file AccountListDelegate.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef ACCOUNTLISTDELEGATE_H_
#define ACCOUNTLISTDELEGATE_H_

#include "AccountListImpl.h"
#include "../../idl/Account.hh"
#include <vector>
#include <memory>
#include "AccountDelegate.h"

namespace account {

class AccountListDelegate {
private:
	std::unique_ptr<AccountListImpl> _instance;
public:
	AccountListDelegate(bool publish = true);
	AccountListDelegate(const AccountListDelegate& ald);
	AccountListDelegate(const ::corbaAccount::accountListType* al);
	virtual ~AccountListDelegate();
	void addAccount(AccountDelegate& account);
    std::vector<corbaAccount::Account_ptr> getAccounts() const;
    corbaAccount::AccountList_ptr getCorbaInstance() const;
    std::vector<int> getAccountIds() const;
};

} /* namespace account */

#endif /* ACCOUNTLISTDELEGATE_H_ */
