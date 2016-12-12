/**
 * \file DateDelegate.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "DateDelegate.h"
#include <chrono>
#include <time.h>

namespace account {

DateDelegate::DateDelegate(bool publish) {
	_instance = new DateImpl;
	if (publish) {
		std::string time;
	  std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::now();
	  time_t t = std::chrono::system_clock::to_time_t(timepoint);
	  connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", std::string("Date") + std::string(_instance->toString()) + "_" + time, "Date");
	}

}

DateDelegate::~DateDelegate() {
	delete _instance;
}

DateDelegate::DateDelegate(corbaAccount::date_ptr d) {
	_instance = new DateImpl(d->year(), d->month(), d->day());
}

DateDelegate::DateDelegate(int year, int month, int day, bool publish) {
	_instance = new DateImpl(year,  month,  day);
	if (publish)
		connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "Date"+ std::string(_instance->toString()), "Date");
}

std::string DateDelegate::toString() {
	return _instance->toString();
}

int DateDelegate::getYear() {
	return _instance->year();
}

int DateDelegate::getMonth() {
	return _instance->month();
}

int DateDelegate::getDay() {
	return _instance->day();
}

corbaAccount::date_ptr DateDelegate::getCorbaInstance() {
	return _instance->_this();
}

} /* namespace account */
