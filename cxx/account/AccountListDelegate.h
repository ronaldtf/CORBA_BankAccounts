/**
 * @file AccountListDelegate.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef ACCOUNTLISTDELEGATE_H_
#define ACCOUNTLISTDELEGATE_H_

#include "../../idl/Account.hh"

#include "AccountDelegate.h"
#include "AccountListImpl.h"

#include <memory>
#include <vector>

namespace account {

/**
 * This class implements the delegate for the list of accounts in a bank entity.
 * @see AccountListImpl.h
 */
class AccountListDelegate {
private:
	/**
	 * This is an instance of an AccountListImpl, in which the class delegates
	 */
	std::unique_ptr<AccountListImpl> _instance;
public:
	/**
	 * Create a list of accounts
	 * @param[in]	publish	Indicates whether the account needs to be added to the corba naming service
	 */
	AccountListDelegate(bool publish = true);

	/**
	 * Copy constructor
	 * @param[in] ald	AccountList to copy
	 */
	AccountListDelegate(const AccountListDelegate& ald);

	/**
	 * Class constructor
	 * @param[in] al	List of accounts to be included here
	 */
	AccountListDelegate(const ::corbaAccount::accountListType* al);

	/**
	 * Destructor of the class
	 */
	virtual ~AccountListDelegate();

	/**
	 * Add an account to the list
	 * @param[in] account	Account to be added to the list
	 */
	void addAccount(AccountDelegate& account);

	/**
	 * Get the accounts from the list
	 * @return List of accounts
	 */
    std::vector<corbaAccount::Account_ptr> getAccounts() const;

	/**
	 * Get the CORBA instance for the account list
	 * @return CORBA instance
	 */
    corbaAccount::AccountList_ptr getCorbaInstance() const;

    /**
     * Get the ids of the accounts in the list
     * @return Vector of account ids
     */
    std::vector<int> getAccountIds() const;
};

} /* namespace account */

#endif /* ACCOUNTLISTDELEGATE_H_ */
