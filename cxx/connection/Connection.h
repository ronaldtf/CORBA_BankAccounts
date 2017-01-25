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
#include <memory>

namespace connection {
class Connection {
private:
	static std::shared_ptr<Connection> _instance;
	static const std::string CONF_NAME;
	static bool isReferenced;

	CORBA::ORB_ptr orb;
	PortableServer::POA_var poa;

	std::map<std::string, std::string> properties;

	Connection();
	void init();
	void referenceObject();

public:
	static std::shared_ptr<Connection> getInstance();
	void close();
	CORBA::Object_ptr getClientObject(std::string componentName, std::string contextName, std::string objectType);
	void bindObjectToName(CORBA::Object_ptr objref, std::string componentName, std::string contextName, std::string objectType);
	CORBA::Object_ptr activateServant(PortableServer::ServantBase* obj);
	void deactivateServant(PortableServer::ServantBase* obj);
	void runServer();
};
};
#endif /* CONNECTION_H_ */
