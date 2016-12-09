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
	DateDelegate(bool publish = true);
	DateDelegate(corbaAccount::date_ptr d);
	virtual ~DateDelegate();
	DateDelegate(int year, int month, int day);
	DateDelegate(int year, int month, int day, bool publish);
	std::string toString();
	int getYear();
	int getMonth();
	int getDay();
	corbaAccount::date_ptr getCorbaInstance();
};

} /* namespace account */

#endif /* DATEDELEGATE_H_ */
