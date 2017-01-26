/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package client;

import org.omg.CORBA.Object;

import corbaAccount.AccountList;
import corbaAccount.AccountListHelper;

import account.AccountDelegate;
import account.AccountListDelegate;
import account.OperationDelegate;
import connection.Connection;
import utils.Utils;

/*
 * In this class I implement an example of how to handle accounts from the client side.
 * In this example, the list of accounts is obtained and two new accounts are added to the list.
 * After that, I verify that the list of accounts is correct.
 */
public class Client {
	public static void main(String args[]) {
		try {
			// Get the accountList
			Object objAccountList = Connection.getInstance().getClientObject("myContext", "AccountList", "AccountList");
			AccountList list = AccountListHelper.narrow(objAccountList);
			
			// Create the accounts. Note that, by default, accounts are published and, therefore, added as
			// objects in the naming service.
			AccountListDelegate ald = new AccountListDelegate(list);
			AccountDelegate ad1 = new AccountDelegate("MainName1", "Main Surname1", 1);
			AccountDelegate ad2 = new AccountDelegate("MainName2", "Main Surname2", 2);
			
			// Add the accounts to the list
			ald.addAccount(ad1);
			ald.addAccount(ad2);
			
			// Verify the initial balance (before performing any operation)
			System.out.println("Balance (before): " + ad1.getBalance());
			System.out.println("Number of operations (before): " + ad1.getOperations().size());
			
			// Perform an operation on each account
			OperationDelegate op1 = new OperationDelegate(1000, Utils.OperationType.ADD, 1);
			OperationDelegate op2 = new OperationDelegate(250, Utils.OperationType.WITHDRAW, 2);
			ad1.addOperation(op1);
			ad1.addOperation(op2);
			
			// Get the recent list
			AccountListDelegate ald2 = new AccountListDelegate(list);
			
			// Verify that the balance in the accounts is the expected
			System.out.println("Verify that the behavior is the expected: " + ald2.getAccounts().size() + " == 2");
			assert (ald2.getAccounts().size() == 2);
			System.out.println("Verify that the behavior is the expected: " + ald2.getAccounts().elementAt(0).balance() + " == 750.0");
			assert (ald2.getAccounts().elementAt(0).balance() == 750.0);
			
			// Verify the account ids
			System.out.println("Account ids:");
			for (Integer id : ald.getAccountIds())
				System.out.println("** accId: " + id);
			
		} catch (Exception e) {
			System.err.println("An error has occurred: " + e.getLocalizedMessage());
		} catch (Throwable t) {
			System.err.println("A generic error has occurred: " + t.getLocalizedMessage());
		}
	}
}
