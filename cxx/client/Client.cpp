/**
 * \file Client.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include <iostream>
#include "../../idl/Account.hh"
#include "../connection/Connection.h"
#include "../account/AccountDelegate.h"
#include "../account/AccountListDelegate.h"
#include <cassert>

int main() {
	try {
		CORBA::Object_ptr objAccountList = connection::Connection::getInstance()->getClientObject("myContext", "AccountList", "AccountList");
		corbaAccount::AccountList_var list = corbaAccount::AccountList::_narrow(objAccountList);
		if (CORBA::is_nil(list)) {
			std::cerr << "Cannot narrow reference." << std::endl;
			return 1;
		}

		corbaAccount::accountListType* accountList = list->accountsList();

		account::AccountListDelegate ald = new account::AccountListDelegate(accountList);
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

		// Get the recent list
		accountList = ald.getCorbaInstance()->accountsList();

		account::AccountListDelegate ald2 = account::AccountListDelegate(accountList);
		std::cout << "Verify that the behavior is the expected: " << ald2.getAccounts().size()  << " == 2" << std::endl;
		assert (ald2.getAccounts().size() == 2);

		std::cout << "Verify that the behavior is the expected: " << ald2.getAccounts().at(0)->balance() << " == 750.0" << std::endl;
		assert (ald2.getAccounts().at(0)->balance() == 750.0);

		std::cout << "Account ids:" << std::endl;
		for (int id : ald.getAccountIds()) {
			std::cout << "** accId: " << id << std::endl;
		}

	} catch (std::exception& e) {
		std::cerr << "An error has occurred " << e.what() << std::endl;
	} catch (::CORBA::TRANSIENT& e) {
		std::cerr << "A transient exception has occurred: " << e.NP_minorString() << std::endl;
	} catch (::CORBA::COMM_FAILURE& e) {
		std::cerr << "A comm failure has occurred: " << e.NP_minorString() << std::endl;
	}
}



