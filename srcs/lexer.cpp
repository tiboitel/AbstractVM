/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 02:00:27 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/02 18:27:10 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.hpp"
#include "exception.hpp"

Lexer::Lexer(std::string str) : _entry(str), _arithmetic_value(0)
{
}

Lexer::Lexer(void)
{
	this->_arithmetic_value = 0;
}

Lexer::~Lexer(void)
{
	this->_tokens.clear();
}

int Lexer::_validate_pop(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_pop called." << std::endl;)
	D(std::cout << "_validate_pop value : " << this->_arithmetic_value << std::endl;)
	if (this->_arithmetic_value == 0)
		throw ParserException("Instruction pop on an empty stack.", iter - this->_tokens.begin(), "lexer.cpp", 35);
	return (0);
}

int Lexer::_validate_push(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_push_value : " << *(iter + 1) << std::endl;)
	if (!std::regex_match(*(iter + 1), std::regex("((int8|int16|int32)\\(-?[0-9]+\\))|((double|float)\\(-?[0-9]+(\\.[0-9]+)?\\))")))
		throw ParserException("An lexical error occured", iter - this->_tokens.begin(), "lexer.cpp", 40);
	return (0);
}

int Lexer::_validate_assert(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_assert called." << std::endl;)
	if (!std::regex_match(*(iter + 1), std::regex("((int8|int16|int32)\\(-?[0-9]+\\))|((double|float)\\(-?[0-9]+(\\.[0-9]+)?\\))")))
		throw ParserException("An lexical error occured", iter - this->_tokens.begin(), "lexer.cpp", 40);
	return (0);
}

int Lexer::_validate_add(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_add called." << std::endl;)
	if (this->_arithmetic_value < 2)
		throw ParserException("The stack is composed of strictly less that two values when arithmetic instruction is executed.", 0, "lexer.cpp", 61);
	return (0);
}

int Lexer::_validate_sub(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_sub_called." << std::endl;)
	if (this->_arithmetic_value < 2)
		throw ParserException("The stack is composed of strictly less that two values when arithmetic instruction is executed.", 0, "lexer.cpp", 61);
	return (0);
}

int Lexer::_validate_mul(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_mul called." << std::endl;)
	if (this->_arithmetic_value < 2)
		throw ParserException("The stack is composed of strictly less that two values when arithmetic instruction is executed.", 0, "lexer.cpp", 61);
	return (0);
}

int Lexer::_validate_div(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_mod called." << std::endl;)
	if (this->_arithmetic_value < 2)
		throw ParserException("The stack is composed of strictly less that two values when arithmetic instruction is executed.", 0, "lexer.cpp", 61);
	return (0);
}

int Lexer::_validate_mod(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_mod called." << std::endl;)
	if (this->_arithmetic_value < 2)
		throw ParserException("The stack is composed of strictly less that two values when arithmetic instruction is executed.", 0, "lexer.cpp", 61);
	return (0);
}

int Lexer::_validate_print(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_print called." << std::endl;)
	return (0);
}

int Lexer::_validate_dump(std::vector<std::string>::const_iterator iter) const
{
	(void)iter;
	D(std::cout << "_validate_dump called." << std::endl);
	return (0);
}

std::vector<std::string> Lexer::getTokens(void) const
{
	return (this->_tokens);
}

std::string Lexer::getEntry(void) const
{
	return (this->_entry);
}

int Lexer::tokenize(void)
{
	std::istringstream		iss(this->_entry);

	copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			back_inserter(this->_tokens));
	/*
	 ** Need to delete theses lines after debug.
	 */
	D(std::cout << "--- Dump tokens : ---" << std::endl);
	D(for (std::vector<std::string>::const_iterator i = this->_tokens.begin();
		i != this->_tokens.end();
			++i)
		std::cout << *i << std::endl;)
	return (1);
}

int	Lexer::validate(void)
{
	bool			have_exit;
	validate_table	table {
		{"pop", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_pop(iter));}},
		{"push", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_push(iter));}},
		{"exit", [this](std::vector<std::string>::const_iterator iter){(void)iter;return 0;}},
		{"assert", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_assert(iter));}},
		{"add", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_add(iter));}},
		{"sub", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_sub(iter));}},
		{"mul", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_mul(iter));}},
		{"div", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_div(iter));}},
		{"print", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_print(iter));}},
		{"mod", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_mod(iter));}},
		{"dump", [this](std::vector<std::string>::const_iterator iter){return (this->_validate_dump(iter));}}	
	};
	have_exit = false;
	D(std::cout << "--- Validate ---" << std::endl);
	for (std::vector<std::string>::const_iterator i = this->_tokens.begin();
		i != this->_tokens.end(); ++i)
	{
		auto iter = table.find(*i);
		if (!std::regex_match(*i, std::regex("[A-Za-z0-9;()]+")))
			throw ParserException("An lexical error occured", i - this->_tokens.begin(), "lexer.cpp", 80);
		if (iter == table.end())
			throw ParserException("An instruction is unknown : " + *i + ".", i  - this->_tokens.begin(), "lexer.cpp.", 82);
		else
		{
			iter->second(i);	
			if (iter->first.compare("exit") == 0)
				have_exit = true;
			if (iter->first.compare("push") == 0)
				i++, this->_arithmetic_value++;
			if (iter->first.compare("assert") == 0)
				i++;
		}
		/* Verifier si le token est une instruction possible. Et si le token suivant est valide au vus du precedent */
	}
	if (have_exit == false)
		throw ParserException("The program doesn't have an exit instruction.", 0, "lexer.cpp", 89);
	return (0);
}

Lexer::Lexer(const Lexer &rhs)
{
	this->_tokens = rhs.getTokens();
	this->_entry = rhs.getEntry();
}
