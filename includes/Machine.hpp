/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:49:37 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/02 13:43:49 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHINE_HPP
# define MACHINE_HPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "Operand.hpp"
#include <list>
#include <string>
#include <vector>
#include <map>
#include "exception.hpp"
#include <regex>
#include <iostream>

class Machine
{
	public:
		Machine();
		Machine(std::vector<std::string> &tokens);
		Machine(const Machine&);
		void push(std::vector<std::string>::iterator &it);
		void pop(std::vector<std::string>::iterator &it);
		void dump(std::vector<std::string>::iterator &it);
		void assert(std::vector<std::string>::iterator &it);
		void add(std::vector<std::string>::iterator &it);
		void sub(std::vector<std::string>::iterator &it);
		void mul(std::vector<std::string>::iterator &it);
		void div(std::vector<std::string>::iterator &it);
		void mod(std::vector<std::string>::iterator &it);
		void print(std::vector<std::string>::iterator &it);
		void exit(std::vector<std::string>::iterator &it);
		eOperandType findType(std::string token);
		const Machine &operator=(const Machine&);
		~Machine();
		void run(void);
	private:
		std::list<const IOperand *>		_stack;
		std::vector<std::string>		_tokens;
		OperandFactory					_factory;
		std::map<std::string, void (Machine::*)(std::vector<std::string>::iterator& it)> _hashtable;
};

#endif
