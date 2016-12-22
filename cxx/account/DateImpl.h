/**
 * \file DateImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef DATEIMPL_H_
#define DATEIMPL_H_

#include "../../idl/Account.hh"
#include "../connection/Connection.h"
#include <string>

namespace account {

class DateImpl : public POA_corbaAccount::date {
private:
	int _year;
	int _month;
	int _day;
	static connection::Connection* _connection;
private:
	std::string str;
public:
	DateImpl();
	DateImpl(::corbaAccount::date_ptr d);
	DateImpl(int year, int month, int day);
	~DateImpl();
    ::CORBA::Long day();
    void day(::CORBA::Long _v);
    ::CORBA::Long month();
    void month(::CORBA::Long _v);
    ::CORBA::Long year();
    void year(::CORBA::Long _v);
	char* toString();
};

} /* namespace account */

#endif /* DATEIMPL_H_ */
