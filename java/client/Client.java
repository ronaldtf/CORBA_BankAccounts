package client;

import org.omg.CORBA.Object;

import account.AccountDelegate;
import account.AccountListDelegate;
import account.OperationDelegate;
import account.OperationDelegate.OperationType;
import connection.Connection;
import corbaAccount.AccountList;
import corbaAccount.AccountListHelper;

public class Client {
	public static void main(String args[]) {
		try {
			Object objAccountList = Connection.getInstance().getClientObject("myContext", "AccountList", "AccountList");
			AccountList list = AccountListHelper.narrow(objAccountList);
			
			AccountListDelegate ald = new AccountListDelegate(list);
			AccountDelegate ad1 = new AccountDelegate("MainName1", "Main Surname1", 1);
			AccountDelegate ad2 = new AccountDelegate("MainName2", "Main Surname2", 2);
			
			ald.addAccount(ad1);
			ald.addAccount(ad2);
			
			System.out.println("Balance (before): " + ad1.getBalance());
			System.out.println("Number of operations (before): " + ad1.getOperations().size());
			
			OperationDelegate op1 = new OperationDelegate(1000, OperationType.ADD, 1);
			OperationDelegate op2 = new OperationDelegate(250, OperationType.WITHDRAW, 2);
	
			ad1.addOperation(op1);
			ad1.addOperation(op2);
			
			AccountListDelegate ald2 = new AccountListDelegate(list);
			System.out.println("Verify that the behavior is the expected: " + ald2.getAccounts().size() + " == 2");
			assert (ald2.getAccounts().size() == 2);

			System.out.println("Verify that the behavior is the expected: " + ald2.getAccounts().elementAt(0).balance() + " == 750.0");
			assert (ald2.getAccounts().elementAt(0).balance() == 750.0);
			
			System.out.println("Account ids:");
			for (Integer id : ald.getAccountIds())
				System.out.println("** accId: " + id);
			
		} catch (Exception e) {
			System.err.println("An error has occurred: " + e.getLocalizedMessage());
		}
	}
}
