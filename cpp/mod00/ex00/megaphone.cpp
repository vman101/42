#include <cctype>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			for (uint j = 0; j < std::string(argv[i]).length(); j++)
			{
				std::cout << (char)std::toupper(argv[i][j]);
			}
		}
		std::cout << std::endl;
	}
}
