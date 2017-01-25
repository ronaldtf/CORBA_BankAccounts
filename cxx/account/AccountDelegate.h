/**
 * \file AccountDelegate.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef ACCOUNTDELEGATE_H_
#define ACCOUNTDELEGATE_H_

#include "AccountImpl.h"
#include "../../idl/Account.hh"
#include "DateDelegate.h"
#include "OperationDelegate.h"

#include <vector>
#include <string>
#include <memory>

namespace account {

/*
 * This class implements the delegate for the user bank account
 */
class AccountDelegate {
private:
	std::unique_ptr<AccountImpl> _instance;

public:
	/**
	 * Constructor of the class
	 * \param[in] name		Account owner name
	 * \param[in] surname 	Account owner surname
	 * \param[in] accountId	Account identifier
	 * \param[in] publish	Indicates whether the account needs to be added to the corba naming service
	 */
	AccountDelegate(std::string name, std::string surname, int accountId, bool publish = true);

	/**
	 * Constructor of the class
	 * \param[in] name		Account owner name
	 * \param[in] surname 	Account owner surname
	 * \param[in] balance	Account initial balance
	 * \param[in] accountId	Account identifier
	 */
	AccountDelegate(std::string name, std::string surname, float balance, int accountId);

	/**
	 * Copy constructor of the class
	 * \param[in] ad	Another account
	 */
	AccountDelegate(const AccountDelegate& ad);

	/**
	 * Destructor of the class
	 */
	~AccountDelegate();

	/**
	 * Obtain the account identifier
	 * \return accountId
	 */
	int getAccountId() const;

	/**
	 * Obtain the account owner name
	 * \return	Owner name
	 */
	std::string getName() const;

	/**
	 * Obtain the current acccount balance
	 * \return Up-to-date account balance
	 */
	float getBalance() const;

	/**
	 * Show the account details
	 * \return String with a summary of the account
	 */
	std::string toString() const;

	/**
	 * Get the account creation date
	 * \return Account creation date
	 */
	DateDelegate getDate() const;

	/**
	 * Get the operations performed in the account
	 * \return List of operations
	 */
	std::vector<OperationDelegate> getOperations() const;

	/**
	 * Add an operation to the current account
	 * \param[in] op	Operation to be added to the current account
	 */
	void addOperation(OperationDelegate op);

	/**
	 * Gets the CORBA instance for the account
	 * \return CORBA instance
	 */
	corbaAccount::Account_ptr getCorbaInstance() const;
};

} /* namespace account */

#endif /* ACCOUNTDELEGATE_H_ */
