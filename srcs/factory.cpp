/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 14:50:47 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/01 17:59:40 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"
#include "Operand.hpp"

OperandFactory::OperandFactory()
{
	create[Int8] = &OperandFactory::createInt8;
	create[Int16] = &OperandFactory::createInt16;
	create[Int32] = &OperandFactory::createInt32;
	create[Float] = &OperandFactory::createFloat;
	create[Double] = &OperandFactory::createDouble;
}

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
	IOperand const * (OperandFactory::*f)(std::string const &value) const;
	f = create.at(type);
	return ((*this.*f)(value));
}

OperandFactory::~OperandFactory()
{
}

IOperand const *OperandFactory::createInt8(std::string const &value) const
{
	return (new Operand<char>(value, Int8, 0, this));
}

IOperand const *OperandFactory::createInt16(std::string const &value) const
{
	return (new Operand<short int>(value, Int16, 0, this));
}

IOperand const *OperandFactory::createInt32(std::string const &value) const
{
	return (new Operand<int>(value, Int32, 0, this));
}

IOperand const *OperandFactory::createFloat(std::string const &value) const
{
	return (new Operand<float>(value, Float, 7, this));
}

IOperand const *OperandFactory::createDouble(std::string const &value) const
{
	return (new Operand<double>(value, Double, 14, this));
}


