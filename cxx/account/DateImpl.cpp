/**
 * \file DateImpl.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "DateImpl.h"
#include <sstream>
#include <iomanip>

namespace account {

std::shared_ptr<connection::Connection> DateImpl::_connection = nullptr;

DateImpl::~DateImpl() {
	_connection->deactivateServant(this);
}

DateImpl::DateImpl(::corbaAccount::date_ptr d) {
	DateImpl(d->year(), d->month(), d->day());
}

DateImpl::DateImpl(int year, int month, int day) : _year(year), _month(month), _day(day) {
	std::ostringstream os;
	os << std::setw(2) << std::setfill('0') << this->_year << "/" << this->_month << "/" << this->_day;
	str = os.str();
	_connection = connection::Connection::getInstance();
	_connection->activateServant(this);
}

DateImpl::DateImpl() {
	DateImpl(0, 0, 0);
};

::CORBA::Long DateImpl::day() {
	return this->_day;
}
void DateImpl::day(::CORBA::Long _v) {
	this->_day = _v;
}
::CORBA::Long DateImpl::month() {
	return this->_month;
}
void DateImpl::month(::CORBA::Long _v) {
	this->_month = _v;
}
::CORBA::Long DateImpl::year() {
	return this->_year;
}
void DateImpl::year(::CORBA::Long _v) {
	this->_year = _v;
}

char* DateImpl::toString() {
	return CORBA::string_dup(str.c_str());
};

} /* namespace account */
