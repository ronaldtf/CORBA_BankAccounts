/**
 * @file Connection.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <omniORB4/CORBA.h>
#include <omniORB4/poa.h>
#include <string>
#include <map>
#include <memory>

namespace connection {
class Connection {
private:
	/**
	 * Instance needed to implement the singleton pattern
	 */
	static std::shared_ptr<Connection> _instance;
	/**
	 * Connection configuration file name
	 */
	static const std::string CONF_NAME;

	/**
	 * Indicates whether the reference of the root context of the name service has been obtained
	 */
	static bool isReferenced;

	/**
	 * ORB reference
	 */
	CORBA::ORB_ptr orb;

	/**
	 * POA reference
	 */
	PortableServer::POA_var poa;

	/**
	 * Connection configuration properties
	 */
	std::map<std::string, std::string> properties;

	/**
	 * Class constructor
	 */
	Connection();

	/**
	 * Initialize the attributes of the instance
	 */
	void init();

	/**
	 * Obtain the reference of the root context of the name service
	 */
	void referenceObject();

public:
	/**
	 * Get an instance of the class - Singleton pattern
	 * @return A reference to the connection
	 */
	static std::shared_ptr<Connection> getInstance();

	/**
	 * Close the connection
	 */
	void close();

	/**
	 * Resolve the CORBA naming service and get the referenced object
	 * @param[in] contextName	Name of the context
	 * @param[in] componentName	Name of the component
	 * @param[in] objectType	Type of object
	 * @return Referenced object (published in the CORBA naming service)
	 */
	CORBA::Object_ptr getClientObject(std::string contextName, std::string componentName, std::string objectType);

	/**
	 * Publish the object in the CORBA naming service
	 * @param[in] objref		Referenced object (published in the CORBA naming service)
	 * @param[in] contextName	Name of the context
	 * @param[in] componentName	Name of the component
	 * @param[in] objectType	Type of object
	 */
	void bindObjectToName(CORBA::Object_ptr objref, std::string contextName, std::string componentName, std::string objectType);

	/**
	 * Activate CORBA object
	 * @param[in] obj	CORBA object to activate
	 * @return	Activated object
	 */
	CORBA::Object_ptr activateServant(PortableServer::ServantBase* obj);

	/**
	 * Deactivate CORBA object
	 * @param[in] obj	CORBA object to deactivate
	 */
	void deactivateServant(PortableServer::ServantBase* obj);

	/**
	 * Starts a server to receive incoming CORBA requests
	 */
	void runServer();
};
};
#endif /* CONNECTION_H_ */
