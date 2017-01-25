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

class AccountDelegate {
private:
	std::unique_ptr<AccountImpl> _instance;

public:
	AccountDelegate(std::string name, std::string surname, int accountId, bool publish = true);
	AccountDelegate(std::string name, std::string surname, float balance, int accountId);
	AccountDelegate(const AccountDelegate& ad);
	~AccountDelegate();
	int getAccountId() const;
	std::string getName() const;
	float getBalance() const;
	std::string toString() const;
	DateDelegate getDate() const;
	std::vector<OperationDelegate> getOperations() const;
	void addOperation(OperationDelegate op);
	corbaAccount::Account_ptr getCorbaInstance() const;
};

} /* namespace account */

#endif /* ACCOUNTDELEGATE_H_ */
