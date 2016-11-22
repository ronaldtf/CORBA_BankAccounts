package connection;

import org.omg.CORBA.Object;

public interface ConnectionClientInterface {
	public Object getClientObject(String componentName, String contextName, String objectType) throws Exception;
}
