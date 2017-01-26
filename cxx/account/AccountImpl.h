/**
 * @file AccountImpl.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef ACCOUNTIMPL_H_
#define ACCOUNTIMPL_H_

#include "../../idl/Account.hh"
#include "../connection/Connection.h"

#include "DateDelegate.h"
#include "DateImpl.h"
#include "OperationImpl.h"

#include <memory>
#include <string>
#include <vector>

namespace account {

/**
 * This class is an implementation of the Account CORBA interface
 */
class AccountImpl : public POA_corbaAccount::Account {
private:
	/**
	 * Account identifier
	 */
	unsigned int _accountId;
	/**
	 * Account owner name
	 */
	std::string _name;
	/**
	 * Account owner surname
	 */
	std::string _surname;
	/**
	 * Account creation date
	 */
	DateDelegate* _dateAccountCreated;
	/**
	 * Updated account balance
	 */
	float _balance;
	/**
	 * Operations performed in the account
	 */
	corbaAccount::accountOperationsType _accountOperations;
	/**
	 * CORBA connection, used to publish the current instance in the naming service (if proceed)
	 */
	static std::shared_ptr<connection::Connection> _connection;

public:
	/**
	 * Class constructor
	 * @param[in] a A reference to an already existing account
	 */
	AccountImpl(corbaAccount::Account_ptr a);
	/**
	 * Class constructor
	 * @param[in] name 				Account owner name
	 * @param[in] surname			Account owner surname
	 * @param[in] dateAccCreated	Account creation date
	 * @param[in] balance			Initial account balance
	 * @param[in] accOperations		Operations performed in the account
	 * @param[in] accountId			Account identifier
	 */
	AccountImpl(std::string name, std::string surname, corbaAccount::date_ptr dateAccCreated, float balance, corbaAccount::accountOperationsType& accOperations, unsigned int accountId);

	/**
	 * Class constructor
	 * @param[in] name 				Account owner name
	 * @param[in] surname			Account owner surname
	 * @param[in] balance			Initial account balance
	 * @param[in] accountId			Account identifier
	 */
	AccountImpl(std::string name, std::string surname, float balance, unsigned int accountId);

	/**
	 * Class constructor
	 * @param[in] name 				Account owner name
	 * @param[in] surname			Account owner surname
	 * @param[in] accountId			Account identifier
	 */
	AccountImpl(std::string name, std::string surname, unsigned int accountId);

	/**
	 * Destructor of the class
	 */
	~AccountImpl();

	/**
	 * Get the accountId
	 * @return accountId
	 */
    ::CORBA::Long accountId();

    /**
     * Set the accountId
     * @param[in]	_v new accountId
     */
    void accountId(::CORBA::Long _v);

    /**
     * Get the account owner name
     * @return Owner name
     */
    char* name();

    /**
     * Set the account owner name
     * @param[in]	_v new name
     */
    void name(const char* _v);

    /**
     * Get the account owner surname
     * @return Owner surname
     */
    char* surname();

    /**
     * Set the account owner surname
     * @param[in]	_v new surname
     */
    void surname(const char* _v);

    /**
     * Get the account creation date
     * @return Account creation date
     */
    corbaAccount::date_ptr dateAccountCreated();

    /**
     * Set the account creation date
     * * @param[in]	_v new creation date
     */
    void dateAccountCreated(::corbaAccount::date_ptr _v);

    /**
     * Get the account balance
     * @return balance
     */
    ::CORBA::Float balance();

    /**
     * Set the account balance
     * @param[in]	_v new balance
     */
    void balance(::CORBA::Float _v);

    /**
     * Get the list of operations performed in the account
     * @return List of accountOperations
     */
    corbaAccount::accountOperationsType* accountOperations();

    /**
     * Set the list of account operations in the account.
     * NOTE: This overrides the existing accounts in case they exist!
     * @param[in]	_v New account operations
     */
    void accountOperations(const ::corbaAccount::accountOperationsType& _v);

    /**
     * Get the account owner full name
     * @return Concatenation os name and surname
     */
    char* details();

    /**
     * Add an operation and update the account balance
     * @param[in]	op
     */
    void addOperation(::corbaAccount::Operation_ptr op);

    /**
     * Get a summary of the account
     * @return String with the details of the account
     */
    char* toString();
};

};


#endif /* ACCOUNTIMPL_H_ */
