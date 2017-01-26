/**
 * @file Client.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "../../idl/Account.hh"
#include "../connection/Connection.h"
#include "../account/AccountDelegate.h"
#include "../account/AccountListDelegate.h"

#include <cassert>
#include <iostream>

/*
 * In this method I implement an example of how to handle accounts from the client side.
 * In this example, the list of accounts is obtained and two new accounts are added to the list.
 * After that, I verify that the list of accounts is correct.
 */
int main() {
	try {
		// Get the accountList
		CORBA::Object_ptr objAccountList = connection::Connection::getInstance()->getClientObject("myContext", "AccountList", "AccountList");
		corbaAccount::AccountList_var list = corbaAccount::AccountList::_narrow(objAccountList);
		// Verify that the list is not null
		if (CORBA::is_nil(list)) {
			std::cerr << "Cannot narrow reference." << std::endl;
			return 1;
		}
		corbaAccount::accountListType* accountList = list->accountsList();

		// Create the accounts. Note that, by default, accounts are published and, therefore, added as
		// objects in the naming service.
		account::AccountListDelegate ald = new account::AccountListDelegate(accountList);
		account::AccountDelegate ad1 = account::AccountDelegate("MainName1", "Main Surname1", 1);
		account::AccountDelegate ad2 = account::AccountDelegate("MainName2", "Main Surname2", 2);

		// Add the accounts to the list
		ald.addAccount(ad1);
		ald.addAccount(ad2);

		// Verify the initial balance (before performing any operation)
		std::cout << "Balance (before): " << ad1.getBalance() << std::endl;
		std::cout << "Number of operations (before): " << ad1.getOperations().size() << std::endl;

		// Perform an operation on each account
		account::OperationDelegate op1 = account::OperationDelegate(1000, utils::Utils::OperationType::ADD, 1);
		account::OperationDelegate op2 = account::OperationDelegate(250, utils::Utils::OperationType::WITHDRAW, 2);
		ad1.addOperation(op1);
		ad1.addOperation(op2);

		// Get the recent list
		accountList = ald.getCorbaInstance()->accountsList();

		// Verify that the balance in the accounts is the expected
		account::AccountListDelegate ald2 = account::AccountListDelegate(accountList);
		std::cout << "Verify that the behavior is the expected: " << ald2.getAccounts().size()  << " == 2" << std::endl;
		assert (ald2.getAccounts().size() == 2);
		std::cout << "Verify that the behavior is the expected: " << ald2.getAccounts().at(0)->balance() << " == 750.0" << std::endl;
		assert (ald2.getAccounts().at(0)->balance() == 750.0);

		// Verify the account ids
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

} // end main
