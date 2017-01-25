package connection;

import java.nio.channels.AlreadyBoundException;
import java.util.Properties;

import org.omg.CORBA.COMM_FAILURE;
import org.omg.CORBA.ORB;
import org.omg.CORBA.Object;
import org.omg.CORBA.SystemException;
import org.omg.CORBA.ORBPackage.InvalidName;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextHelper;
import org.omg.CosNaming.NamingContextPackage.AlreadyBound;
import org.omg.CosNaming.NamingContextPackage.NotFound;
import org.omg.PortableServer.POA;
import org.omg.PortableServer.POAHelper;
import org.omg.PortableServer.POAManager;
import org.omg.PortableServer.Servant;
import org.omg.PortableServer.POAPackage.ServantAlreadyActive;
import org.omg.PortableServer.POAPackage.ServantNotActive;
import org.omg.PortableServer.POAPackage.WrongPolicy;

import utils.Utils;

public class Connection {

	private ORB orb = null;
	private static final String CONF_NAME = "conf/server.cfg";
	private static boolean isReferenced = false;
	private Properties properties;
	private POA poa;
	private static Connection _instance = null;
	
	public static Connection getInstance() throws Exception {
		if (_instance == null) {
			_instance = new Connection();
		}
		return _instance;
	}
	
	private Connection() throws Exception {
		init();
	}
	
	private void init() throws Exception {
		properties = Utils.readProperties(CONF_NAME);
		String args[] = { "-ORBInitRef", "NameService=corbaname::" + 
				properties.getProperty("org.omg.CORBA.ORBInitialHost") + ":" + 
				properties.getProperty("org.omg.CORBA.ORBInitialPort")};
		
		System.out.println("****************** PROPERTIES *******************");
		for (java.lang.Object p : properties.keySet())
			System.out.println("* " + p.toString() + " : " + properties.getProperty(p.toString()));
		System.out.println("*************************************************");
		System.out.println("ARGS: " + args[0] + " " + args[1]);
		System.out.println("*************************************************");
		orb = ORB.init(args, properties);
		
		referenceObject();
		
		POAManager pman = poa.the_POAManager();
		pman.activate();
	}
	
	private void referenceObject() throws InvalidName {
		if (!isReferenced) {
			poa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
			isReferenced = true;
		}
	}
	
	public Object getClientObject(String componentName, String contextName, String objectType) throws Exception {
	      Object objRef = orb.resolve_initial_references("NameService");
	      NamingContext namingContext = NamingContextHelper.narrow(objRef);
	      NameComponent name[] = new NameComponent[] {
	    		  new NameComponent(componentName, contextName),
	    		  new NameComponent(objectType, "Object")
	      };

	      Object object = namingContext.resolve(name);
	      if (object == null) {
	    	  throw new Exception("Reference is null");
	      }
	      return object;
	}
	
	public void bindObjectToName(Object objRef, String componentName, String contextName, String objectType) throws Exception {
		NamingContext namingContext;
		NamingContext subContext;
		try {
			Object object = orb.resolve_initial_references("NameService");
			namingContext = NamingContextHelper.narrow(object);
			if (namingContext == null)
				throw new Exception("A problem occurred when narrowing the naming context");
		} catch (Exception e) {
			throw new Exception("Name service does not exist");
		}
		
		try {
			NameComponent nameComponent[] = new NameComponent[] {
					new NameComponent(componentName, contextName)
			};
			try {
				subContext = namingContext.bind_new_context(nameComponent);
			} catch (NotFound nf) {
				throw new Exception("Cannot bind new context");
			} catch (AlreadyBoundException abe) {
				//	throw new Exception("Context is already bound");
				Object object = namingContext.resolve(nameComponent);
				if ((subContext = NamingContextHelper.narrow(object)) == null)
					throw new Exception("Cannot rebind the naming context");
			}
			NameComponent objectName[] = new NameComponent[] {
					new NameComponent(objectType, "Object")
			};
			try {
				subContext.bind(objectName, objRef);
			} catch (AlreadyBound ab) {
				// throw new Exception("Object already bound to the subcontext");
				subContext.rebind(objectName, objRef);
			}
		} catch (COMM_FAILURE cf) {
			throw new Exception("A problem has occurred when contacting the naming service");
		} catch (SystemException se) {
			throw new Exception("A problem has occurred whe using the naming service");
		}
		System.out.println("Object of type " + objectType + " bound in componentName " + componentName + " and context " + contextName);
	}	
	
	
	public Object activateServant(Servant obj) throws ServantAlreadyActive, WrongPolicy, ServantNotActive {
		poa.activate_object(obj);
		return poa.servant_to_reference(obj);
	}
	
	public void runServer() {
		orb.run();
	}
	
	public void close() {
		if (orb != null) {
			orb.destroy();
		}
	}
}
