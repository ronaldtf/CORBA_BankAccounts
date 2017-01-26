/**
 * @file AccountListImpl.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef ACCOUNTLISTIMPL_H_
#define ACCOUNTLISTIMPL_H_

#include "../../idl/Account.hh"
#include "../connection/Connection.h"

#include "AccountImpl.h"

#include <memory>
#include <vector>

namespace account {

/**
 * This class is an implementation of the AccountList CORBA interface
 */
class AccountListImpl: public POA_corbaAccount::AccountList {
private:
	/**
	 * CORBA connection, used to publish the current instance in the naming service (if proceed)
	 */
	static std::shared_ptr<connection::Connection> _connection;
	/**
	 * CORBA AccountList reference
	 */
	::corbaAccount::accountListType _accountList;

public:
	/**
	 * Class constructor
	 */
	AccountListImpl();

	/**
	 * Class destructor
	 */
	~AccountListImpl();

	/**
	 * Class constructor
	 * @param[in] a		List of accounts
	 */
	AccountListImpl(const ::corbaAccount::accountListType* a);

	/**
	 * Get the list of accounts
	 * @return CORBA object with the list of accounts
	 */
    corbaAccount::accountListType* accountsList();

	/**
	 * Set the list of accounts
	 * @param[in] _v List of accounts. IMPORTANT: Previous accounts will not
	 * be taken into account (removed)
	 */
    void accountsList(const ::corbaAccount::accountListType& _v);

	/**
	 * Add and account
	 * @param[in] ac	Account to be added
	 */
    void addAccount(::corbaAccount::Account_ptr ac);
};

} /* namespace account */

#endif /* ACCOUNTLISTIMPL_H_ */
