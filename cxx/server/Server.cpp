/**
 * \file Server.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "../account/AccountListDelegate.h"
#include "../connection/Connection.h"
#include <iostream>
#include <memory>

int main() {
	std::shared_ptr<account::AccountListDelegate> ald = std::shared_ptr<account::AccountListDelegate>(new account::AccountListDelegate);
	try {
		connection::Connection* connection = connection::Connection::getInstance();
		connection->runServer();
	} catch (std::exception& e) {
		std::cerr << "Error when starting server: " << std::string(e.what()) << std::endl;;
	}

	return 0;
}
