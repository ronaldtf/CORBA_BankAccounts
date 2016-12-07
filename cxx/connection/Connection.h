/**
 * \file Connection.hpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <omniORB4/CORBA.h>
#include <omniORB4/poa.h>
#include <string>
#include <map>

namespace connection {
class Connection {
private:
	static Connection* _instance;
	static const std::string CONF_NAME;
	static bool isReferenced;
	PortableServer::POA_var poa;

	CORBA::ORB_ptr orb;
	std::map<std::string, std::string> properties;

	Connection();
	~Connection();
	void init();
	void referenceObject();

public:
	static Connection* getInstance();
	CORBA::Object_ptr getClientObject(std::string componentName, std::string contextName, std::string objectType);
	void bindObjectToName(CORBA::ORB_ptr orb,
			CORBA::Object_ptr objref, std::string componentName, std::string contextName, std::string objectType);
	CORBA::Object_ptr activateServant(PortableServer::ServantBase* obj);
	void runServer();
};
};
#endif /* CONNECTION_H_ */
