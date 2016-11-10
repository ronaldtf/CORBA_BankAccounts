/**
 * \file AccountImpl.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include "../idl/Account.hh"
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>

class dateImpl : public POA_corbaAccount::date {
private:
	int _year;
	int _month;
	int _day;
private:
	std::string str;
public:
	dateImpl() : _year(0), _month(0), _day(0) {};
	dateImpl(int year, int month, int day) : _year(year), _month(month), _day(day) {
		std::ostringstream os;
		os << std::setw(2) << std::setfill('0') << this->_year << "/" << this->_month << "/" << this->_day;
		str = os.str();
	}

    ::CORBA::Long day() {
    	return this->_day;
    }
    void day(::CORBA::Long _v) {
    	this->_day = _v;
    }
    ::CORBA::Long month() {
    	return this->_month;
    }
    void month(::CORBA::Long _v) {
    	this->_month = _v;
    }
    ::CORBA::Long year() {
    	return this->_year;
    }
    void year(::CORBA::Long _v) {
    	this->_year = _v;
    }

	char* toString() {
		return const_cast<char*>(str.c_str());
	};
};

class OperationImpl : public POA_corbaAccount::Operation {
private:
	corbaAccount::operationType _type;
	float _amount;
public:
	OperationImpl(corbaAccount::operationType type, const float amount) : _type(type), _amount(amount) {
	}

    corbaAccount::operationType type() {
    	return _type;
    }

    void type(::corbaAccount::operationType _v) {
    	this->_type = _v;
    }

    ::CORBA::Float amount() {
    	return _amount;
    }

    void amount(::CORBA::Float _v) {
    	this->_amount = _v;
    }

};

class AccountImpl : public POA_corbaAccount::Account {
private:
	unsigned int _accountId;
	std::string _details;
	dateImpl _dateAccountCreated;
	float _balance;
	std::vector<OperationImpl> _accountOperations;

public:
	AccountImpl(std::string name, std::string surname, float balance = 0) : _details(name + " " + surname), _balance(balance),
			_accountOperations() {
		static unsigned int id;
		_accountId = ++id;

		std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::now();
		time_t t = std::chrono::system_clock::to_time_t(timepoint);
		struct tm* tmp = localtime(&t);
		_dateAccountCreated = dateImpl(tmp->tm_year, tmp->tm_mon, tmp->tm_mday);
	}

    float balance() {
    	return _balance;
    };

    corbaAccount::date_ptr dateAccountCreated() {
    	corbaAccount::date_ptr d = corbaAccount::date_ptr();
    	d->year(_dateAccountCreated.year());
    	d->month(_dateAccountCreated.month());
    	d->day(_dateAccountCreated.day());
    	return d;
    }

    char* details() {
    	return const_cast<char*>(_details.c_str());
    };

    ::CORBA::Long accountId() {
    	return _accountId;
    };

    void addOperation(::corbaAccount::Operation_ptr op) {
    	_accountOperations.push_back(OperationImpl(op->type(), op->amount()));
    };

    corbaAccount::accountOperationsType* accountOperations() {
    	corbaAccount::accountOperationsType* ops = new corbaAccount::accountOperationsType;
    	ops->length(_accountOperations.size());
    	unsigned int pos = 0;
    	for (OperationImpl op : _accountOperations) {
    		(*ops)[pos]->type(op.type());
    		(*ops)[pos++]->amount(op.amount());
    	}
    	return ops;
    };

    void accountOperations(const ::corbaAccount::accountOperationsType& _v) {
    	_accountOperations.clear();
    	size_t len = _v.length();
    	for (size_t pos=0; pos<len; ++pos) {
    		_accountOperations.push_back(OperationImpl(_v[pos]->type(), _v[pos]->amount()));
    	}
    }

    char* toString() {
    	std::ostringstream os;
    	os << std::setw(2) << std::setfill('0') << "accountId: " << _accountId << ", owner: " << _details << ", balance: " <<
    			_balance << ", operations: " << _accountOperations.size();
    	return const_cast<char*>(os.str().c_str());
    };
};

