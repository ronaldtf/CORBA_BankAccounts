/**
 * @file DateDelegate.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef DATEDELEGATE_H_
#define DATEDELEGATE_H_

#include "DateImpl.h"

namespace account {

/**
 * This class implements the delegate for date.
 * @see DateImpl.h
 */
class DateDelegate {
private:
	/**
	 * This is an instance of an DateImpl, in which the class delegates
	 */
	std::unique_ptr<DateImpl> _instance;
public:
	/**
	 * Class constructor
	 * @param[in] publish	Indicates whether the date needs to be added to the corba naming service
	 */
	DateDelegate(bool publish = true);

	/**
	 * Copy constructor
	 * @param[in] dd	Date to be copied
	 */
	DateDelegate(const DateDelegate& dd);

	/**
	 * Class constructor
	 * @param[in] d		Date to use for initialization
	 */
	DateDelegate(corbaAccount::date_ptr d);

	/**
	 * Class destructor
	 */
	virtual ~DateDelegate();

	/**
	 * @param[in] year	Year
	 * @param[in] month	Month
	 * @param[in] day	Day
	 * @param[in] publish	Indicates whether the date needs to be added to the corba naming service
	 */
	DateDelegate(const int year, const int month, const int day, bool publish = true);

	/**
	 * Get the date in String format
	 * @return Date in String format
	 */
	std::string toString() const;

	/**
	 * Get the year
	 * @return Year
	 */
	int getYear() const;

	/**
	 * Get the month
	 * @return Month
	 */
	int getMonth() const;

	/**
	 * Get the day
	 * @return Day
	 */
	int getDay() const;

	/**
	 * Get the CORBA instance of the date
	 * @return date CORBA instance
	 */
	corbaAccount::date_ptr getCorbaInstance() const;
};

} /* namespace account */

#endif /* DATEDELEGATE_H_ */
