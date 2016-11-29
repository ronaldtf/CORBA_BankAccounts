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
			Connection connection = Connection.getInstance();
			Object objAccountList = connection.getClientObject("myContext", "AccountList0", "AccountList");
			AccountList list = AccountListHelper.narrow(objAccountList);
			
			AccountListDelegate ald = new AccountListDelegate(list);
			AccountDelegate ad1 = new AccountDelegate("MainName1", "Main Surname1");
			AccountDelegate ad2 = new AccountDelegate("MainName2", "Main Surname2");
			connection.bindObjectToName(ad1.getCorbaInstance(), "myContext", "Account1", "Account");
			connection.bindObjectToName(ad1.getCorbaInstance(), "myContext", "Account2", "Account");
			
			ald.addAccount(ad1.getCorbaInstance());
			ald.addAccount(ad2.getCorbaInstance());
			
			System.out.println("Balance (before): " + ad1.getBalance());
			System.out.println("Number of operations (before): " + ad1.getOperations().size());
			
			OperationDelegate op1 = new OperationDelegate(1000, OperationType.ADD);
			OperationDelegate op2 = new OperationDelegate(250, OperationType.WITHDRAW);
			connection.bindObjectToName(op1.getCorbaInstance(), "myContext", "Operation1", "Operation");
			connection.bindObjectToName(op2.getCorbaInstance(), "myContext", "Operation2", "Operation");
	
			ad1.addOperation(op1.getCorbaInstance());
			ad1.addOperation(op2.getCorbaInstance());
			
			AccountListDelegate ald2 = new AccountListDelegate(list);
			System.out.println("Verify that the behavior is the expected: " + ald2.getAccounts().size() + " == 2");
			assert (ald2.getAccounts().size() == 2);

			System.out.println("Verify that the behavior is the expected: " + ald2.getAccounts().elementAt(0).balance() + " == 750.0");
			assert (ald2.getAccounts().elementAt(0).balance() == 750.0);
			
		} catch (Exception e) {
			System.err.println("An error has occurred: " + e.getLocalizedMessage());
		}
	}
}
