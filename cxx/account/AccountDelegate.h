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

namespace account {

class AccountDelegate {
private:
	AccountImpl* _instance = nullptr;

public:
	AccountDelegate(std::string name, std::string surname, int accountId, bool publish = true);
	AccountDelegate(std::string name, std::string surname, float balance, int accountId);
	~AccountDelegate();
	int getAccountId();
	std::string getName();
	float getBalance();
	std::string toString();
	DateDelegate getDate();
	std::vector<OperationDelegate> getOperations() ;
	void addOperation(OperationDelegate op);
	corbaAccount::Account_ptr getCorbaInstance();
};

} /* namespace account */

#endif /* ACCOUNTDELEGATE_H_ */
