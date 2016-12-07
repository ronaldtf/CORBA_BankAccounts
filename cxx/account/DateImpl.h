/**
 * \file DateImpl.h
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#ifndef DATEIMPL_H_
#define DATEIMPL_H_

namespace account {

class DateImpl: public corbaAccount::date {
public:
	DateImpl();
	virtual ~DateImpl();
};

} /* namespace account */

#endif /* DATEIMPL_H_ */
