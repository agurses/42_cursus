#include <string>
#include <fstream>
#include <iostream>

void	process(char **av, std::ofstream& ofile)
{
	std::string buffer;

	std::ifstream file(av[1]);
	while (std::getline(file, buffer))
	{
		size_t pos = 0;
		while ((pos = buffer.find(av[2], pos)) != std::string::npos)
		{
			buffer.erase(pos, std::string (av[2]).length());
			buffer.insert(pos, std::string (av[3]));
			pos += std::string (av[3]).length();
		}
		ofile << buffer << std::endl;
	}
	file.close();
}

int main(int ac, char **av)
{
	if (ac != 4 || !av[2] || !av[3])
	{
		std::cerr << "Error: Wrong Arguman Number" << std::endl;
		return (1);
	}
	if (std::string(av[2]).empty())
	{
		std::cerr << "AV2 is Empty" << std::endl;
		return (1);
	}
	if (std::string(av[3]).empty())
	{
		std::cerr << "AV3 is Empty" << std::endl;
		return (1);
	}
	std::ifstream file(av[1]);
	if (!file.is_open())
	{
		std::cerr << "Error: InputFile couldn't open" << std::endl;
		return (1);
	}
	file.close();
	std::ofstream ofile((std::string(av[1]) + ".replace").c_str());
	if (!ofile.is_open())
	{
		std::cerr << "Error: OutFile couldn't open" << std::endl;
		return (1);
	}
	process(av, ofile);
	ofile.close();
	return (0);
}

