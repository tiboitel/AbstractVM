/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 16:47:51 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/02 18:19:40 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits.h>
#include <math.h>
#include <cfloat>
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "exception.hpp"

template <typename T>
class Operand : public IOperand
{
	public:
		Operand();
		Operand(const Operand&);
		Operand(std::string const &value, eOperandType type, int precision,
			const OperandFactory *factory) : _type(type), _factory(factory),
				_precision(precision)
		{
			try
			{
				if (type < Float)
				{
					long long v = std::stoll(value);
					if (hasOverflow<long long>(v, type))
						throw AbstractException("Overflow or underflow on value: ", value, __LINE__, "Operand.hpp");
					_value = static_cast<T>(v);
					std::stringstream ss(std::stringstream::out);
					ss << std::setprecision(_precision) << v;
					_str = ss.str();
				}
				else
				{
					long double v = std::stold(value);	
					if (hasOverflow<long double>(v, type))
						throw AbstractException("Overflow or underflow on value: ", value, __LINE__, "Operand.hpp");
					_value = static_cast<T>(v);
					std::stringstream ss(std::stringstream::out);
					ss << std::setprecision(_precision) << v;
					_str = ss.str();

				}
			}
			catch (std::exception const &e)
			{
				throw;
			}
		}
		const Operand &operator=(const Operand&);
		IOperand const *operator+(IOperand const &rhs) const
		{
			eOperandType	type = (this->_type >= rhs.getType()) ? _type : rhs.getType();
			int				precision = (this->_precision >= rhs.getPrecision()) ? _precision : rhs.getPrecision();
			try
			{
				std::stringstream	ss(std::stringstream::out);
				if (type < Float)
				{
					long long r = std::stoll(_str) + std::stoll(rhs.toString());
					if (hasOverflow<long long>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "+" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << r;
				}
				else
				{
					long double r = std::stold(_str) + std::stold(rhs.toString());
					if (hasOverflow<long double>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "+" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << std::setprecision(precision) << r;
				}
				return (_factory->createOperand(type, ss.str()));
			} 
			catch (std::exception const &e)
			{
				throw;
			}
			return (0);
		}

		IOperand const *operator-(IOperand const &rhs) const
		{
			eOperandType	type = (this->_type >= rhs.getType()) ? _type : rhs.getType();
			int				precision = (this->_precision >= rhs.getPrecision()) ? _precision : rhs.getPrecision();
			try
			{
				std::stringstream	ss(std::stringstream::out);
				if (type < Float)
				{
					long long r = std::stoll(_str) - std::stoll(rhs.toString());
					if (hasOverflow<long long>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "-" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << r;
				}
				else
				{
					long double r = std::stold(_str) - std::stold(rhs.toString());
					if (hasOverflow<long double>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "-" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << std::setprecision(precision) << r;
				}
				return (_factory->createOperand(type, ss.str()));
			} 
			catch (std::exception const &e)
			{
				throw;
			}
			return (0);
		}

		IOperand const *operator*(IOperand const &rhs) const
		{
			eOperandType	type = (this->_type >= rhs.getType()) ? _type : rhs.getType();
			int				precision = (this->_precision >= rhs.getPrecision()) ? _precision : rhs.getPrecision();
			try
			{
				std::stringstream	ss(std::stringstream::out);
				if (type < Float)
				{
					long long r = std::stoll(_str) * std::stoll(rhs.toString());
					if (hasOverflow<long long>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "*" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << r;
				}
				else
				{
					long double r = std::stold(_str) * std::stold(rhs.toString());
					if (hasOverflow<long double>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "*" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << std::setprecision(precision) << r;
				}
				return (_factory->createOperand(type, ss.str()));
			} 
			catch (std::exception const &e)
			{
				throw;
			}
			return (0);
		}

		IOperand const *operator/(IOperand const &rhs) const
		{
			eOperandType	type = (this->_type >= rhs.getType()) ? _type : rhs.getType();
			int				precision = (this->_precision >= rhs.getPrecision()) ? _precision : rhs.getPrecision();
			try
			{
				std::stringstream	ss(std::stringstream::out);
				if (type < Float)
				{
					long long r = std::stoll(_str) / std::stoll(rhs.toString());
					if (hasOverflow<long long>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "/" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << r;
				}
				else
				{
					long double r = std::stold(_str) / std::stold(rhs.toString());
					if (hasOverflow<long double>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "/" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << std::setprecision(precision) << r;
				}
				return (_factory->createOperand(type, ss.str()));
			} 
			catch (std::exception const &e)
			{
				throw;
			}
			return (0);
		}

		IOperand const *operator%(IOperand const &rhs) const
		{
			eOperandType	type = (this->_type >= rhs.getType()) ? _type : rhs.getType();
			int				precision = (this->_precision >= rhs.getPrecision()) ? _precision : rhs.getPrecision();
			try
			{
				std::stringstream	ss(std::stringstream::out);
				if (type < Float)
				{
					long long r = std::stoll(_str) % std::stoll(rhs.toString());
					if (hasOverflow<long long>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "%" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << r;
				}
				else
				{
					long double r = fmod(std::stold(_str), std::stold(rhs.toString()));
					if (hasOverflow<long double>(r, type))
						throw AbstractException("Overflow or underflow on value: ", _str + "%" + rhs.toString(), __LINE__, "Operand.hpp");
					ss << std::setprecision(precision) << r;
				}
				return (_factory->createOperand(type, ss.str()));
			} 
			catch (std::exception const &e)
			{
				throw;
			}
			return (0);
		}

		std::string const &toString(void) const
		{
			return (this->_str);
		}

		eOperandType getType(void) const
		{
			return (this->_type);
		}

		int getPrecision(void) const
		{
			return (this->_precision);
		}

		template <typename U>
		bool 	hasOverflow(U r, eOperandType type) const
		{
			switch (type)
			{
				case (Int8):
					return (r > SCHAR_MAX || r < SCHAR_MIN);
				case (Int16):
					return  (r > SHRT_MAX || r < SHRT_MIN);
				case (Int32):
					return (r > INT_MAX || r < INT_MIN);
				case (Float):
					return (r > FLT_MAX || r < -FLT_MAX);
				case (Double):
					return (r > DBL_MAX || r < -DBL_MAX);
					break;
			}
			return (true);
		}
		~Operand(void)
		{
		}

	private:
		T						_value;
		eOperandType			_type;
		const OperandFactory	*_factory;
		int						_precision;
		std::string				_str;
};

#endif
