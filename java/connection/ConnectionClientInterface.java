package connection;

import org.omg.CORBA.Object;
import org.omg.PortableServer.Servant;
import org.omg.PortableServer.POAPackage.ServantAlreadyActive;
import org.omg.PortableServer.POAPackage.ServantNotActive;
import org.omg.PortableServer.POAPackage.WrongPolicy;

public interface ConnectionClientInterface {
	public Object getClientObject(String componentName, String contextName, String objectType) throws Exception;
	public Object activateServant(Servant obj) throws ServantAlreadyActive, WrongPolicy, ServantNotActive;
	public void bindObjectToName(Object objRef, String componentName, String contextName, String objectType) throws Exception;
}
