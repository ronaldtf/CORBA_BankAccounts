/**
 * \file AccountImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef ACCOUNTIMPL_H_
#define ACCOUNTIMPL_H_

#include "../idl/Account.hh"

namespace account {

class AccountImpl : public POA_corbaAccount::Account {
public:
	AccountImpl();
	virtual ~AccountImpl();
};

}

#endif /* ACCOUNTIMPL_H_ */
