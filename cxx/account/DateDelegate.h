/**
 * \file DateDelegate.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef DATEDELEGATE_H_
#define DATEDELEGATE_H_

#include "DateImpl.h"

namespace account {

class DateDelegate {
private:
	DateImpl* _instance;
public:
	DateDelegate();
	DateDelegate(corbaAccount::date_ptr d);
	virtual ~DateDelegate();
};

} /* namespace account */

#endif /* DATEDELEGATE_H_ */
