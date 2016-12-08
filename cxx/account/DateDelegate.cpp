/**
 * \file DateDelegate.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "DateDelegate.h"

namespace account {

DateDelegate::DateDelegate() {
	_instance = new DateImpl();

}

DateDelegate::~DateDelegate() {
	delete _instance;
}

DateDelegate::DateDelegate(corbaAccount::date_ptr d) {
	_instance = new DateImpl(d.year(), d.month(), d.day());
}

} /* namespace account */
