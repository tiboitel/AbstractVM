/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:49:02 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/02 18:27:32 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Machine.hpp"
#include "Operand.hpp"

Machine::Machine()
{
}

eOperandType Machine::findType(std::string token)
{
	eOperandType	type;

	type = Int8;
	if (std::regex_match(token, std::regex("(int8)\\(-?[0-9]+\\)")))
		type = Int8;
	else if (std::regex_match(token, std::regex("(int16)\\(-?[0-9]+\\)")))
		type = Int16;
	else if (std::regex_match(token, std::regex("(int32)\\(-?[0-9]+\\)")))
		type = Int32;
	else if (std::regex_match(token, std::regex("(float)\\(-?[0-9]+(\\.[0-9]+)?\\)")))
		type = Float;
	else if (std::regex_match(token, std::regex("(double)\\(-?[0-9]+(\\.[0-9]+)?\\)"))) 
		type = Double;
	else
		throw AbstractException("Unknow type value.", token, __LINE__, "Machine.cpp");

	return (type);
}

void Machine::push(std::vector<std::string>::iterator& it)
{	
	eOperandType						type;
	std::string							value;
	std::vector<std::string>::iterator 	i;
	std::smatch							m;
	
	i = it++;
	type = this->findType(*it);	
	if (std::regex_search(*it, m, std::regex("\\(-?[0-9]+(\\.[0-9]+)?\\)")))
		value = m.str();
	value = value.substr(1);
	value = value.substr(0, value.length() - 1);
	_stack.push_front(_factory.createOperand(static_cast<eOperandType>(type), value));
}

void Machine::pop(std::vector<std::string>::iterator& it)
{
	(void)it;
	if (_stack.size() == 0)
		throw AbstractException("Instruction pop on an empty stack.", __LINE__, "Machine.cpp");
	_stack.pop_front();
}

void Machine::dump(std::vector<std::string>::iterator& it)
{
	(void)it;
	if (_stack.size() == 0)
		throw AbstractException("Instruction pop on an dump stack.", __LINE__, "Machine.cpp");
	std::list<const IOperand *>::iterator	i;
	for (i = _stack.begin(); i != _stack.end(); i++)
		std::cout << (*i)->toString() << std::endl;
}

void Machine::assert(std::vector<std::string>::iterator& it)
{
	(void)it;	
	std::string value;
	std::smatch	m;	

	if (_stack.size() == 0)
		throw AbstractException("Assert instruction on empty stack.", 93, "Machine.cpp");
	std::vector<std::string>::iterator i = ++it;
	const IOperand *op = *(_stack.begin());
	if (std::regex_search(*i, m, std::regex("\\(-?[0-9]+(\\.[0-9]+)?\\)")))
		value = m.str();
	value = value.substr(1);
	value = value.substr(0, value.length() - 1);
	if (op->toString() != value)
		throw AbstractException("Assert instruction is not true (" + op->toString() + " != " + value + ")", __LINE__, "Machine.cpp");
	if (op->getType() != (this->findType(*i) - Int8))
		throw AbstractException("Assert instruction is not true different type.",  __LINE__, "Machine.cpp");
}

void Machine::add(std::vector<std::string>::iterator& it)
{
	(void)it;
	if (_stack.size() < 2)
		throw AbstractException("Arithmetic instruction on stack with less than two values.", __LINE__, "Machine.cpp");
	const IOperand 	*op = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*result = *op + *op1;
	delete op;
	delete op1;
	_stack.push_front(result);
}

void Machine::sub(std::vector<std::string>::iterator& it)
{
	(void)it;
	if (_stack.size() < 2)
		throw AbstractException("Arithmetic instruction on stack with less than two values.", __LINE__, "Machine.cpp");
	const IOperand 	*op = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*result = *op - *op1;
	delete op;
	delete op1;
	_stack.push_front(result);
}

void Machine::mul(std::vector<std::string>::iterator& it)
{
	(void)it;
	const IOperand 	*op = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*result = *op * *op1;
	delete op;
	delete op1;
	_stack.push_front(result);
}

void Machine::div(std::vector<std::string>::iterator& it)
{
	(void)it;
	const IOperand 	*op = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*op1 = *(_stack.begin());
	_stack.pop_front();
	if ((op->toString()).compare("0") == 0 || (op1->toString()).compare("0") == 0)
		throw AbstractException("Division by zero.", __LINE__, "Machine.cpp");
	const IOperand	*result = *op / *op1;
	delete op;
	delete op1;
	_stack.push_front(result);
}

void Machine::mod(std::vector<std::string>::iterator& it)
{
	(void)it;
	const IOperand 	*op = *(_stack.begin());
	_stack.pop_front();
	const IOperand	*op1 = *(_stack.begin());
	_stack.pop_front();
	if ((op->toString()).compare("0") == 0 || (op1->toString()).compare("0") == 0)
		throw AbstractException("Modulo by zero.", __LINE__, "Machine.cpp");
	const IOperand	*result = *op % *op1;
	delete op;
	delete op1;
	_stack.push_front(result);
}

void Machine::print(std::vector<std::string>::iterator& it)
{
	(void)it;
	if (_stack.size() == 0)
		throw AbstractException("Instruction print on an empty stack.", __LINE__, "Machine.cpp");
	const IOperand *op = *(_stack.begin());
	if (op->getType() != Int8)
		throw AbstractException("Instruction print on non 8-bit integer", __LINE__, "Machine.cpp");
	std::cout << (std::stoi(op->toString())) << std::endl;
}

void Machine::exit(std::vector<std::string>::iterator& it)
{
	for (std::list<const IOperand *>::iterator i = _stack.begin(); i != _stack.end(); i++)
		delete *i;
	std::exit(0);
	(void)it;
}

Machine::Machine(std::vector<std::string> &tokens) : _tokens(tokens)
{
	_hashtable["push"] = &Machine::push;
	_hashtable["pop"] = &Machine::pop;
	_hashtable["dump"] = &Machine::dump;
	_hashtable["assert"] = &Machine::assert;
	_hashtable["add"] = &Machine::add;
	_hashtable["sub"] = &Machine::sub;
	_hashtable["mul"] = &Machine::mul;
	_hashtable["div"] = &Machine::div;
	_hashtable["mod"] = &Machine::mod;
	_hashtable["print"] = &Machine::print;
	_hashtable["exit"] = &Machine::exit;
}

void Machine::run()
{
	D(std::cout << "--- Run program -- " << std::endl);
	for (std::vector<std::string>::iterator i = this->_tokens.begin();
		i != this->_tokens.end(); i++)
	{
		std::map<std::string, void (Machine::*)(std::vector<std::string>::iterator &it)>::iterator iter = _hashtable.find(*i);
		if (iter == _hashtable.end())
			continue;
		(this->*(_hashtable.find(*i)->second))(i);
	}
}

Machine::~Machine()
{
	for (std::list<const IOperand *>::iterator i = _stack.begin(); i != _stack.end(); i++)
		delete *i;
}
