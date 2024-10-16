#include <cctype>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	for (int i = 0; i < argc - 1; i++)
	{
		for (uint j = 0; j < std::string(argv[i]).length(); j++)
		{
			std::cout << toupper(argv[i][j]);
		}
		std::cout << std::endl;
	}
}
