/**
 * \file DateDelegate.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "DateDelegate.h"

#include "../utils/Utils.h"

#include <chrono>
#include <ctime>

namespace account {

DateDelegate::DateDelegate(bool publish) {
	_instance = std::unique_ptr<DateImpl>(new DateImpl);
	if (publish) {
		std::string time;
		std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::now();
		time_t t = std::chrono::system_clock::to_time_t(timepoint);
		connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", std::string("Date") + std::string(_instance->toString()) + "_" + utils::Utils::convertDate(t), "Date");
	}

}

DateDelegate::DateDelegate(const DateDelegate& dd) {
	_instance = std::unique_ptr<DateImpl>(new DateImpl(dd.getYear(), dd.getMonth(), dd.getDay()));
}

DateDelegate::~DateDelegate() {
}

DateDelegate::DateDelegate(corbaAccount::date_ptr d) {
	_instance = std::unique_ptr<DateImpl>(new DateImpl(d->year(), d->month(), d->day()));
}

DateDelegate::DateDelegate(int year, int month, int day, bool publish) {
	_instance = std::unique_ptr<DateImpl>(new DateImpl(year,  month,  day));
	if (publish)
		connection::Connection::getInstance()->bindObjectToName(_instance->_this(), "myContext", "Date"+ std::string(_instance->toString()), "Date");
}

std::string DateDelegate::toString() const {
	return _instance->toString();
}

int DateDelegate::getYear() const {
	return _instance->year();
}

int DateDelegate::getMonth() const {
	return _instance->month();
}

int DateDelegate::getDay() const {
	return _instance->day();
}

corbaAccount::date_ptr DateDelegate::getCorbaInstance() const {
	return _instance->_this();
}

} /* namespace account */
