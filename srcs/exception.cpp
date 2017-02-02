/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:48:26 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/02 14:38:27 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.hpp"
#include <iostream>

ParserException::ParserException(const std::string &msg, int line_number,
	const char *file, int line)
{
	std::stringstream	ss;

	ss << msg << " Program line: " << line_number << " throwed at line : " << line << " of "
		<< file;
	this->_error = ss.str();
}

ParserException::ParserException(ParserException const &rhs)
{
	*this = rhs;
}

ParserException &ParserException::operator=(ParserException const &rhs)
{
	(void)rhs;
	return (*this);
}

const char	*ParserException::what(void) const throw()
{
	return (this->_error.c_str());
}

ParserException::~ParserException(void)
{
}

AbstractException::AbstractException(const std::string &msg, int line, const char *file)
{
	std::stringstream ss;
	ss << msg  << " throwed at line : " << line << " of " << file;
	this->_error = ss.str();
}

AbstractException::AbstractException(const std::string &msg, const std::string &value,
	int line, const char *file)
{
	std::stringstream ss;
	ss << msg << value << " throwed at line : " << line << " of " << file;
	this->_error = ss.str();
}

const char *AbstractException::what(void) const throw()
{
	return (this->_error.c_str());
}

AbstractException::~AbstractException()
{
}
