/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 01:31:00 by tiboitel          #+#    #+#             */
/*   Updated: 2017/01/20 14:48:35 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_HPP
# define FT_LEXER_HPP
# include <string>
# include <sstream>
# include <algorithm>
# include <iterator>
# include <vector>
# include <iostream>
# include <unordered_map>
# include <functional>
# include <map>
# include <regex>

class	Lexer
{
	public:
		Lexer(std::string str);
		~Lexer();
		int tokenize(void);
		int	validate(void);
		std::vector<std::string> getTokens(void) const;
		std::string getEntry(void) const;
	private:	
		Lexer();
		Lexer(const Lexer &);
		std::vector<std::string> _tokens;
		std::string				 _entry;
		int						 _arithmetic_value;
		void					 _arithmetic_value_add(void);
		int						 _validate_pop(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_push(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_assert(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_add(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_sub(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_mul(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_div(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_print(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_mod(std::vector<std::string>::const_iterator iter) const;
		int						 _validate_dump(std::vector<std::string>::const_iterator iter) const;
};

typedef std::function<int(std::vector<std::string>::const_iterator iter)>	validate_function;
typedef std::map<std::string, validate_function> 			validate_table;
#endif
