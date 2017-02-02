/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:43:32 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/02 18:42:34 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP
# include <exception>
# include <string>
# include <sstream>

#ifdef DEBUG
# define D(x) x
#else
# define D(x)
#endif

class ParserException : public std::exception
{
	public:
		ParserException(const std::string &msg, int line_number, const char *file, int line);
		virtual const char	*what(void) const throw();
		ParserException(ParserException const &rhs);
		~ParserException(void);	
	private:
		std::string		_error;
		ParserException	& operator=(ParserException const &rhs);
		ParserException(void);
};

class AbstractException : public std::exception
{
	public:
		AbstractException(const std::string &msg, const std::string &value, int line, const char *file);
		AbstractException(const std::string &msg, int line, const char *file);
		virtual const char *what(void) const throw();
		AbstractException(AbstractException const &rhs);
		~AbstractException(void);
	private:
		std::string _error;
		AbstractException &operator=(AbstractException const &rhs);
		AbstractException(void);
};
#endif
