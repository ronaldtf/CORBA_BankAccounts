/**
 * \file AccountImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef ACCOUNTIMPL_H_
#define ACCOUNTIMPL_H_

/**
 * \file AccountImpl.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "../../idl/Account.hh"
#include "../connection/Connection.h"
#include "OperationImpl.h"
#include "DateDelegate.h"
#include "DateImpl.h"
#include <vector>
#include <string>
#include <memory>

namespace account {

class AccountImpl : public POA_corbaAccount::Account {
private:
	unsigned int _accountId;
	std::string _name;
	std::string _surname;
	DateDelegate* _dateAccountCreated;
	float _balance;
	corbaAccount::accountOperationsType _accountOperations;
	static std::shared_ptr<connection::Connection> _connection;

public:
	AccountImpl(corbaAccount::Account_ptr a);
	AccountImpl(std::string name, std::string surname, corbaAccount::date_ptr dateAccCreated, float balance, corbaAccount::accountOperationsType& accOperations, unsigned int accountId);
	AccountImpl(std::string name, std::string surname, float balance, unsigned int accountId);
	AccountImpl(std::string name, std::string surname, unsigned int accountId);
	~AccountImpl();
    ::CORBA::Long accountId();
    void accountId(::CORBA::Long _v);
    char* name();
    void name(const char* _v);
    char* surname();
    void surname(const char* _v);
    corbaAccount::date_ptr dateAccountCreated();
    void dateAccountCreated(::corbaAccount::date_ptr _v);
    ::CORBA::Float balance();
    void balance(::CORBA::Float _v);
    corbaAccount::accountOperationsType* accountOperations();
    void accountOperations(const ::corbaAccount::accountOperationsType& _v);
    char* details();
    void addOperation(::corbaAccount::Operation_ptr op);
    char* toString();
};

};


#endif /* ACCOUNTIMPL_H_ */
