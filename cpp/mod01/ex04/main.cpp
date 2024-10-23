/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 12:09:05 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sys/types.h>


void	ocurrences_replace(std::string &line, std::string &to_replace, std::string &replacer)
{
	uint	replace_size = to_replace.length();
	uint	line_size = line.length();

	for (uint i = 0; i < line_size; i++)
	{
		for (uint j = 0; j <= replace_size; j++)
		{
			if (j == replace_size)
			{
				line.erase(i, j);
				line.insert(i, replacer);
				line_size = line.length();
			}
			else if (line[i + j] != to_replace[j])
				break ;
		}
	}
}

int main (int argc, char *argv[])
{
	if (argc != 4)
		return (1);
	std::string to_replace = argv[2];
	std::string replacer = argv[3];
	if (to_replace.empty())
	{
		std::cout << "Emtpy string to replace is not allowed!" << std::endl;
		return (1);
	}
	std::ifstream input_file(argv[1]);
	std::ofstream output_file((std::string(argv[1]) + ".replace").c_str());

	std::string line;
	if (!input_file.is_open() || !output_file.is_open() || to_replace.empty())
		return (1);
	else
	{
		while (getline(input_file, line))
		{
			ocurrences_replace(line, to_replace, replacer);
			output_file.write(line.c_str(), line.length());
			output_file << std::endl;
		}
	}
	input_file.close();
	output_file.close();
	return (0);
}
