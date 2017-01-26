/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
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

	/**
	 * ORB reference
	 */
	private ORB orb = null;
	
	/**
	 * Connection configuration file name
	 */
	private static final String CONF_NAME = "conf/server.cfg";
	
	/**
	 * Indicates whether the reference of the root context of the name service has been obtained
	 */
	private static boolean isReferenced = false;
	
	/**
	 * Connection configuration properties
	 */
	private Properties properties;
	
	/**
	 * POA reference
	 */
	private POA poa;
	
	/**
	 * Instance needed to implement the singleton pattern
	 */
	private static Connection _instance = null;
	
	/**
	 * Get an instance of the class - Singleton pattern
	 * @return A reference to the connection
	 * @throws Exception Throws an exception in case of any problem
	 */
	public static Connection getInstance() throws Exception {
		// Singleton implementation
		if (_instance == null) {
			_instance = new Connection();
		}
		return _instance;
	}
	
	/**
	 * Class constructor
	 * @throws Exception Throws an exception in case of any problem
	 */
	private Connection() throws Exception {
		init();
	}
	
	/**
	 * Initialize the attributes of the instance
	 * @throws Exception Throws an exception in case of any problem
	 */
	private void init() throws Exception {
		// Get the properties
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
		
		// Intialize the ORB
		orb = ORB.init(args, properties);
		
		// Obtain the root context of the name service
		referenceObject();
		
		// Initialize and activate the POA Manager
		POAManager pman = poa.the_POAManager();
		pman.activate();
	}
	
	/**
	 * Obtain the reference of the root context of the name service
	 * @throws InvalidName	Throws this exception in case the name is not valid
	 */
	private void referenceObject() throws InvalidName {
		if (!isReferenced) {
			// Obtain the root context of the name service
			poa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
			isReferenced = true;
		}
	}
	
	/**
	 * Resolve the CORBA naming service and get the referenced object
	 * @param contextName	Name of the context
	 * @param componentName	Name of the component
	 * @param objectType	Type of object
	 * @return Referenced object (published in the CORBA naming service)
	 * @throws Exception Throw an exception in case a generic problem occurs
	 */
	public Object getClientObject(String contextName, String componentName, String objectType) throws Exception {
		// Get the root context
	    Object objRef = orb.resolve_initial_references("NameService");
	    NamingContext namingContext = NamingContextHelper.narrow(objRef);
	    
	    // Get the object given the rootContext, the context name and the componentName (object reference name) and type of object
	    NameComponent name[] = new NameComponent[] {
	      new NameComponent(componentName, contextName),
	      new NameComponent(objectType, "Object")
	    };
	    
	    // Return the reference in case it was found or throw an exception otherwise
	    Object object = namingContext.resolve(name);
	    if (object == null) {
	      throw new Exception("Reference is null");
	    }
	    return object;
	}
	
	/**
	 * Publish the object in the CORBA naming service
	 * @param objRef		Referenced object (published in the CORBA naming service)
	 * @param contextName	Name of the context
	 * @param componentName	Name of the component
	 * @param objectType	Type of object
	 * @throws Exception Throw an exception in case a generic problem occurs
	 */
	public void bindObjectToName(Object objRef, String contextName, String componentName, String objectType) throws Exception {
		NamingContext namingContext;
		NamingContext subContext;
		
		// Get the root context
		try {
			Object object = orb.resolve_initial_references("NameService");
			namingContext = NamingContextHelper.narrow(object);
			if (namingContext == null)
				throw new Exception("A problem occurred when narrowing the naming context");
		} catch (Exception e) {
			throw new Exception("Name service does not exist");
		}
		
		// Sets the context and put there the object of objectType providing a componentName
		try {
			NameComponent nameComponent[] = new NameComponent[] {
					new NameComponent(componentName, contextName)
			};
			try {
				// Bind the context
				subContext = namingContext.bind_new_context(nameComponent);
			} catch (NotFound nf) {
				throw new Exception("Cannot bind new context");
			} catch (AlreadyBoundException abe) {
				//	throw new Exception("Context is already bound");
				Object object = namingContext.resolve(nameComponent);
				if ((subContext = NamingContextHelper.narrow(object)) == null)
					throw new Exception("Cannot rebind the naming context");
			}
			
			// Set the object name and type
			NameComponent objectName[] = new NameComponent[] {
					new NameComponent(objectType, "Object")
			};
			try {
				// Link the object with the context and the object name and type
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
	
	/**
	 * Activate CORBA object
	 * @param obj	CORBA object to activate
	 * @return	Activated object
	 * @throws Exception Throw an exception in case a generic problem occurs
	 */
	public Object activateServant(Servant obj) throws Exception {
		// Activate the CORBA object
		poa.activate_object(obj);
		return poa.servant_to_reference(obj);
	}
	
	/**
	 * Starts a server to receive incoming CORBA requests
	 */
	public void runServer() {
		orb.run();
	}
	
	/**
	 * Close the connection
	 */
	public void close() {
		if (orb != null) {
			orb.destroy();
		}
	}
}
