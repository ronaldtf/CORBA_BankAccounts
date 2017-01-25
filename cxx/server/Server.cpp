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
	std::shared_ptr<connection::Connection> connection = nullptr;
	try {
		connection = connection::Connection::getInstance();
		connection->runServer();
	} catch (std::exception& e) {
		std::cerr << "Error when starting server: " << std::string(e.what()) << std::endl;;
	}

	if (connection != nullptr)
		connection->close();

	return 0;
}
