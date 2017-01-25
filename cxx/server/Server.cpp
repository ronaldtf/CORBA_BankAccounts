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
	// Create an account list (it implicitly publishes in the naming service)
	std::shared_ptr<account::AccountListDelegate> ald = std::shared_ptr<account::AccountListDelegate>(new account::AccountListDelegate);
	std::shared_ptr<connection::Connection> connection = nullptr;
	try {
		// Start the server
		connection = connection::Connection::getInstance();
		connection->runServer();
	} catch (std::exception& e) {
		std::cerr << "Error when starting server: " << std::string(e.what()) << std::endl;;
	}

	// In case an exception has occurred, ensure that the connection is closed
	if (connection != nullptr)
		connection->close();

	return 0;
}
