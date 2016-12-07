/**
 * \file AccountListImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef ACCOUNTLISTIMPL_H_
#define ACCOUNTLISTIMPL_H_

namespace account {

class AccountListImpl: public corbaAccount::AccountList {
public:
	AccountListImpl();
	virtual ~AccountListImpl();
};

} /* namespace account */

#endif /* ACCOUNTLISTIMPL_H_ */
