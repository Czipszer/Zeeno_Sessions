#pragma once
#ifndef CHIP_MYEXCEPTION_HPP
#	define CHIP_MYEXCEPTION_HPP

#	include <exception>

class FileExcept : virtual public std::runtime_error {
public:
	explicit FileExcept(const std::string& message, int newErrorNumber) : std::runtime_error(message) {
		_errorNumber = newErrorNumber;
	}

	virtual ~FileExcept() throw() {
	}

	virtual int getErrorNumber() const throw() {
		return _errorNumber;
	}

protected:
	int _errorNumber;
};

#endif