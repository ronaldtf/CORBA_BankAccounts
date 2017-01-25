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
	std::unique_ptr<DateImpl> _instance;
public:
	DateDelegate(bool publish = true);
	DateDelegate(const DateDelegate& dd);
	DateDelegate(corbaAccount::date_ptr d);
	virtual ~DateDelegate();
	DateDelegate(const int year, const int month, const int day, bool publish = true);
	std::string toString() const;
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	corbaAccount::date_ptr getCorbaInstance() const;
};

} /* namespace account */

#endif /* DATEDELEGATE_H_ */
