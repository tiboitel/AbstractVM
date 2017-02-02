#include "IOperand.hpp"
#include "lexer.hpp"
#include "Operand.hpp"
#include "Machine.hpp"
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>

int		main(int argc, char **argv)
{
	std::string							entry;
	std::string							buffer;
	std::ifstream 						read_file;
	(void)argc;
	if (argc > 1)
		read_file.open(argv[1]);
	if (argc > 1 && !read_file.is_open())
		std::cerr << "Unable to open " << argv[1] << " file. Launch the program with a readable file. You can write your program in standard entry." << std::endl; 
	while (std::getline((read_file.is_open()) ? read_file : std::cin, entry))
	{
		if (entry.compare(";;") == 0)
			break;
		if (entry[0] == ';')
			continue;
		buffer.append(entry + " ");
	}
	if (read_file.is_open())
		read_file.close();
	Lexer lexer(buffer);
	lexer.tokenize();
	try
	{
		lexer.validate();
		std::vector<std::string>		tokens;
		tokens = lexer.getTokens();
		Machine							abstractvm(tokens);
		abstractvm.run();
	} catch (std::exception const &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (-1);
	}
	return (0);
}
