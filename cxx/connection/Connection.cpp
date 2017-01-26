/**
 * @file Connection.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "../utils/Utils.h"

#include "Connection.h"

#include <iostream>

namespace connection {

std::shared_ptr<Connection> Connection::_instance = nullptr;
const std::string Connection::CONF_NAME = "conf/server.cfg";
bool Connection::isReferenced = false;

Connection::Connection() : orb(nullptr), poa(nullptr), properties() {
	init();
}

void Connection::close() {
	if (orb != NULL) {
		try {
			orb->destroy();
		} catch (...) {}
	}
}


void Connection::init() {
	// Get the properties
	std::map<std::string, std::string> properties = std::map<std::string, std::string>();
	utils::Utils::parseFile(CONF_NAME, properties);

	char* key = const_cast<char*>(std::string("-ORBInitRef").c_str());
	std::string valueStr = std::string("NameService=corbaname::" + properties.at("org.omg.CORBA.ORBInitialHost") + ":" + properties.at("org.omg.CORBA.ORBInitialPort")).c_str();
	char *value = (char*)valueStr.c_str();
	char* args[] = { key, value};

	std::cout << "****************** PROPERTIES *******************" << std::endl;
	for (std::map<std::string, std::string>::iterator it = properties.begin(); it != properties.end(); ++it) {
		std::cout << "* " << it->first << " : " << it->second << std::endl;
	}
	std::cout << "*************************************************" << std::endl;
	std::cout << "ARGS: " << args[0] << " " << args[1] << std::endl;
	std::cout << "*************************************************" << std::endl;

	// Initialize the ORB
	int argc=2;
	orb = CORBA::ORB_init(argc, args);

	// Obtain the root context of the name service
	referenceObject();

	// Initialize and activate the POA Manager
	PortableServer::POAManager_var pman = poa->the_POAManager();
	pman->activate();

}

void Connection::referenceObject() {
	if (!isReferenced) {
		// Obtain the root context of the name service
		poa = PortableServer::POA::_narrow(orb->resolve_initial_references("RootPOA"));
		isReferenced = true;
	}
}

std::shared_ptr<Connection> Connection::getInstance() {
	// Singleton implementation
	if (_instance == nullptr)
		_instance = std::shared_ptr<Connection>(new Connection());
	return _instance;
}

CORBA::Object_ptr Connection::getClientObject(std::string contextName, std::string componentName, std::string objectType) {
	CosNaming::NamingContext_var rootContext;

	// Get the root context
	try {
		CORBA::Object_var obj;
		obj = orb->resolve_initial_references("NameService");

		rootContext = CosNaming::NamingContext::_narrow(obj);
		if (CORBA::is_nil(rootContext)) {
			std::cerr << "Error getting the root context" << std::endl;
			return CORBA::Object::_nil();
		}
	} catch (CORBA::ORB::InvalidName& ex) {
		std::cerr << "Service does not exist" << std::endl;
		return CORBA::Object::_nil();
	}

	// Get the object given the rootContext, the context name and the componentName (object reference name) and type of object
	CosNaming::Name name;
	name.length(2);
	name[0].id = componentName.c_str();
	name[0].kind = contextName.c_str();
	name[1].id = objectType.c_str();
	name[1].kind = "Object";

	// Return the reference in case it was found or show an otherwise
	try {
		return rootContext->resolve(name);
	} catch (CosNaming::NamingContext::NotFound& e) {
		std::cerr << "Context not found" << std::endl;
	} catch (CORBA::COMM_FAILURE& e) {
		std::cerr << "Error contacting to the naming service" << std::endl;
	} catch (CORBA::SystemException& e) {
		std::cerr << "A system exception has occurred" << std::endl;
	}

	// Return a null reference in case it is not found
	return CORBA::Object::_nil();
}

void Connection::bindObjectToName(CORBA::Object_ptr objref, std::string contextName, std::string componentName, std::string objectType) {
	CosNaming::NamingContext_var namingContext;
	CosNaming::NamingContext_var subContext;

	// Get the root context
	try {
		CORBA::Object_var obj = orb->resolve_initial_references("NameService");
		namingContext = CosNaming::NamingContext::_narrow(obj);

		if (CORBA::is_nil(namingContext)) {
			std::cerr << "Failed to narrow the root naming context." << std::endl;
			throw std::exception();
		}
	} catch (CORBA::ORB::InvalidName& ex) {
		std::cerr << "Service required is not valid" << std::endl;
		throw std::exception();
	}

	// Sets the context and put there the object of objectType providing a componentName
	try {
		CosNaming::Name nameComponent;
		nameComponent.length(1);
		nameComponent[0].id = componentName.c_str();
		nameComponent[0].kind = contextName.c_str();

		try {
			// Bind the context
			subContext = namingContext->bind_new_context(nameComponent);
		} catch (CosNaming::NamingContext::AlreadyBound& ex) {
			CORBA::Object_var obj;
			obj = namingContext->resolve(nameComponent);
			subContext = CosNaming::NamingContext::_narrow(obj);
			if (CORBA::is_nil(subContext)) {
				std::cerr << "Failed to narrow naming context." << std::endl;
				throw std::exception();
			}
		}

		// Set the object name and type
		CosNaming::Name objectName;
		objectName.length(1);
		objectName[0].id = (const char*) objectType.c_str();
		objectName[0].kind = (const char*) "Object";

		try {
			// Link the object with the context and the object name and type
			subContext->bind(objectName, objref);
		} catch (CosNaming::NamingContext::AlreadyBound& ex) {
			subContext->rebind(objectName, objref);
		}

	} catch (CORBA::COMM_FAILURE& ex) {
		std::cerr << "Unable to access to the naming service" << std::endl;
		throw std::exception();
	} catch (CORBA::SystemException&) {
		std::cerr << "A system exception has occurred" << std::endl;
		throw std::exception();
	}
}

CORBA::Object_ptr Connection::activateServant(PortableServer::ServantBase* obj) {
	// Activate the CORBA object
	poa->activate_object(obj);
	return poa->servant_to_reference(obj);
}

void Connection::deactivateServant(PortableServer::ServantBase* obj) {
	// Deactivate the CORBA object
	poa->deactivate_object(*poa->servant_to_id(obj));
}

void Connection::runServer() {
	// Start a CORBA server to receive incoming requests
	orb->run();
}
};
