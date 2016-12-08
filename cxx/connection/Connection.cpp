/**
 * \file Connection.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

/**
 * \file Connection.hpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include <iostream>
#include "Connection.h"
#include "../utils/Utils.h"

namespace connection {

Connection* Connection::_instance = nullptr;
const std::string Connection::CONF_NAME = "conf/server.cfg";
bool Connection::isReferenced = false;

Connection::Connection() : orb(nullptr), poa(nullptr), properties() {
	init();
}

Connection::~Connection() {
	if (_instance != nullptr)
		delete _instance;
}

void Connection::init() {
	std::map<std::string, std::string> properties;
	utils::Utils::parseFile(CONF_NAME, properties);

	char *key = const_cast<char*>(std::string("-ORBInitRef").c_str());
	char *value = const_cast<char*>(std::string("NameService=corbaname::" + properties.at("org.omg.CORBA.ORBInitialHost") + ":" + properties.at("org.omg.CORBA.ORBInitialPort")).c_str());
	char* args[] = { key, value};

	std::cout << "****************** PROPERTIES *******************" << std::endl;
	for (std::map<std::string, std::string>::iterator it = properties.begin(); it != properties.end(); ++it) {
		std::cout << "* " << it->first << " : " << it->second << std::endl;
	}
	std::cout << "*************************************************" << std::endl;
	std::cout << "ARGS: " << args[0] << " " << args[1] << std::endl;
	std::cout << "*************************************************" << std::endl;
	char* arr[properties.size()][2];
	utils::Utils::convertMapToArray(properties, (char****)arr);
	int argc=2;
	orb = CORBA::ORB_init(argc, (char**)args, "", (const char*(*)[2])arr);

	referenceObject();

	PortableServer::POAManager_var poaManager = poa->the_POAManager();
	poaManager->activate();


}

void Connection::referenceObject() {
	if (!isReferenced) {
		CORBA::Object_var poaObject = orb->resolve_initial_references("RootPOA");
		poa = PortableServer::POA::_narrow(poaObject.in());
		isReferenced = true;
	}
}

Connection* Connection::getInstance() {
	if (_instance == nullptr)
		_instance = new Connection();
	return _instance;
}

CORBA::Object_ptr Connection::getClientObject(std::string componentName, std::string contextName, std::string objectType) {
	CosNaming::NamingContext_var rootContext;

	try {
		CORBA::Object_var obj;
		obj = orb->resolve_initial_references(componentName.c_str());

		rootContext = CosNaming::NamingContext::_narrow(obj);
		if (CORBA::is_nil(rootContext)) {
			std::cerr << "Error getting the root context" << std::endl;
			return CORBA::Object::_nil();
		}
	} catch (CORBA::ORB::InvalidName& ex) {
		std::cerr << "Service does not exist" << std::endl;
		return CORBA::Object::_nil();
	}

	CosNaming::Name name;
	name.length(2);
	name[0].id = "my_context";
	name[0].kind = contextName.c_str();
	name[1].id = objectType.c_str();
	name[1].kind = "Object";

	try {
		return rootContext->resolve(name);
	} catch (CosNaming::NamingContext::NotFound& e) {
		std::cerr << "Context not found" << std::endl;
	} catch (CORBA::COMM_FAILURE& e) {
		std::cerr << "Error contacting to the naming service" << std::endl;
	} catch (CORBA::SystemException& e) {
		std::cerr << "A system exception has occurred" << std::endl;
	}

	return CORBA::Object::_nil();
}

void Connection::bindObjectToName(CORBA::Object_ptr objref, std::string componentName, std::string contextName, std::string objectType) {
	CosNaming::NamingContext_var rootContext;
	try {
		CORBA::Object_var obj = orb->resolve_initial_references("NameService");

		rootContext = CosNaming::NamingContext::_narrow(obj);
		if (CORBA::is_nil(rootContext)) {
			std::cerr << "Failed to narrow the root naming context." << std::endl;
			throw std::exception();
		}
	} catch (CORBA::ORB::InvalidName& ex) {
		std::cerr << "Service required is not valid" << std::endl;
		throw ex;
	}

	try {
		CosNaming::Name context;
		context.length(1);
		context[0].id = "my_context";
		context[0].kind = contextName.c_str();

		CosNaming::NamingContext_var testContext;
		try {
			testContext = rootContext->bind_new_context(context);
		} catch (CosNaming::NamingContext::AlreadyBound& ex) {
			CORBA::Object_var obj;
			obj = rootContext->resolve(context);
			testContext = CosNaming::NamingContext::_narrow(obj);
			if (CORBA::is_nil(testContext)) {
				std::cerr << "Failed to narrow naming context." << std::endl;
				throw std::exception();
			}
		}

		CosNaming::Name objectName;
		objectName.length(1);
		objectName[0].id = (const char*) "Clock";
		objectName[0].kind = (const char*) "Object";

		try {
			testContext->bind(objectName, objref);
		} catch (CosNaming::NamingContext::AlreadyBound& ex) {
			testContext->rebind(objectName, objref);
		}

	} catch (CORBA::COMM_FAILURE& ex) {
		std::cerr << "Unable to access to the naming service" << std::endl;
		throw ex;
	} catch (CORBA::SystemException&) {
		std::cerr << "A system exception has occurred" << std::endl;
		throw std::exception();
	}
}

CORBA::Object_ptr Connection::activateServant(PortableServer::ServantBase* obj) {
	poa->activate_object(obj);
	return poa->servant_to_reference(obj);

}

void Connection::runServer() {
	orb->run();
}
};
