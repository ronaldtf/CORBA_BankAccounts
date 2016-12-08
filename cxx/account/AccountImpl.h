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

#include "../idl/Account.hh"
#include "../connection/Connection.h"
#include "OperationImpl.h"
#include "DateImpl.h"
#include <vector>
#include <string>

namespace account {

class AccountImpl : public POA_corbaAccount::Account {
private:
	unsigned int _accountId;
	std::string _name;
	std::string _surname;
	DateImpl _dateAccountCreated;
	float _balance;
	std::vector<OperationImpl> _accountOperations;
	static connection::Connection* _connection;

public:
	AccountImpl(std::string name, std::string surname, corbaAccount::date_ptr dateAccCreated, float balance, corbaAccount::accountOperationsType& accOperations);
	AccountImpl(std::string name, std::string surname, float balance = 0);
	AccountImpl(std::string name, std::string surname, float balance, int accountId);
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
