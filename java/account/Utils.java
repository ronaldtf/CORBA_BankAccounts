package account;

import account.OperationDelegate.OperationType;
import corbaAccount.operationType;

public class Utils {

	public static operationType convertType(OperationType opType) {
		switch (opType) {
		case ADD:
			return operationType.ADD;
		case WITHDRAW:
			return operationType.WITHDRAW;
		default:
			throw new RuntimeException("Type not valid");
		}
	}
	
	public static OperationType convertType(operationType opType) {
		if (opType == operationType.ADD)
			return OperationType.ADD;
		else if (opType == operationType.WITHDRAW)
			return OperationType.WITHDRAW;
		throw new RuntimeException("Type not implemented");
	}
}
