/**
 * \file Client.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include <iostream>
#include "../idl/Account.hh"
#include "../connection/Connection.h"
#include "../account/AccountDelegate.h"
#include "../account/AccountListDelegate.h"

int main() {
	try {
		CORBA::Object_ptr objAccountList = connection::Connection::getInstance()->getClientObject("myContext", "AccountList", "AccountList");
		corbaAccount::AccountList_ptr list = corbaAccount::AccountList::_narrow(objAccountList);

		account::AccountListDelegate ald = new account::AccountListDelegate(list);
		account::AccountDelegate ad1 = account::AccountDelegate("MainName1", "Main Surname1", 1);
		account::AccountDelegate ad2 = account::AccountDelegate("MainName2", "Main Surname2", 2);

		ald.addAccount(ad1);
		ald.addAccount(ad2);

		std::cout << "Balance (before): " << ad1.getBalance() << std::endl;
		std::cout << "Number of operations (before): " << ad1.getOperations().size() << std::endl;

		account::OperationDelegate op1 = account::OperationDelegate(1000, utils::Utils::OperationType::ADD, 1);
		account::OperationDelegate op2 = account::OperationDelegate(250, utils::Utils::OperationType::WITHDRAW, 2);

		ad1.addOperation(op1);
		ad1.addOperation(op2);

		account::AccountListDelegate ald2 = account::AccountListDelegate(list);
		std::cout << "Verify that the behavior is the expected: " << ald2.getAccounts().size()  << " == 2" << std::endl;
		//std::assert (ald2.getAccounts().size() == 2);

		std::cout << "Verify that the behavior is the expected: " << ald2.getAccounts().at(0)->balance() << " == 750.0" << std::endl;
		//assert (ald2.getAccounts().at(0)->balance() == 750.0);

		std::cout << "Account ids:" << std::endl;
		for (int id : ald.getAccountIds())
			std::cout << "** accId: " << id << std::endl;

	} catch (...) {
		std::cerr << "An error has occurred " << std::endl;
	}
}



